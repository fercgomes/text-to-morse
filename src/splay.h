tNode* rightRotation(tNode* node);
/* Rotates the tree to the right,
 * Returns the tree after a right rotation*/

tNode* leftRotation(tNode* node);
/* Rotates the tree to the left,
 * Returns the tree after a left rotation*/

tNode* splay(tNode* root, int key, int* search_count);
/* Splays a node to the root of the tree,
 * returns a new tree with the node passed through argument as root*/

tNode* SPLAY_insert(tNode* root, int key, char* morse);
/* Inserts a new entry in the tree and splays it to the top of the tree;
 * returns a tree.*/

char* SPLAY_search(tNode** root, int key, int* search_count);
/* Splays the node with the key passed through argument,
 * if the node is contained in the tree, returns a pointer to the morse code of it.
 * else, returns NULL; */
