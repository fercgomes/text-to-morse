/* TAD: Arvore Binaria de Pesquisa */
typedef struct treeNode tNode;
struct treeNode {
	char* morseCode;
	int ascii;
	int factor;
	tNode* left;
	tNode* right;
};

tNode* BST_create();

tNode* BST_delete(tNode* root);

char* BST_search(tNode* root, int key, int* search_count);

int BST_height(tNode *a);

tNode* BST_insert(tNode* root, int ascii, char* morseCode);
