#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bst.h"

int main() {
    node_t *root = NULL;
    
    root = bst_insert(root, "apple");
    root = bst_insert(root, "banana");
    root = bst_insert(root, "cherry");

    node_t *found_node = bst_find(root, "banana");
    if (found_node) {
        printf("Found: %s\n", found_node->data);
    } else {
        printf("Not Found.\n");
    }
    
    bst_free(root);
    return 0;
}