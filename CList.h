#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#ifndef CLIST_H
#define CLIST_H
typedef struct Element Element;
typedef enum status
{
    OPEN = 0,
    PROTECTED = 1,
    PRIVATE = 2
} STATUS;
typedef struct
{
    int data;
    STATUS status;
    Element *next;
} Element;
typedef struct
{
    Element *head;
    int size;
} List;
/*Creates an Element*/
Element *createElement(int data, STATUS status)
{
    Element *newElement = malloc(sizeof(Element));
    newElement->data = data;
    newElement->status = status;
    newElement->next = NULL;
    return newElement;
}
/*Creates a list*/
List *createList()
{
    List *newList = malloc(sizeof(List));
    newList->head = createElement(-INT_MAX, OPEN);
    newList->size = 1;
    return newList;
}
/*Adds an Element to the list's end
    @param data
    @param status
    @param list
*/
void addElement(int data, STATUS status, List *list)
{
    list->size++;
    Element *newElement = createElement(data, status);
    if (list->head == NULL)
    {
        list->head = newElement;
        list->size = 1;
        return;
    }
    Element *temp = list->head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newElement;
}
/*Adds an Element to the list's end
 */
void addElementAsElement(Element *element, List *list)
{
    list->size++;
    Element *newElement = element;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    Element *temp = list->head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newElement;
}
/* Returns the last element's data, if the status is set as true.*/
int pop(List *list)
{
    if (list->size < 1)
    {
        return -INT_MAX - 1;
    }
    if (list->size == 1 && list->head->status == OPEN)
    {
        int data = list->head->data;
        free(list->head);
        list->head = NULL;
        list->size--;
        return data;
    }
    else if (list->size == 1 && (list->head->status == PRIVATE))
    {
        return INT_MIN;
    }
    else if (list->size == 1 && (list->head->status == PROTECTED))
    {
        return list->head->data;
    }
    Element *temp = list->head;
    Element *prev = temp;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp->status == OPEN)
    {
        int data = temp->data;
        prev->next = NULL;
        free(temp);
        list->size--;
        return data;
    }
    return INT_MIN;
}
int setEnd(List *list, STATUS status)
{
    if (list->size < 1)
    {
        return INT_MIN;
    }
    Element *element = list->head;
    while (element->next != NULL)
    {
        element = element->next;
    }
    element->status = status;
    if (status == OPEN || status == PROTECTED)
        return element->data;
    return INT_MIN;
}
#endif