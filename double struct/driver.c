#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bst.h"

// int main()
// {
//     srand(time(NULL));
//     node_t *root = NULL;
//     node_t *new = NULL;

//     for (int i = 0; i < 16; ++i) {
//         new = bst_create_node(rand() % 32);
//         if (0 == bst_add(&root, new)) {
//             free(new);
//         }
//     }

//     bst_print(root);

//     bst_destroy_tree(&root);
// }

int main()
{
    srand(time(NULL));
    bst_t tree; // Create a binary search tree using the bst_t structure
    tree.root = NULL; // Initialize the root to NULL
    tree.size = 0; // Initialize the size to 0

    for (int i = 0; i < 16; ++i) {
        node_t *new = (node_t *)malloc(sizeof(node_t)); // Create a new node directly using malloc
        if (!new) {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation error.\n");
            break;
        }
        new->data = rand() % 32;
        new->left = NULL;
        new->right = NULL;
        if (!bst_add(&tree, new)) {
            // If the node was not added to the tree, free it to avoid memory leak
            free(new);
        }
    }

    bst_print(&tree); // Pass the bst_t pointer to the bst_print function

    bst_destroy_tree(&tree); // Pass the bst_t pointer to the bst_destroy_tree function
}