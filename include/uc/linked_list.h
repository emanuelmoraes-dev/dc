#ifndef UC_LINKED_LIST_H_INCLUDED
#define UC_LINKED_LIST_H_INCLUDED

#include "uc/errors.h"
#include "uc/tags.h"
#include <stdbool.h>

#define UC_LINKED_LIST_FOR_EACH(it, linked_list) \
    for (it = (linked_list->__head != NULL ? linked_list->__head->next : NULL); it != NULL; it = it->next)

#define UC_LINKED_LIST_FOR_EACH_PREVIOUS(it, linked_list) \
    for (it = linked_list->__head; it != NULL; it = it->next)

/**
 * Struct representing an instance of each element in UcLinkedList
 */
typedef struct uc_linked_list_element {
    share void* value;
    owner  struct uc_linked_list_element* next;
} UcLinkedListElement;

/**
 * Struct representing an instance of UcLinkedList
 */
typedef struct uc_linked_list {
    int size;
    owner UcLinkedListElement* __head;
    owner UcLinkedListElement* __last;
} UcLinkedList;

/**
 * Initialize an empty UcLinkedList
 *
 * @param linked_list - UcLinkedList instance to be initialized
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_init(UcLinkedList* linked_list);

/**
 * Get the head of UcLinkedList pointing to the first element in the list
 *
 * @param linked_list - UcLinkedList instance
 * @param head - UcLinkedList head pointing to the first element in the list
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_borrow_head(UcLinkedList* linked_list, borrow UcLinkedListElement** head);

/**
 * Get the last element of UcLinkedList. If the list is empty, returns the head
 *
 * @param linked_list - UcLinkedList instance
 * @param last - Last element of UcLinkedList. If the list is empty, returns the head
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_borrow_last(UcLinkedList* linked_list, borrow UcLinkedListElement** last);

/**
 * @param linked_list - UcLinkedList instance
 * @return true if the linked list is empty. false otherwise
 */
bool uc_linked_list_is_empty(UcLinkedList* linked_list);

/**
 * Get the value at the beginning of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - value at the beginning of UcLinkedList
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_borrow_top(UcLinkedList* linked_list, borrow void** value);

/**
 * Find a UcLinkedListElement of UcLinkedList that has the provided position
 *
 * @param linked_list - UcLinkedList instance
 * @param index - position of the element to be searched
 * @param element - instance of UcLinkedListElement that has the provided position
 * @return true if the element was found. false otherwise
 */
bool uc_linked_list_find_element_at(UcLinkedList* linked_list, int index, borrow UcLinkedListElement** element);

/**
 * Find a UcLinkedListElement* from the list that has a value with the same reference provided
 *
 * @param linked_list - UcLinkedList instance
 * @param value - reference pointing to the value of UcLinkedListElement to be searched. NULL if the value was not found
 * @param element - instance of UcLinkedListElement* from the list that has a value with the same reference provided
 * @return true if the element was found. false otherwise
 */
bool uc_linked_list_find_element_by_reference(UcLinkedList* linked_list, const void* value, borrow UcLinkedListElement** element);

/**
 * Find and get the element before the list element that has the same reference as "value"
 *
 * @param linked_list - UcLinkedList instance
 * @param value - reference of the value after the value to be returned
 * @param element - element before the element that has the received reference. NULL if the element is not found
 * @return true if the element was found. false otherwise
 */
bool uc_linked_list_find_previous_by_reference(UcLinkedList* linked_list, const void* value, borrow UcLinkedListElement** element);

/**
 * Add a value to UcLinkedList after the given element
 *
 * @param linked_list - UcLinkedList instance
 * @param before - element before the element to be added. If NULL, last element is used
 * @param value - value to be added
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_add_next(UcLinkedList* linked_list, UcLinkedListElement* before, share void* value);

/**
 * Add a value to the beginning of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - Value to be added to the beginning of UcLinkedList
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_add_top(UcLinkedList* linked_list, share void* value);

/**
 * Add a value to the endding of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - Value to be added to the endding of UcLinkedList
 * @return C_OK if successful. Otherwise, return the error value
 */
c_err uc_linked_list_add_last(UcLinkedList* linked_list, share void* value);

