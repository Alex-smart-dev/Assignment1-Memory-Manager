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
    
}

void list_insert_after(Node* prev_node, uint16_t data)<
{

}

void list_insert_before(Node** head, Node* next_node, uint16_t data)
{

}

void list_delete(Node** head, uint16_t data)
{

}

Node* list_search(Node** head, uint16_t data)
{

}

void list_display(Node** head)
{

}

void list_display_range(Node** head, Node* start_node, Node* end_node)
{

}

void Tmain()
{

}