#include "memory_manager.h"
#include "common_defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct MemObj
{
    void *start;
    size_t amount;
} MemObj;


void *memoryBlock = NULL;
size_t *memVis = NULL;
MemObj *memObjs = NULL;
size_t capacityMemObjs = 0;
size_t sizeOfMemLeft = 0;
size_t maxMem = 0;

size_t checkForPlace(size_t size)
{
    int beginOfPlace = -1;
    size_t desiredAmount = 0;
    for (size_t i = 0; i < maxMem; i++) 
    {
        if (memVis[i] == 0) {
            if (beginOfPlace == -1) 
            {
                beginOfPlace = i;
            }
            desiredAmount++;

            if (desiredAmount == size) 
            {
                return beginOfPlace; 
            }
        } 
        else 
        {
            beginOfPlace = -1;
            desiredAmount = 0;
        }
    }

    return -1;    
}

int checkForObj(void *block)
{
    for (size_t i = 0; i < capacityMemObjs; i++)
    {
        if (memObjs[i].start == block)
        {
            return i;
        }
    }
    return -1;
}

void editMemVisSpace(size_t begin, size_t size, size_t emptyAdd)
{
    for (size_t i = 0; i < size; i++)
    {
        memVis[begin + i] = emptyAdd;
    }
}

// size_t posOfBlock(void *block)
// {
//     return (char*)block - (char*)memoryBlock;
// }

void addMemObj(size_t begin, size_t size)
{
    capacityMemObjs += 1;
    memObjs = realloc(memObjs, capacityMemObjs * sizeof(MemObj));
    if (memObjs == NULL) 
    {
        printf("Memory reallocation failed\n");
        exit(1);
    }

    editMemVisSpace(begin, size, 1);   
    // for (size_t i = 0; i < size; i++)
    // {
    //     memVis[begin + i] = 1;
    // }
    
    memObjs[capacityMemObjs-1].start = (char*)memoryBlock + begin;
    memObjs[capacityMemObjs-1].amount = size;
}

void mem_init(size_t size)
{
    memoryBlock = malloc(size);
    memVis = calloc(size, sizeof(*memVis));
    sizeOfMemLeft = size;
    memObjs = malloc(0 * sizeof(MemObj));
    capacityMemObjs = 0;
    maxMem = size;
}

void* mem_alloc(size_t size)
{
    if (size > sizeOfMemLeft)
    {
        return NULL;
    }
    if (maxMem >= size && memObjs == NULL)
    {
        addMemObj(0, size);
        sizeOfMemLeft -= size;
        return memoryBlock;
    }
    else
    {
        size_t begin = checkForPlace(size);
        if (begin != -1)
        {
            addMemObj(begin, size);
            sizeOfMemLeft -= size;
            return (char*)memoryBlock + begin;
        }
    }
    return NULL;
}

void mem_free(void* block)
{
    int posOfObj = checkForObj(block);

    if (posOfObj == -1)
    {
        printf("Block does not exist");
        return;
    }

    sizeOfMemLeft += memObjs[posOfObj].amount;

    size_t posOfBlock = (char*)block - (char*)memoryBlock;

    editMemVisSpace(posOfBlock, memObjs[posOfObj].amount, 0);
    // for (size_t i = posOfBlock; i < memObjs[posOfObj].amount; i++)
    // {
    //     memVis[i] = 0;
    // }
    
    for (size_t i = posOfObj; i < capacityMemObjs-1; i++)
    {
        memObjs[i] = memObjs[i+1];
    }
    
    capacityMemObjs -= 1;
    if (capacityMemObjs > 0) 
    {
        memObjs = realloc(memObjs, capacityMemObjs * sizeof(MemObj));
        if (memObjs == NULL && capacityMemObjs > 0) 
        {
            printf("Memory reallocation failed\n");
            exit(1);
        }
    }
    else 
    {
        free(memObjs);
        memObjs = NULL;
    }

}

void* mem_resize(void* block, size_t size)
{
    int posOfObj = checkForObj(block);
    if (posOfObj == -1)
    {
        return NULL;
    }

    size_t posOfBlock = (char*)block - (char*)memoryBlock;
    size_t newSize = memObjs[posOfObj].amount + (size - memObjs[posOfObj].amount);

    if (newSize == memObjs[posOfObj].amount)
    {
        return block;
    }
    else if (newSize < memObjs[posOfObj].amount)
    {
        editMemVisSpace(posOfBlock + newSize, (memObjs[posOfObj].amount - newSize) , 0);
        memObjs[posOfObj].amount = newSize;
        return block;
    }
    else
    {
        int begin = checkForPlace(newSize);

        if (begin == -1)
        {
            return NULL;
        }

        editMemVisSpace(posOfBlock, memObjs[posOfObj].amount, 0);
        memObjs[posOfObj].amount = newSize;
        editMemVisSpace(begin, memObjs[posOfObj].amount, 1);
        memObjs[posOfObj].start = memoryBlock + begin;
        return memoryBlock + begin;
    }
    
}

void mem_deinit()
{
    free(memoryBlock);
    if (memObjs != NULL)
    {
        free(memObjs);
        memObjs = NULL;
    }    
    free(memVis);
    capacityMemObjs = 0;
    sizeOfMemLeft = 0;
    maxMem = 0;
}

void Tmain()
{
    printf_yellow("  Testing mem_alloc(0) and mem_free --->");
    mem_init(1024);
    void *block1 = mem_alloc(0);
    my_assert(block1 != NULL);
    void *block2 = mem_alloc(200);
    my_assert(block2 != NULL);
    my_assert(block1 == block2);

    mem_free(block1);
    mem_free(block2);
    mem_deinit();
    printf_green("[PASS].\n");
}