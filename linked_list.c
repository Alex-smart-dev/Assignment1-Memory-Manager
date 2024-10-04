#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "linked_list.h"
#include "memory_manager.h"

void list_init(Node** head, size_t size)
{
    mem_init(size);
    *head = NULL;
}

void list_insert(Node** head, uint16_t data)
{
    Node *newNode = mem_alloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *walker = *head;
        while (walker->next != NULL)
        {
            walker = walker->next;
        }
        walker->next = newNode;
    }
}

void list_insert_after(Node* prev_node, uint16_t data)
{
    if (prev_node == NULL)
    {
        return;
    }
    
    Node *newNode = mem_alloc(sizeof(Node));
    newNode->data = data;
    newNode->next = prev_node->next;
    prev_node->next = newNode;
}

void list_insert_before(Node** head, Node* next_node, uint16_t data)
{
    if (next_node == NULL)
    {
        return;
    }

    Node *newNode = mem_alloc(sizeof(Node));
    newNode->data = data;

    Node *walker = *head;

    while (walker->next != next_node)
    {
        walker = walker->next;
    }

    newNode->next = walker->next;
    walker->next = newNode;
}

void list_delete(Node** head, uint16_t data)
{
    if (*head == NULL)
    {
        return;
    }

    Node *temp = NULL;

    if ((*head)->data == data)
    {
        temp = *head;
        *head = (*head)->next;
        mem_free(temp);
    }
    else
    {
        Node *walker = *head;
        while (walker != NULL && walker->next->data != data)
        {
            walker = walker->next;
        }

        if (walker == NULL)
        {
            return;
        }
        else
        {
            temp = walker->next;
            walker->next = temp->next;
            mem_free(temp);
            
        }
    }
}

Node* list_search(Node** head, uint16_t data)
{
    Node *walker = *head;
    while (walker != NULL)
    {
        if (walker->data == data)
        {
            return walker;
        }
    }
    return NULL;
}

void list_display(Node** head)
{   
    if (*head == NULL)
    {
        return;
    }
    Node *walker = *head;
    printf("[");
    while (walker->next != NULL)
    {
        printf("%" PRIu16, walker->data);
        walker = walker->next;
    }
    printf("%" PRIu16, walker->data);
    printf("]");
}

void list_display_range(Node** head, Node* start_node, Node* end_node)
{

}

int list_count_nodes(Node** head)
{
    return 0;
}

void list_cleanup(Node** head)
{

}

void Tmain()
{

}