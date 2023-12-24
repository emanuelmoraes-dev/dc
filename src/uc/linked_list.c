#include "uc/linked_list.h"
#include <stdlib.h>

UcLinkedListElement* __new_element();

/**
 * Initialize an empty UcLinkedList
 *
 * @param linked_list - UcLinkedList instance to be initialized
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_init(UcLinkedList* linked_list) {
	linked_list->size = 0;
	linked_list->__head = __new_element();

	if (linked_list->__head == NULL) {
		return UC_ERR_THROW_ALLOC(UC_ERR_ARG_ALLOC_LINKED_LIST_HEAD);
	}

	linked_list->__last = linked_list->__head;
	return C_OK;
}

/**
 * Get the head of UcLinkedList pointing to the first element in the list
 *
 * @param linked_list - UcLinkedList instance
 * @param head - UcLinkedList head pointing to the first element in the list
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_borrow_head(UcLinkedList* linked_list, borrow UcLinkedListElement** head) {
	if (linked_list->__head == NULL) {
        linked_list->__head = __new_element();

        if (linked_list->__head == NULL) {
        	*head = NULL;
        	return UC_ERR_THROW_ALLOC(UC_ERR_ARG_ALLOC_LINKED_LIST_HEAD);
        }

        linked_list->size = 0;
        linked_list->__last = linked_list->__head;
    }

    *head = linked_list->__head;
    return C_OK;
}

/**
 * Get the last element of UcLinkedList. If the list is empty, returns the head
 *
 * @param linked_list - UcLinkedList instance
 * @param last - Last element of UcLinkedList. If the list is empty, returns the head
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_borrow_last(UcLinkedList* linked_list, borrow UcLinkedListElement** last) {
	UcLinkedListElement* head;
	c_err error = uc_linked_list_borrow_head(linked_list, &head);

	if (error != C_OK) {
		return error;
	}

    if (linked_list->__last == NULL)
        linked_list->__last = head;

    *last = linked_list->__last;

    return C_OK;
}

/**
 * @param linked_list - UcLinkedList instance
 * @return true if the linked list is empty. false otherwise
 */
bool uc_linked_list_is_empty(UcLinkedList* linked_list) {
	if (linked_list->size <= 0) {
		return true;
	}

	UcLinkedListElement* head;
	c_err error = uc_linked_list_borrow_head(linked_list, &head);

	if (error != C_OK) {
		return true;
	}

	UcLinkedListElement* last;
	error = uc_linked_list_borrow_last(linked_list, &last);

	if (error != C_OK) {
		return true;
	}

	return head == last;
}

/**
 * Get the value at the beginning of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - value at the beginning of UcLinkedList
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_borrow_top(UcLinkedList* linked_list, borrow void** value) {
	if (linked_list->size == 0) {
        *value = NULL;
        return C_OK;
	}

	UcLinkedListElement* head;
	c_err error = uc_linked_list_borrow_head(linked_list, &head);

	if (error != C_OK) {
		return error;
	}

	if (head->next == NULL) {
		*value = NULL;
	} else {
		*value = head->next->value;
	}

    return C_OK;
}

/**
 * Find a UcLinkedListElement of UcLinkedList that has the provided position
 *
 * @param linked_list - UcLinkedList instance
 * @param index - position of the element to be searched
 * @param element - instance of UcLinkedListElement that has the provided position
 * @return true if the element was found. false otherwise
 */
bool uc_linked_list_find_element_at(UcLinkedList* linked_list, int index, borrow UcLinkedListElement** element) {
	int i = 0;
    UcLinkedListElement* it;
    UC_LINKED_LIST_FOR_EACH(it, linked_list) {
        if (i++ == index) {
            *element = it;
            return true;
        }
    }
    *element = NULL;
    return false;
}

/**
 * Find a UcLinkedListElement* from the list that has a value with the same reference provided
 *
 * @param linked_list - UcLinkedList instance
 * @param value - reference pointing to the value of UcLinkedListElement to be searched. NULL if the value was not found
 * @param element - instance of UcLinkedListElement* from the list that has a value with the same reference provided
 * @return true if the element was found. false otherwise
 */
bool uc_linked_list_find_element_by_reference(UcLinkedList* linked_list, const void* value, borrow UcLinkedListElement** element) {
	UcLinkedListElement* it;
    UC_LINKED_LIST_FOR_EACH(it, linked_list) {
        if (it->value == value) {
            *element = it;
            return true;
        }
    }
    *element = NULL;
    return false;
}

/**
 * Find and get the element before the list element that has the same reference as "value"
 *
 * @param linked_list - UcLinkedList instance
 * @param value - reference of the value after the value to be returned
 * @param element - element before the element that has the received reference. NULL if the element is not found
 * @return true if the element was found. false otherwise
 */
bool uc_linked_list_find_previous_by_reference(UcLinkedList* linked_list, const void* value, borrow UcLinkedListElement** element) {
	UcLinkedListElement* it;
    UC_LINKED_LIST_FOR_EACH_PREVIOUS(it, linked_list) {
        if (it->next != NULL && it->next->value == value) {
            *element = it;
            return true;
        }
    }
    *element = NULL;
    return false;
}

