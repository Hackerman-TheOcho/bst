#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bst.h"



typedef struct trunk trunk_t;

// static void show_tree(node_t *root, struct trunk *prev, int is_left);
// void show_tree(node_t *root, node_t *parent, int level);
static void show_trunks(struct trunk *p);

node_t *bst_create_node(int data)
{
	if (data < 1) {
		return NULL;
	}

	node_t *node = calloc(1, sizeof(*node));
	if (node) {
		node->left = NULL;
		node->right = NULL;
		node->data = data;
	}
	return node;
}

// Helper function for bst_destroy_tree
void bst_destroy_node(node_t *node) {
    if (node) {
        bst_destroy_node(node->left);
        bst_destroy_node(node->right);
        free(node);
    }
}

int bst_destroy_tree(bst_t *tree) {
	if (!tree || !tree->root) {
		return 0;
	}
        bst_destroy_node(tree->root);
        tree->root = NULL;
        tree->size = 0;
}

bool bst_delete(bst_t *tree, int target)
{
	if (!tree || !tree->root || target < 1) {
		return false;
	}

	node_t *root = tree->root;
	node_t *parent = NULL;
	node_t *current = root;

	while (current && current->data != target) {
		parent = current;
		if (target < current->data) {
			current = current->left;
		} else {
			current = current->right;
		}
	}

	if (!current) {
		// value not found
		return false;
	}

	if (!current->left && !current->right) {
		// delete node with no children
		if (!parent) {
			tree->root = NULL;
		} else if (parent->left == current) {
			parent->left = NULL;
		} else {
			parent->right = NULL;
		}
		free(current);
	} else if (!current->left || !current->right) {
		// delete node with 1 child
		node_t *child = current->left ? current->left : current->right;
		if (!parent) {
			tree->root = child;
		} else if (parent->left == current) {
			parent->left = child;
		} else {
			parent->right = child;
		}
		free(current);
	} else {
		// delete node with 2 kids
		node_t *successor = bst_min(current->right);
		current->data = successor->data;
		bst_delete(&(current->right), successor->data);
	}

	tree->size--;
	return true;
}

bool bst_find(bst_t *tree, int target)
{
	if (!tree || target < 1 || !tree->root) {
		return false;
	}

	node_t *current = tree->root;

	while (current) {
		if (current->data == target) {
			return true;
		} else if (target < current->data) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return false;
}

int bst_add(bst_t *tree, node_t *new_node)
{
	if (!new_node || !tree) {
		return 0;
	}

	node_t **root = &(tree->root);
	if (!*root) {
		*root = new_node;
		tree->size++;
		return 1;
	}

	if ((*root)->data == new_node->data) {
		return 0;
	}

	node_t **next = new_node->data < (*root)->data ? 
			&((*root)->left) : &((*root)->right);
	return bst_add(tree, new_node);
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

void bst_print(bst_t *tree)
{
    if (!tree || !tree->root) {
        return;
    }
    show_tree(tree->root, NULL, 0);
}


// // Adapted from: https://rosettacode.org/wiki/AVL_tree/C
// struct trunk {
// 	struct trunk *prev;
// 	const char * str;
// };

// // Adapted from: https://rosettacode.org/wiki/AVL_tree/C
// void show_trunks(struct trunk *p)
// {
// 	if (!p) return;
// 	show_trunks(p->prev);
// 	printf("%s", p->str);
// }

// Adapted from: https://rosettacode.org/wiki/AVL_tree/C
// this is very haphazard
// void show_tree(node_t *root, struct trunk *prev, int is_left)
// {
// 	if (root == NULL) return;

// 	struct trunk this_disp = { prev, "    " };
// 	const char *prev_str = this_disp.str;
// 	show_tree(root->left, &this_disp, 1);

// 	if (!prev)
// 		this_disp.str = "---";
// 	else if (is_left) {
// 		this_disp.str = ".--";
// 		prev_str = "   |";
// 	} else {
// 		this_disp.str = "`--";
// 		prev->str = prev_str;
// 	}

// 	show_trunks(&this_disp);
// 	printf("%d\n", root->data);

// 	if (prev) prev->str = prev_str;
// 	this_disp.str = "   |";

// 	show_tree(root->right, &this_disp, 0);
// 	if (!prev) puts("");
// }

void show_tree(node_t *root, node_t *parent, int level) 
{
	if (!root) {
		return;
	}

	show_tree(root->right, root, level + 1);

	for (int i = 0; i < level; i++) {
		printf("    ");
	}

	if (parent) {
		if (parent->left == root) {
		printf("L: ");
		} else {
		printf("R: ");
		}
	}

	printf("%d\n", root->data);

	show_tree(root->left, root, level + 1);
}