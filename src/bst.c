#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bst.h"

typedef struct node_t {
	node_t *left;
	node_t *right;
	const char *data;
} node_t;

node_t *bst_create_node(const char *data)
{
	if (!data || strlen(data) == 0) {
		return NULL;
	}

	node_t *root = calloc(1, sizeof(*root));
	if (root) {
		root->data = data;
		root->left = NULL;
		root->right = NULL;
	}
	return root;
}

// int bst_destroy_tree(node_t **root)
// {
// 	if (!root || !*root) {
// 		return 0;
// 	}

// 	// post-order recursion
// 	bst_destroy_tree(&((*root)->left));
// 	bst_destroy_tree(&((*root)->right));
// 	free(*root);
// 	*root = NULL;
// 		return 1;
// }

void bst_free(node_t *root)
{
    if (root) {
        bst_free(root->left);
        bst_free(root->right);
        // free(root->data);
        free(root);
    }
}

// // this is BAR-C for kicks
// int bst_delete(node_t **p_root, int target)
// {
// 	if (!p_root || !*p_root || target < 1) {
// 		return 0;
// 	}
// 	node_t *root = *p_root;

// 	if (target == root->data) {
// 		node_t *right = root->right;
// 		node_t *parent = root;
// 		if (right) {
// 		// if right has no left, we pull right->right up
// 		if (!right->left) {
// 			root->right = right->right;
// 		} else {
// 			// move to minimum of right sub-tree
// 			while (right->left) {
// 			parent = right;
// 			right = right->left;
// 			}

// 			// update parents->left (us) to our->right
// 			// we can't have a left or else we wouldn't be minimum
// 			parent->left = right->right;
// 		}
// 		root->data = right->data;
// 		free(right);

// 		} else {
// 		// we have no right, therefore left becomes root
// 		*p_root = root->left;
// 		free(root);
// 		}
// 		return target;
// 	}

// 	// call recursion on left or right child
// 	// ternary target < self ? left : right;
// 	node_t **next = target < root->data ? &(root->left) : &(root->right);
// 	return bst_delete(next, target);
// }

node_t *bst_find(node_t *root, const char *target)
{
	if (!root || !target || strlen(target) == 0) {
		return NULL;
	}

	int cmp = strcmp(target, root->data);
	if (cmp == 0) {
		return root;
	} else if (cmp < 0) {
		return bst_find(root->left, target);
	} else {
		return bst_find(root->right, target);
	}
}

node_t *bst_insert(node_t *root, const char *data)
{
	if (!data || strlen(data) == 0) {
		return root;
	}

	if (!root) {
		return bst_create_node(data);
	}

	int cmp = strcmp(data, root->data);

	if (cmp < 0) {
		root->left = bst_insert(root->left, data);
	} else if (cmp > 0) {
		root->right = bst_insert(root->right, data);
	}

	return root;
}

// int bst_size(node_t *root)
// {
// 	if (!root) {
// 		return 0;
// 	}

// 	int result = bst_size(root->left);
// 	result += bst_size(root->right);
// 	return result + 1;
// }

// int bst_min(node_t *root)
// {
// 	if (!root) {
// 		return 0;
// 	}
// 	if (!root->left) {
// 		return root->data;
// 	}
// 	return bst_min(root->left);
// }

// int bst_max(node_t *root)
// {
// 	if (!root) {
// 		return 0;
// 	}
// 	if (!root->right) {
// 		return root->data;
// 	}
// 	return bst_max(root->right);
// }

// void bst_print(node_t *root)
// {
// 	if (!root) {
// 		return;
// 	}
// 	show_tree(root, NULL, 0);
// }

// void bst_pre_traversal(node_t *root)
// {
// 	if (root != NULL) {
// 		printf("%d\t", root->data);
// 		bst_pre_traversal(root->left);
// 		bst_pre_traversal(root->right);
// 	}
// }

// void bst_in_traversal(node_t *root)
// {
// 	if (root != NULL) {
// 		bst_in_traversal(root->left);
// 		printf("%d\t", root->data);
// 		bst_in_traversal(root->right);
// 	}
// }

// void bst_post_traversal(node_t *root)
// {
// 	if (root != NULL) {
// 		bst_post_traversal(root->left);
// 		bst_post_traversal(root->right);
// 		printf("%d\t", root->data);
// 	}
// }

// int total_nodes(node_t *root)
// {
// 	if (!root) {
// 		return 0;
// 	} else {
// 		return (total_nodes(root->left) + total_nodes(root->right) + 1);
// 	}
// }
