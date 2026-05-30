#include <stdio.h>

#include <stdlib.h>

typedef struct Block {
    size_t size;
    int free;
    struct Block *next;
} Block;

#define BLOCK_SIZE sizeof(Block)

Block *head = NULL;  // start of the linked list

// find a free block big enough
Block *find_free_block(size_t size) {
    Block *current = head;
    while (current != NULL) {
        if (current->free == 1 && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// ask OS for more memory
Block *request_space(size_t size) {
    Block *block = malloc(BLOCK_SIZE + size);
    block->size = size;
    block->free = 0;
    block->next = NULL;
    return block;
}

// our malloc
void *my_malloc(size_t size) {
    Block *block;

    if (head == NULL) {
        // first ever malloc call
        block = request_space(size);
        head = block;
    } else {
        // look for a free block
        block = find_free_block(size);
        if (block == NULL) {
            // no free block found, get more memory
            block = request_space(size);
            // add to end of list
            Block *current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = block;
        } else {
            block->free = 0;
        }
    }

    return (void *)(block + 1);
}

// our free
void my_free(void *ptr) {
    Block *block = (Block *)ptr - 1;
    block->free = 1;
}

// test it
int main() {
    int *a = my_malloc(sizeof(int));
    int *b = my_malloc(sizeof(int));

    *a = 10;
    *b = 20;

    printf("a = %d\n", *a);
    printf("b = %d\n", *b);

    my_free(a);
    printf("freed a\n");

    int *c = my_malloc(sizeof(int));
    *c = 30;
    printf("c = %d\n", *c);
    printf("a and c same address? %s\n", a == c ? "YES" : "NO");

    return 0;
}