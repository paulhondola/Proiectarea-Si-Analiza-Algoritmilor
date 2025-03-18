#include<stdio.h>
#include<stdint.h>
#include "Bib.h"

TTree InitTree(TTree a) {
	for (int i = 0; i < MAXNODES; i++) {
		a.nodes[i].parent = 0;
		a.nodes[i].key = 0;
	}
	a.size = 0;
	return a;
}

TTree InsertNode(TTree a, TNodeRef  parent, TKey key) {
	a.size++;
	a.nodes[a.size].key = key;
	a.nodes[a.size].parent = parent;
	return a;
}

void printArray(TTree a) {
	printf("\nIndex: ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", i);
	}
	printf("\nKey:   ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].key);
	}
	printf("\nParent:");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].parent);
	}
	printf("\n-----------------------------------------------------------");
}

void printNode(TNode node, char* message) {
	printf("\n%s Key: %d, Parent: %d\n", message, node.key, node.parent);
}
TNodeRef parent(TTree a, TNodeRef noderef) {
	return a.nodes[noderef].parent;
}

TNodeRef getRoot(TTree a) {
	if (a.size < 1) return 0;
	return 1;
}

TNodeRef findNodeIndex(TTree a, TNode node) {
	for (uint8_t i = 0; i <= a.size; i++) {
		if (a.nodes[i].key == node.key && a.nodes[i].parent == node.parent) return i;
	}
	return 0;
}

TNodeRef firstChild(TTree a, TNodeRef index) {
	if (!index) return 0;
	for (uint8_t i = 1; i <= a.size; i++) {
		if (a.nodes[i].parent == index) return i;
	}
	return 0;
}

TKey nodeKey(TTree a, TNodeRef noderef) {
	if (noderef > a.size) return 0;
	return a.nodes[noderef].key;
}

TNode nodeByRef(TTree a, TNodeRef noderef) {
	return a.nodes[noderef];
}

TNodeRef rightSibling(TTree a, TNodeRef noderef) {
	if (!noderef) return 0;
	for (TNodeRef i = noderef + 1; i <= a.size; i++) {
		if (a.nodes[i].parent == a.nodes[noderef].parent) return i;
	}
	return 0;
}

TTree deleteNode(TTree a, TNodeRef noderef) {
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
}

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

void printBST(bstNode root) {
	if (root == NULL) return;
	printBST(root->left);
	printf("%d, ", root->key);
	printBST(root->right);
}