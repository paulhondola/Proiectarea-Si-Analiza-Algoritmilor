#include<stdio.h>
#include<stdint.h>
#include "Bib.h"

TTree InitTree(TTree a) {
	for (int i = 0; i < MAXNODES; i++) {
		a.nodes[i].firstChild = 0;
		a.nodes[i].rightSibling = 0;
		a.nodes[i].key = 0;
	}
	a.size = 0;
	return a;
}

TTree InsertNode(TTree a, TNodeRef  parent, TKey key) {

	if (a.size >= MAXNODES - 1) return a;

	if (parent < 0 || parent > a.size) return a;

	a.size++;
	a.nodes[a.size].key = key;
	a.nodes[a.size].firstChild = 0;
	a.nodes[a.size].rightSibling = 0;

	if (parent == 0) return a;

	TNodeRef parentIndex = parent;

	if (a.nodes[parentIndex].firstChild == 0) {
		a.nodes[parentIndex].firstChild = a.size;
		return a;
	}

	TNodeRef childIndex = a.nodes[parentIndex].firstChild;
	while (a.nodes[childIndex].rightSibling != 0) {
		childIndex = a.nodes[childIndex].rightSibling;
	}

	a.nodes[childIndex].rightSibling = a.size;

	return a;
}

void printArray(TTree a) {
	printf("\nIndex:\n");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%d ", i);
	}
	printf("\nKey:\n");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%d ", a.nodes[i].key);
	}
	printf("\nFirst Child:\n");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%d ", a.nodes[i].firstChild);
	}
	printf("\nRight Sibling:\n");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%d ", a.nodes[i].rightSibling);
	}
	printf("\n-----------------------------------------------------------");
}

void printNode(TNode node, char* message) {
	printf("\n%s Key: %d, FS: %d, RS: %d\n", message, node.key, node.firstChild, node.rightSibling);
}

TNodeRef parent(TTree a, TNodeRef noderef) {
	if (noderef == 0 || noderef > a.size) {
		return 0; // Invalid node reference, no parent
	}

	// Search all nodes to find which node has `noderef` as a child
	for (TNodeRef i = 1; i <= a.size; i++) {
		// Check if `noderef` is the first child of node `i`
		if (a.nodes[i].firstChild == noderef) {
			return i; // `i` is the parent
		}

		// Check if `noderef` is a right sibling of node `i`
		TNodeRef sibling = a.nodes[i].firstChild;
		while (sibling != 0) {
			if (a.nodes[sibling].rightSibling == noderef) {
				return i; // `i` is the parent
			}
			sibling = a.nodes[sibling].rightSibling;
		}
	}

	return 0; // No parent found (noderef might be the root)
}

TNodeRef getRoot(TTree a) {
	if (a.size < 1) return 0;
	return 1;
}

TNodeRef findNodeIndex(TTree a, TNode node) {
	for (uint8_t i = 0; i <= a.size; i++) {
		if (a.nodes[i].key == node.key && a.nodes[i].firstChild == node.firstChild && a.nodes[i].rightSibling == node.rightSibling) return i;
	}
	return 0;
}

TNodeRef firstChild(TTree a, TNodeRef index) {
	return a.nodes[index].firstChild;
	/*
	if (!index) return 0;
	for (uint8_t i = 1; i <= a.size; i++) {
		if (a.nodes[i].parent == index) return i;
	}
	return 0;
	*/
}

TKey nodeKey(TTree a, TNodeRef noderef) {
	if (noderef > a.size) return 0;
	return a.nodes[noderef].key;
}

TNode nodeByRef(TTree a, TNodeRef noderef) {
	return a.nodes[noderef];
}

TNodeRef rightSibling(TTree a, TNodeRef noderef) {
	return a.nodes[noderef].rightSibling;
	/*
	if (!noderef) return 0;
	for (TNodeRef i = noderef + 1; i <= a.size; i++) {
		if (a.nodes[i].parent == a.nodes[noderef].parent) return i;
	}
	return 0;
	*/
}

