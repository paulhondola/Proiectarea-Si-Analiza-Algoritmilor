#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include "Bib.h"
#include <stdlib.h>

TTree bulkInsert(TTree a, FILE *f) {
	
	int x = 0, y = 0;

    while (fscanf(f, "%d %d", &y, &x) == 2) { // Ensures two values are read
        printf("Inserting %d %d\n", x, y);
        a = InsertNode(a, x, y);  // Ensure InsertNode correctly returns the new tree structure
    }

	return a;
}

bstNode createBSTNode(TKey key) {
	bstNode node = malloc(sizeof(struct BSTNODE));
	if (node == NULL) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

bstNode insert_into_bst(bstNode root, TKey key) {
	if (root == NULL) {
		bstNode newNode = (bstNode)malloc(sizeof(struct BSTNODE));
		if (newNode == NULL) {
			printf("Memory allocation failed!\n");
			exit(1);
		}
		newNode->key = key;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}

	if (key < root->key) {
		root->left = insert_into_bst(root->left, key);
	}
	else {
		root->right = insert_into_bst(root->right, key);
	}

	return root;
}

bstNode convert_generic_to_bst(TTree tree) {
	if (tree.size == 0) return NULL;

	bstNode root = NULL;

	for (uint8_t i = 1; i <= tree.size; i++) {
		root = insert_into_bst(root, tree.nodes[i].key);
	}

	return root;
}

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Usage: %s <input_file>\n", argv[0]);
		return 1;
	}

	FILE* f = fopen(argv[1], "r");
	if (f == NULL) {
		printf("Could not open file %s\n", argv[1]);
		return 2;
	}

	TTree a = { 0 };
	a = InitTree(a);
	a = bulkInsert(a, f);

	printArray(a);

	printf("\npreOrder:\n");
	preOrder(a);
	printf("\ninOrder:\n");
	inOrder(a);
	printf("\npostOrder:\n");
	postOrder(a);

	bstNode root = convert_generic_to_bst(a);

	// Print the BST
	printf("\nBST:\n");
	printBST(root);
	
	fclose(f);

	return 0;
}