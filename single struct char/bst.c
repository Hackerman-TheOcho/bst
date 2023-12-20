#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

typedef struct node_t {
	node_t *left;
	node_t *right;
	int data;
} node_t;

// typedef struct bst_t {
// 	node_t *root;
// 	int size;
// } bst_t;

typedef struct trunk trunk_t;

static void show_tree(node_t *root, struct trunk *prev, int is_left);
static void show_trunks(struct trunk *p);

node_t *bst_create_node(int data)
{
	if (data < 1) {
		return NULL;
	}

	node_t *root = calloc(1, sizeof(*root));
	if (root) {
		root->data = data;
	}
	return root;
}

int bst_destroy_tree(node_t **root)
{
	if (!root || !*root) {
		return 0;
	}

	// post-order recursion
	bst_destroy_tree(&((*root)->left));
	bst_destroy_tree(&((*root)->right));
	free(*root);
	*root = NULL;
		return 1;
}

// this is BAR-C for kicks
int bst_delete(node_t **p_root, int target)
{
	if (!p_root || !*p_root || target < 1) {
		return 0;
	}
	node_t *root = *p_root;

	if (target == root->data) {
		node_t *right = root->right;
		node_t *parent = root;
		if (right) {
		// if right has no left, we pull right->right up
		if (!right->left) {
			root->right = right->right;
		} else {
			// move to minimum of right sub-tree
			while (right->left) {
			parent = right;
			right = right->left;
			}

			// update parents->left (us) to our->right
			// we can't have a left or else we wouldn't be minimum
			parent->left = right->right;
		}
		root->data = right->data;
		free(right);

		} else {
		// we have no right, therefore left becomes root
		*p_root = root->left;
		free(root);
		}
		return target;
	}

	// call recursion on left or right child
	// ternary target < self ? left : right;
	node_t **next = target < root->data ? &(root->left) : &(root->right);
	return bst_delete(next, target);
}

int bst_find(node_t *root, int target)
{
	if (!root || target < 1) {
		return 0;
	}
	if (root->data == target) {
		return target;
	}
	node_t *next = target < root->data ? root->left : root->right;
	return bst_find(next, target);
}

// int bst_add(node_t *root, node_t *new_node)
// {
// 	if (!root || !new_node) {
// 		return 0;
// 	}

// 	if (root->data == new_node->data) {
// 		return 0;
// 	} else if (root->data < new_node->data && root->right == NULL) {
// 		// add to right
// 		root->right = new_node;
// 		return new_node->data;
// 	} else if (new_node->data < root->data && root->left == NULL) {
// 		// add to left
// 		root->left = new_node;
// 		return new_node->data;	
// 	}

// 	node_t *next = new_node->data < root->data ? root->left : root->right;
// 	return bst_add(next, new_node);
// }

int bst_add(node_t **root, node_t *new_node)
{
	if (!new_node || !root) {
		return 0;
	}

	if (!*root) {
		*root = new_node;
		return new_node->data;
	}

	if ((*root)->data == new_node->data) {
		return 0;
	}

	node_t **next = new_node->data < (*root)->data 
			? &((*root)->left) : &((*root)->right);
	return bst_add(next, new_node);
}

int bst_size(node_t *root)
{
	if (!root) {
		return 0;
	}

	int result = bst_size(root->left);
	result += bst_size(root->right);
	return result + 1;
}

int bst_min(node_t *root)
{
	if (!root) {
		return 0;
	}
	if (!root->left) {
		return root->data;
	}
	return bst_min(root->left);
}

int bst_max(node_t *root)
{
	if (!root) {
		return 0;
	}
	if (!root->right) {
		return root->data;
	}
	return bst_max(root->right);
}

void bst_print(node_t *root)
{
	if (!root) {
		return;
	}
	show_tree(root, NULL, 0);
}

void bst_pre_traversal(node_t *root)
{
	if (root != NULL) {
		printf("%d\t", root->data);
		bst_pre_traversal(root->left);
		bst_pre_traversal(root->right);
	}
}

void bst_in_traversal(node_t *root)
{
	if (root != NULL) {
		bst_in_traversal(root->left);
		printf("%d\t", root->data);
		bst_in_traversal(root->right);
	}
}

void bst_post_traversal(node_t *root)
{
	if (root != NULL) {
		bst_post_traversal(root->left);
		bst_post_traversal(root->right);
		printf("%d\t", root->data);
	}
}

int total_nodes(node_t *root)
{
	if (!root) {
		return 0;
	} else {
		return (total_nodes(root->left) + total_nodes(root->right) + 1);
	}
}


// Adapted from: https://rosettacode.org/wiki/AVL_tree/C
struct trunk {
	struct trunk *prev;
	const char * str;
};

// Adapted from: https://rosettacode.org/wiki/AVL_tree/C
void show_trunks(struct trunk *p)
{
	if (!p) return;
	show_trunks(p->prev);
	printf("%s", p->str);
}

// Adapted from: https://rosettacode.org/wiki/AVL_tree/C
// this is very haphazard
void show_tree(node_t *root, struct trunk *prev, int is_left)
{
	if (root == NULL) return;

	struct trunk this_disp = { prev, "    " };
	const char *prev_str = this_disp.str;
	show_tree(root->left, &this_disp, 1);

	if (!prev)
		this_disp.str = "---";
	else if (is_left) {
		this_disp.str = ".--";
		prev_str = "   |";
	} else {
		this_disp.str = "`--";
		prev->str = prev_str;
	}

	show_trunks(&this_disp);
	printf("%d\n", root->data);

	if (prev) prev->str = prev_str;
	this_disp.str = "   |";

	show_tree(root->right, &this_disp, 0);
	if (!prev) puts("");
}
