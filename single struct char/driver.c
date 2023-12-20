#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bst.h"

int main()
{
    srand(time(NULL));
    node_t *root = NULL;
    node_t *new = NULL;

    for (int i = 0; i < 16; ++i) {
        new = bst_create_node(rand() % 32);
        if (0 == bst_add(&root, new)) {
            free(new);
        }
    }

    bst_print(root);

    bst_destroy_tree(&root);
}