TTree deleteNode(TTree a, TNodeRef noderef) {
	/*
	a.nodes[noderef].key = 0;
	a.nodes[noderef].parent = 0;

	for (TNodeRef i = noderef; i <= a.size; i++) {
		if (a.nodes[i].parent == noderef) {
			a.nodes[i].key = 0;
			a.nodes[i].parent = 0;
		}
	}

	for (TNodeRef i = noderef; i <= a.size; ) {
		if (a.nodes[i].parent == 0 && a.nodes[i].key == 0) {
			for (TNodeRef j = i + 1; j <= a.size; j++) {
				if (a.nodes[j].parent > i) a.nodes[j].parent--;
				a.nodes[j - 1] = a.nodes[j];

			}
			a.size--;
		}
		if (a.nodes[i].parent != 0 && a.nodes[i].key != 0) i++;
	}
	printArray(a);

	return a;
	*/
}

/*
void preOrderDo(TTree a, TNodeRef root) {
	printf("%d, ", nodeKey(a, root));
	TNodeRef fc = firstChild(a, root);
	if (fc) preOrderDo(a, fc);

	TNodeRef rs = fc;
	while ((rs = rightSibling(a, rs)) != 0) {
		preOrderDo(a, rs);
	}
}

void inOrderDo(TTree a, TNodeRef root) {
	TNodeRef fc = firstChild(a, root);
	if (!fc) {
		printf("%d, ", nodeKey(a, root));
		return;
	}
	inOrderDo(a, fc);
	printf("%d, ", nodeKey(a, root));
	TNodeRef  rs = fc;
	while ((rs = rightSibling(a, rs))) {
		inOrderDo(a, rs);
	}

}

void postOrderDo(TTree a, TNodeRef root) {
	if (!root) return;
	TNodeRef fc = firstChild(a, root);
	postOrderDo(a, fc);
	TNodeRef rs = fc;
	while ((rs = rightSibling(a, rs))) {
		postOrderDo(a, rs);
	}
	printf("%d, ", nodeKey(a, root));
}
*/

void preOrderDo(TTree a, TNodeRef node) {
	if (node == 0) return; // Base case

	printf("%d ", a.nodes[node].key); // Print node value

	// Traverse first child
	TNodeRef fc = firstChild(a, node);
	preOrderDo(a, fc);

	// Traverse right siblings
	TNodeRef rs = rightSibling(a, fc);
	while (rs != 0) {
		preOrderDo(a, rs);
		rs = rightSibling(a, rs);
	}
}

void inOrderDo(TTree a, TNodeRef node) {
	if (node == 0) return; // Base case
	// Traverse first child
	TNodeRef fc = firstChild(a, node);
	inOrderDo(a, fc);
	printf("%d ", a.nodes[node].key); // Print node value
	// Traverse right siblings
	TNodeRef rs = rightSibling(a, fc);
	while (rs != 0) {
		inOrderDo(a, rs);
		rs = rightSibling(a, rs);
	}
}

void postOrderDo(TTree a, TNodeRef node) {
	if (node == 0) return; // Base case
	// Traverse first child
	TNodeRef fc = firstChild(a, node);
	postOrderDo(a, fc);
	// Traverse right siblings
	TNodeRef rs = rightSibling(a, fc);
	while (rs != 0) {
		postOrderDo(a, rs);
		rs = rightSibling(a, rs);
	}
	printf("%d ", a.nodes[node].key); // Print node value
}

void preOrder(TTree a) {
	if (a.size < 1) return;
	preOrderDo(a, getRoot(a));
}
void inOrder(TTree a) {
	if (a.size < 1) return;
	inOrderDo(a, getRoot(a));
}
void postOrder(TTree a) {
	if (a.size < 1) return;
	postOrderDo(a, getRoot(a));
}