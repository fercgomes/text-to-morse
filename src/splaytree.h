typedef struct treeNode tNode;
struct treeNode {
  char* morseCode
  int ascii;
  tNode* leftChild;
  tNode* rightChild;
}

tNode* splayCreate();
/* Returns an empty tree*/

void splayDelete(tNode* root);
/* Delete all nodes on a tree and cleans the memory,
 * Returns an empty tree*/

tNode* rightRotation(tNode* node);
/* Rotates the tree to the right,
 * Returns the tree after a right rotation*/

tNode* leftRotation(tNode* node);
/* Rotates the tree to the left,
 * Returns the tree after a left rotation*/

tNode* splay(tNode* root, int key);
/* Splays a node to the root of the tree,
 * returns a new tree with the node passed through argument as root*/

tNode* insert(tNode* root, int key);
