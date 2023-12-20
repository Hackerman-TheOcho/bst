#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bst.h"

int main() 
{
    node_t *root = bst_create_node("apple");
    
    root = bst_insert(root, "banana");
    root = bst_insert(root, "cherry");

    node_t *found_node = bst_find(root, "banana");
    if (found_node) {
        printf("Found: %s\n", found_node);
    } else {
        printf("Not Found.\n");
    }
    
    bst_free(root);
    return 0;
}