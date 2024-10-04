#include <stdio.h>
#include <stdlib.h>
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

    if (*head == next_node)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node *walker = *head;

    while (walker != NULL && walker->next != next_node)
    {
        walker = walker->next;
    }

    if (walker != NULL)
    {
        newNode->next = walker->next;
        walker->next = newNode;
    }
    else
    {
        mem_free(newNode); // Prevent memory leak if node wasn't inserted
    }
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
        walker = walker->next;
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
        printf("%" PRIu16", " , walker->data);
        walker = walker->next;
    }
    printf("%" PRIu16, walker->data);
    printf("]");
}

void list_display_range(Node** head, Node* start_node, Node* end_node)
{
    if (*head == NULL)
    {
        return;
    }

    if (start_node == NULL)
    {
        start_node = *head;
    }

    printf("[");
    while (start_node->next != end_node)
    {
        printf("%" PRIu16", ", start_node->data);
        start_node = start_node->next;
    }
    if (end_node == NULL)
    {
        printf("%" PRIu16, start_node->data);
        printf("]");
    }
    else
    {
        printf("%" PRIu16", ""%" PRIu16, start_node->data, end_node->data);
        printf("]");
    }
    
    
}

int list_count_nodes(Node** head)
{
    if (*head == NULL)
    {   
        return 0;
    }
    
    Node *walker = *head;
    int count = 0;
    while (walker != NULL)
    {
        count++;
        walker = walker->next;
    }
    return count;
}

void list_cleanup(Node** head)
{
    Node *temp = NULL;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        mem_free(temp);
    }
    
}
