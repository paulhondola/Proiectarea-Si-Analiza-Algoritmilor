#include<stdint.h>

#define MAXNODES 100

typedef uint8_t TKey;

typedef struct {
	uint8_t firstChild, rightSibling;
	TKey key;
}TNode;

typedef uint8_t TNodeRef;

typedef struct {
	TNode nodes[MAXNODES];
	uint8_t size; //tree size = number of nodes in the tree	
}TTree;

typedef struct OBNODE {
	struct OBNode* left;
	struct OBNode* right;
	TKey key;
} *OBNode;

TTree InitTree(TTree a);

TTree InsertNode(TTree a, TNodeRef  parent, TKey key);

void printArray(TTree a);

void printNode(TNode node, char* message);

TNodeRef parent(TTree a, TNodeRef noderef);

TKey nodeKey(TTree a, TNodeRef noderef);

TNode nodeByRef(TTree a, TNodeRef noderef);

TNodeRef firstChild(TTree a, TNodeRef noderef);

TNodeRef rightSibling(TTree a, TNodeRef noderef);

TTree deleteNode(TTree a, TNodeRef noderef);

void preOrder(TTree a);
void inOrder(TTree a);
void postOrder(TTree a);

void preOrderBinary(TTree a);
void inOrderBinary(TTree a);
void postOrderBinary(TTree a);
