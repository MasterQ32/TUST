#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

/**
 * \file arraylist.h
 * \brief Arraylist implementation.
 *
 * Provides a generic array list. Array lists have fast direct access, but slower adding of elements
 */

typedef struct ArrayList
{
	int count;
	int capacity;
	int itemsize;
	void *array;
} ArrayList;

/**
 * This macro allows you to access the array list as a normal array.
 * \param	list	The array list to be accessed.
 * \param	T		The type of the array you want to access.
 * \return			The array list as an array of type T.
 */
#define genarray(list, T) ((T*)((list)->array))

/**
 * Creates a new array list.
 * \param	itemsize	The size of one item in the array.
 * \param	capacity	The initial capacity of the list.
 * \return				The newly created array list.
 */
ArrayList *arraylist_create(int itemsize, int capacity);

/**
 * Frees an array list.
 * \param	list		The list to delete.
 */
void arraylist_delete(ArrayList *list);

/**
 * Adds a new item to the array list and returns its index
 * \param	list		The arraylist where the element should be added.
 * \param	element		The element to be added.
 * \return				The index of the added element.
 */
#define arraylist_add(list, element) arraylist_add_internal((list), &(element))

/**
 * Adds a new item at a given position to the array list and returns its index
 * \param	list		The arraylist where the element should be added.
 * \param	index		The position where the element should be inserted.
 * \param	element		The element to be added.
 * \return				The index of the added element.
 */
#define arraylist_insert(list, index, element) arraylist_insert_internal((list), (index), &(element))

/**
 * Removes the item at a given index.
 * \param	list		The arraylist where the element should be removed.
 * \param	index		The position of the element to remove.
 */
#define arraylist_remove_at(list, index) arraylist_remove_at_internal(list, index)

#include "arraylist.c"
#endif