/**
 * Remove from UcLinkedList without freeing the memory of the element after the received element
 *
 * @param linked_list - UcLinkedList instance
 * @param element - element before the element to be removed
 * @param value - value removed from UcLinkedList. NULL if the value was not found
 * @return true if the element was located and removed from UcLinkedList. false otherwise
 */
bool uc_linked_list_remove_next(UcLinkedList* linked_list, UcLinkedListElement* element, move void** value);

/**
 * Remove from UcLinkedList and free the memory of the element after the received element
 *
 * @param linked_list - UcLinkedList instance
 * @param element - element before the element to be freed
 * @return true if the element was located, removed from UcLinkedList, and freed from memory. false otherwise
 */
bool uc_linked_list_eraser_next(UcLinkedList* linked_list, UcLinkedListElement* element);

/**
 * Remove from UcLinkedList and free the element's memory after the element using a destructor
 *
 * @param linked_list - UcLinkedList instance
 * @param element - element before the element to be freed
 * @return true if the element was located, removed from UcLinkedList, and freed from memory. false otherwise
 */
bool uc_linked_list_eraser_destructor_next(UcLinkedList* linked_list, UcLinkedListElement* element, void (*destructor)(void*));

/**
 * Remove the element from the beginning of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - value removed from the beginning of UcLinkedList. NULL if UcLinkedList is empty
 * @return true if the element was located and removed from UcLinkedList. false otherwise
 */
bool uc_linked_list_remove_top(UcLinkedList* linked_list, move void** value);

/**
 * Remove from the list and free the memory of the element at the beginning of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @return true if there was an element at the beginning of UcLinkedList that was removed and freed from UcLinkedList and memory. false otherwise
 */
bool uc_linked_list_eraser_top(UcLinkedList* linked_list);

/**
 * Remove the element from the endding of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @param value - value removed from the endding of UcLinkedList. NULL if UcLinkedList is empty
 * @return true if the element was located and removed from UcLinkedList. false otherwise
 */
bool uc_linked_list_remove_last(UcLinkedList* linked_list, move void** value);

/**
 * Remove from the list and free the memory of the element at the endding of UcLinkedList
 *
 * @param linked_list - UcLinkedList instance
 * @return true if there was an element at the endding of UcLinkedList that was removed and freed from UcLinkedList and memory. false otherwise
 */
bool uc_linked_list_eraser_last(UcLinkedList* linked_list);

/**
 * Remove the elements from the list without freeing the elements of UcLinkedList from memory, starting from head.
 * Does not free UcLinkedList from memory
 *
 * @param linked_list - UcLinkedList instance
 * @param head - element pointing to the first element of UcLinkedList to be removed. If NULL, head is used
 * @return true if elements were found and removed. false otherwise
 */
bool uc_linked_list_clear_by_head(UcLinkedList* linked_list, UcLinkedListElement* head);

/**
 * Remove the elements from the list and free the elements of UcLinkedList from memory, starting from head.
 * Does not free UcLinkedList from memory
 *
 * @param linked_list - UcLinkedList instance
 * @param head - element pointing to the first element of UcLinkedList to be removed. If NULL, head is used
 * @return true if elements were found that were removed and freed from memory. false otherwise
 */
bool uc_linked_list_clear_eraser_by_head(UcLinkedList* linked_list, UcLinkedListElement* head);

/**
 * Remove the elements from the list and free the elements of UcLinkedList from memory using a destructor,
 * starting from head. Does not free UcLinkedList from memory
 *
 * @param linked_list - UcLinkedList instance
 * @param head - element pointing to the first element of UcLinkedList to be removed. If NULL, head is used
 * @param destructor - destructor for each element of UcLinkedList
 * @return true if elements were found that were removed and freed from memory. false otherwise
 */
bool uc_linked_list_clear_eraser_destructor_by_head(UcLinkedList* linked_list, UcLinkedListElement* head, void (*destructor)(void*));

/**
 * Remove the elements from the list without freeing the elements of UcLinkedList from memory, starting from head
 * and free the UcLinkedList memory
 * @param linked_list - UcLinkedList instance
 */
void uc_linked_list_free(UcLinkedList* linked_list);

#endif