/**
 * Add a value to UcLinkedList after the given element
 *
 * @param linked_list - UcLinkedList instance
 * @param before - element before the element to be added. If NULL, last element is used
 * @param value - value to be added
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_add_next(UcLinkedList* linked_list, UcLinkedListElement* before, share void* value) {
	UcLinkedListElement* ant;

	if (before != NULL) {
		ant = before;
	} else {
		c_err error = uc_linked_list_borrow_last(linked_list, &ant);

		if (error != C_OK) {
			return error;
		}
	}
	
    UcLinkedListElement* prx = ant->next;
    ant->next = __new_element();

    if (ant->next == NULL) {
    	return UC_ERR_THROW_ALLOC(UC_ERR_ARG_ALLOC_LINKED_LIST_NEW_ELEMENT);
    }

    ant->next->value = value;
    ant->next->next = prx;

    if (prx == NULL) {
        linked_list->__last = ant->next;
    }

    linked_list->size++;

    return C_OK;
}

/**
 * Add a value to the beginning of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - Value to be added to the beginning of UcLinkedList
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_add_top(UcLinkedList* linked_list, share void* value) {
	UcLinkedListElement* head;
	c_err error = uc_linked_list_borrow_head(linked_list, &head);

	if (error != C_OK) {
		return error;
	}

	return uc_linked_list_add_next(linked_list, head, value);
}

/**
 * Add a value to the endding of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - Value to be added to the endding of UcLinkedList
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_add_last(UcLinkedList* linked_list, share void* value) {
	UcLinkedListElement* last;
	c_err error = uc_linked_list_borrow_last(linked_list, &last);

	if (error != C_OK) {
		return error;
	}

	return uc_linked_list_add_next(linked_list, last, value);
}

/**
 * Remove from UcLinkedList without freeing the memory of the element after the received element
 *
 * @param linked_list - UcLinkedList instance
 * @param element - element before the element to be removed
 * @param value - value removed from UcLinkedList. NULL if the value was not found
 * @return true if the element was located and removed from UcLinkedList. false otherwise
 */
bool uc_linked_list_remove_next(UcLinkedList* linked_list, UcLinkedListElement* element, move void** value) {
	if (uc_linked_list_is_empty(linked_list)) {
        *value = NULL;
        return false;
	}

	if (element == NULL) {
		*value = NULL;
		return false;
	}

    UcLinkedListElement* target = element->next;

    if (target == NULL) {
    	*value = NULL;
    	return false;
    }

    element->next = target->next;
    void* item = target->value;
    free(target);
    linked_list->size--;
    *value = item;
    return true;
}

/**
 * Remove from UcLinkedList and free the memory of the element after the received element
 *
 * @param linked_list - UcLinkedList instance
 * @param element - element before the element to be freed
 * @return true if the element was located, removed from UcLinkedList, and freed from memory. false otherwise
 */
bool uc_linked_list_eraser_next(UcLinkedList* linked_list, UcLinkedListElement* element) {
	void* value;
	bool removed = uc_linked_list_remove_next(linked_list, element, &value);

	if (removed && value != NULL) {
		free(value);
	}

	return removed;
}

/**
 * Remove from UcLinkedList and free the element's memory after the element using a destructor
 *
 * @param linked_list - UcLinkedList instance
 * @param element - element before the element to be freed
 * @return true if the element was located, removed from UcLinkedList, and freed from memory. false otherwise
 */
bool uc_linked_list_eraser_destructor_next(UcLinkedList* linked_list, UcLinkedListElement* element, void (*destructor)(void*)) {
	void* value;
	bool removed = uc_linked_list_remove_next(linked_list, element, &value);

	if (removed && value != NULL) {
		if (destructor != NULL) {
			destructor(value);
		} else {
			free(value);
		}
	}

	return removed;
}

/**
 * Remove the element from the beginning of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - value removed from the beginning of UcLinkedList. NULL if UcLinkedList is empty
 * @return true if the element was located and removed from UcLinkedList. false otherwise
 */
bool uc_linked_list_remove_top(UcLinkedList* linked_list, move void** value) {
	UcLinkedListElement* head;

	c_err error = uc_linked_list_borrow_head(linked_list, &head);

	if (error != C_OK || uc_linked_list_is_empty(linked_list)) {
		return false;
	}

	return uc_linked_list_remove_next(linked_list, head, value);
}

/**
 * Remove from the list and free the memory of the element at the beginning of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @return true if there was an element at the beginning of UcLinkedList that was removed and freed from UcLinkedList and memory. false otherwise
 */
bool uc_linked_list_eraser_top(UcLinkedList* linked_list) {
	void* value;
	bool removed = uc_linked_list_remove_top(linked_list, &value);

	if (removed && value != NULL) {
		free(value);
	}

	return removed;
}

