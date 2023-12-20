#ifndef _BST_H
#define _BST_H

typedef struct node_t node_t;

/**
 * @brief Create a single node for BST
 * 
 * @param data char to store
 * @return node_t* structure containing data, else NULL
 */
node_t *bst_create_node(const char *data);

// /**
//  * @brief Deletes tree and clears storage location to NULL
//  * 
//  * @param root Address of where root is stored
//  * @return int 1 on success, 0 on fail
//  */
// int bst_destroy_tree(node_t **root);

// /**
//  * @brief Destroy a node
//  * 
//  * @param root 
//  * @return 
//  */
// int bst_delete(node_t **root, int target);

void bst_free(node_t *root);

/**
 * @brief Searches BST for target value.
 * 
 * @param root Starting point of tree to search
 * @param target Value to search for
 * @return int Target value on success, else 0
 */
node_t *bst_find(node_t *root, const char *target);

/**
 * @brief Add created node to BST
 * 
 * @param root Root of tree to add to
 * @param data New data to add
 * @return int Node value on success, else 0
 */
node_t *bst_insert(node_t *root, const char *data);

// /**
//  * @brief Counts nodes in tree
//  * 
//  * @param root Base of tree to check
//  * @return int Number of nodes, else 0
//  */
// int bst_size(node_t *root);

// /**
//  * @brief Gets the smallest value in the tree
//  * 
//  * @param root Base of tree to check
//  * @return int Value of smallest value, else 0
//  */
// int bst_min(node_t *root);

// /**
//  * @brief Gets largest value in the tree
//  * 
//  * @param root Base of tree to check
//  * @return int Value of largest value, else 0
//  */
// int bst_max(node_t *root);

// void bst_pre_traversal(node_t *root);

// void bst_in_traversal(node_t *root);

// void bst_post_traversal(node_t *root);

// int total_nodes(node_t *root);



// void bst_print(node_t *root);

// int bst_level(node_t *root);



#endif
