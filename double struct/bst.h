#ifndef _BST_H
#define _BST_H

#include <stdbool.h>

typedef struct node_t node_t;
typedef struct bst_t bst_t;

typedef struct node_t {
	node_t *left;
	node_t *right;
	int data;
} node_t;

typedef struct bst_t {
	node_t *root;
	int size;
} bst_t;

/**
 * @brief Create a single node for BST
 * 
 * @param data Integers to store
 * @return node_t* structure containing data, else NULL
 * 
 * NOTE: Only accepts positive integers
 */
node_t *bst_create_node(int data);

/**
 * @brief Deletes tree and clears storage location to NULL
 * 
 * @param root Address of where root is stored
 * @return int 1 on success, 0 on fail
 */
int bst_destroy_tree(bst_t *tree);

/**
 * @brief Destroy a node
 * 
 * @param tree BST tree instance
 * @param target value to destroy 
 * @return 
 */
bool bst_delete(bst_t *tree, int target);

/**
 * @brief Searches BST for target value.
 * 
 * @param root Starting point of tree to search
 * @param target Value to search for
 * @return int True on success, else false
 */
bool bst_find(bst_t *tree, int target);

/**
 * @brief Add created node to BST
 * 
 * @param root Root of tree to add to
 * @param new_node New node to add
 * @return int Node value on success, else 0
 */
int bst_add(bst_t *tree, node_t *new_node);

/**
 * @brief Counts nodes in tree
 * 
 * @param root Base of tree to check
 * @return int Number of nodes, else 0
 */
int bst_size(node_t *root);

/**
 * @brief Gets the smallest value in the tree
 * 
 * @param root Base of tree to check
 * @return int Value of smallest value, else 0
 */
int bst_min(node_t *root);

/**
 * @brief Gets largest value in the tree
 * 
 * @param root Base of tree to check
 * @return int Value of largest value, else 0
 */
int bst_max(node_t *root);

void bst_print(bst_t *tree);

int bst_level(node_t *root);



#endif