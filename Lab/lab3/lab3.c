#include <stdio.h>
#include <stdint.h>
#include "Bib.h"
#include <stdlib.h>

TTree bulkInsert(TTree a) {
	a = InsertNode(a, 0, 1);
	a = InsertNode(a, 1, 2);
	a = InsertNode(a, 1, 3);
	a = InsertNode(a, 1, 4);
	a = InsertNode(a, 2, 5);
	a = InsertNode(a, 2, 6);
	a = InsertNode(a, 4, 7);

	return a;
}

int main(int argc, char** argv) {

	TTree a = { 0 };
	a = InitTree(a);
	printArray(a);
	a = bulkInsert(a);
	//a = InsertNode(a, 0,1);
	printArray(a);

	TNodeRef n = parent(a, 5);
	printNode(nodeByRef(a, n), "Parent: ");
	TNodeRef fc = firstChild(a, 1);
	printNode(nodeByRef(a, fc), "First Child: ");
	TNodeRef rs = rightSibling(a, 5);
	printNode(nodeByRef(a, rs), "Right sibling of 5: ");

	preOrder(a);
	printf("\n inOrder: \n");
	inOrder(a);
	printf("\n postOrder: \n");
	postOrder(a);
	return 0;
}