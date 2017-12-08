tNode* rightRotation(tNode* node);
/* Rotates the tree to the right,
 * Returns the tree after a right rotation*/

tNode* leftRotation(tNode* node);
/* Rotates the tree to the left,
 * Returns the tree after a left rotation*/

tNode* splay(tNode* root, int key);
/* Splays a node to the root of the tree,
 * returns a new tree with the node passed through argument as root*/

tNode* SPLAY_insert(tNode* root, int key, char* morse);
