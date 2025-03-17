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

TNodeRef getRoot(TTree a) {
	if (a.size < 1) return 0;
	return 1;
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

void convertNode(TTree* ob, TTree fcrs, TNodeRef fcrsNode, TNodeRef obNode) {
	if (fcrsNode == 0) return; // Base case

	// Copy key value
	ob->nodes[obNode].key = fcrs.nodes[fcrsNode].key;
	ob->size++;

	// Convert firstChild to leftChild
	if (fcrs.nodes[fcrsNode].firstChild != 0) {
		ob->nodes[obNode].firstChild = ob->size + 1;
		convertNode(ob, fcrs, fcrs.nodes[fcrsNode].firstChild, ob->size + 1);
	}

	// Convert rightSibling to rightChild
	if (fcrs.nodes[fcrsNode].rightSibling != 0) {
		ob->nodes[obNode].rightSibling = ob->size + 1;
		convertNode(ob, fcrs, fcrs.nodes[fcrsNode].rightSibling, ob->size + 1);
	}
}

// convert a FCRS tree to an ordered binary tree
TTree convertFCRStoOBTree(TTree fcrs) {
	if (fcrs.size < 1) return fcrs; // Empty tree case

	TTree ob = { 0 }; // Initialize new ordered binary tree
	ob.size = 1; // Root node starts at index 1
	TNodeRef root = getRoot(fcrs);
	// Start conversion from root (node 1)
	convertNode(&ob, fcrs, root, root);

	return ob;
}

TTree insertBST(TTree* ob, TNodeRef root, TKey key) {
	if (ob->size >= MAXNODES - 1) { // Prevent overflow
		printf("Tree is full, cannot insert more nodes.\n");
		return *ob;
	}

	if (root == 0) { // Root case
		ob->size++;  // Increment size
		TNodeRef newNodeIdx = ob->size;
		ob->nodes[newNodeIdx].key = key;
		ob->nodes[newNodeIdx].firstChild = 0;
		ob->nodes[newNodeIdx].rightSibling = 0;
		return *ob;
	}

	// Determine where to insert
	if (key < ob->nodes[root].key) {
		if (ob->nodes[root].firstChild == 0) {
			ob->size++;
			ob->nodes[root].firstChild = ob->size;
			ob->nodes[ob->size].key = key;
			ob->nodes[ob->size].firstChild = 0;
			ob->nodes[ob->size].rightSibling = 0;
		}
		else {
			*ob = insertBST(ob, ob->nodes[root].firstChild, key);
		}
	}
	else {
		if (ob->nodes[root].rightSibling == 0) {
			ob->size++;
			ob->nodes[root].rightSibling = ob->size;
			ob->nodes[ob->size].key = key;
			ob->nodes[ob->size].firstChild = 0;
			ob->nodes[ob->size].rightSibling = 0;
		}
		else {
			*ob = insertBST(ob, ob->nodes[root].rightSibling, key);
		}
	}

	return *ob;
}


void convertFCRStoBSTRecursive(TTree* bst, TTree fcrs, TNodeRef fcrsNode) {
	if (fcrsNode == 0) return; // Base case

	// Insert the current node into the BST
	*bst = insertBST(bst, getRoot(fcrs), fcrs.nodes[fcrsNode].key);

	// Recursively process first child (ensures left-side processing)
	convertFCRStoBSTRecursive(bst, fcrs, fcrs.nodes[fcrsNode].firstChild);

	// Recursively process right sibling (ensures right-side processing)
	convertFCRStoBSTRecursive(bst, fcrs, fcrs.nodes[fcrsNode].rightSibling);
}


TTree convertFCRStoBST(TTree fcrs) {
	if (fcrs.size < 1) return fcrs; // Handle empty tree case

	TTree bst = { 0 }; // Initialize new binary tree
	bst.size = 0;

	// Start recursive conversion from root (node 1)
	convertFCRStoBSTRecursive(&bst, fcrs, 1);

	return bst;
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

void preOrderBinaryDo(TTree a, TNodeRef ref) {
	if (ref == 0) return;

	printf("%d ", a.nodes[ref].key);
	preOrderBinaryDo(a, a.nodes[ref].firstChild);
	preOrderBinaryDo(a, a.nodes[ref].rightSibling);
}

void inOrderBinaryDo(TTree a, TNodeRef ref) {
	if (ref == 0) return;
	inOrderBinaryDo(a, a.nodes[ref].firstChild);
	printf("%d ", a.nodes[ref].key);
	inOrderBinaryDo(a, a.nodes[ref].rightSibling);
}

void postOrderBinaryDo(TTree a, TNodeRef ref) {
	if (ref == 0) return;
	postOrderBinaryDo(a, a.nodes[ref].firstChild);
	postOrderBinaryDo(a, a.nodes[ref].rightSibling);
	printf("%d ", a.nodes[ref].key);
}

void preOrderBinary(TTree a) {
	preOrderBinaryDo(a, getRoot(a));
}

void inOrderBinary(TTree a) {
	inOrderBinaryDo(a, getRoot(a));
}

void postOrderBinary(TTree a) {
	postOrderBinaryDo(a, getRoot(a));
}