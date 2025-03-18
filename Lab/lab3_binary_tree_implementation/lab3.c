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

OBNode createOBNode(TKey key) {
	OBNode new = (OBNode)malloc(sizeof(struct OBNODE));
	if (new == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	new->key = key;
	new->left = NULL;
	new->right = NULL;
	return new;
}

OBNode convertFCRStoOBTree(TTree fcrs, TNodeRef root) {
	OBNode ob = createOBNode(fcrs.nodes[root].key);

	// Convert first child to left child
	if (fcrs.nodes[root].firstChild != 0)
		ob->left = convertFCRStoOBTree(fcrs, fcrs.nodes[root].firstChild);

	// Convert right sibling to right child
	if (fcrs.nodes[root].rightSibling != 0)
		ob->right = convertFCRStoOBTree(fcrs, fcrs.nodes[root].rightSibling);
	
	return ob;
}

void printOBTree(OBNode ob) {
	if (ob == NULL) return;
	printOBTree(ob->left);
	printf("%d ", ob->key);
	printOBTree(ob->right);
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

	inOrder(a);
	printf("\n");
	inOrderBinary(a);


	OBNode ob = NULL;

	ob = convertFCRStoOBTree(a, getRoot(a));

	// Print the OB tree
	printf("\nOB Tree:\n");
	printOBTree(ob);

	fclose(f);

	return 0;
}