/**
 * Remove the element from the endding of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - value removed from the endding of UcLinkedList. NULL if UcLinkedList is empty
 * @return true if the element was located and removed from UcLinkedList. false otherwise
 */
bool uc_linked_list_remove_last(UcLinkedList* linked_list, move void** value) {
	UcLinkedListElement* last;

	c_err error = uc_linked_list_borrow_last(linked_list, &last);

	if (error != C_OK) {
		return false;
	}

	return uc_linked_list_remove_next(linked_list, last, value);
}

/**
 * Remove from the list and free the memory of the element at the endding of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @return true if there was an element at the endding of UcLinkedList that was removed and freed from UcLinkedList and memory. false otherwise
 */
bool uc_linked_list_eraser_last(UcLinkedList* linked_list) {
	void* value;
	bool removed = uc_linked_list_remove_last(linked_list, &value);

	if (removed && value != NULL) {
		free(value);
	}

	return removed;
}

/**
 * Remove the elements from the list without freeing the elements of UcLinkedList from memory, starting from head.
 * Does not free UcLinkedList from memory
 *
 * @param linked_list - UcLinkedList instance
 * @param head - element pointing to the first element of UcLinkedList to be removed. If NULL, head is used
 * @return true if elements were found and removed. false otherwise
 */
bool uc_linked_list_clear_by_head(UcLinkedList* linked_list, UcLinkedListElement* head) {
	UcLinkedListElement* linked_list_head;
	c_err error = uc_linked_list_borrow_head(linked_list, &linked_list_head);

	if (error != C_OK) {
		return false;
	}

	if (head == NULL) {
		head = linked_list_head;
	}

    if (head->next == NULL) {
    	return false;
    }

    bool is_removed = uc_linked_list_clear_by_head(linked_list, head->next);
    void* removed_value;
    is_removed = uc_linked_list_remove_next(linked_list, head, &removed_value) || is_removed;

    if (is_removed && head == linked_list_head) {
        free(head);
        linked_list->__head = NULL;
        linked_list->__last = NULL;
    }

    return is_removed;
}

/**
 * Remove the elements from the list and free the elements of UcLinkedList from memory, starting from head.
 * Does not free UcLinkedList from memory
 *
 * @param linked_list - UcLinkedList instance
 * @param head - element pointing to the first element of UcLinkedList to be removed. If NULL, head is used
 * @return true if elements were found that were removed and freed from memory. false otherwise
 */
bool uc_linked_list_clear_eraser_by_head(UcLinkedList* linked_list, UcLinkedListElement* head) {
	UcLinkedListElement* linked_list_head;
	c_err error = uc_linked_list_borrow_head(linked_list, &linked_list_head);

	if (error != C_OK) {
		return false;
	}

	if (head == NULL) {
		head = linked_list_head;
	}

    if (head->next == NULL) {
    	return false;
    }

    bool is_removed = uc_linked_list_clear_eraser_by_head(linked_list, head->next);
    is_removed = uc_linked_list_eraser_next(linked_list, head) || is_removed;

    if (is_removed && head == linked_list_head) {
        free(head);
        linked_list->__head = NULL;
        linked_list->__last = NULL;
    }

    return is_removed;
}

/**
 * Remove the elements from the list and free the elements of UcLinkedList from memory using a destructor,
 * starting from head. Does not free UcLinkedList from memory
 *
 * @param linked_list - UcLinkedList instance
 * @param head - element pointing to the first element of UcLinkedList to be removed. If NULL, head is used
 * @param destructor - destructor for each element of UcLinkedList
 * @return true if elements were found that were removed and freed from memory. false otherwise
 */
bool uc_linked_list_clear_eraser_destructor_by_head(UcLinkedList* linked_list, UcLinkedListElement* head, void (*destructor)(void*)) {
	UcLinkedListElement* linked_list_head;
	c_err error = uc_linked_list_borrow_head(linked_list, &linked_list_head);

	if (error != C_OK) {
		return false;
	}

	if (head == NULL) {
		head = linked_list_head;
	}

    if (head->next == NULL) {
    	return false;
    }

    bool is_removed = uc_linked_list_clear_eraser_destructor_by_head(linked_list, head->next, destructor);
    is_removed = uc_linked_list_eraser_destructor_next(linked_list, head, destructor) || is_removed;

    if (is_removed && head == linked_list_head) {
        free(head);
        linked_list->__head = NULL;
        linked_list->__last = NULL;
    }

    return is_removed;
}

/**
 * Remove the elements from the list without freeing the elements of UcLinkedList from memory, starting from head
 * and free the UcLinkedList memory
 * @param linked_list - UcLinkedList instance
 */
void uc_linked_list_free(UcLinkedList* linked_list) {
	uc_linked_list_clear_by_head(linked_list, NULL);
	free(linked_list);
}

UcLinkedListElement* __new_element() {
	UcLinkedListElement* element = (UcLinkedListElement*) malloc(sizeof(UcLinkedListElement));

	if (element == NULL) {
		return NULL;
	}

    element->value = NULL;
    element->next = NULL;

    return element;
}
