/* Implementacao de ABP */
#include <stdlib.h>

typedef struct treeNode tNode;
struct treeNode {
	char* morseCode;
	int ascii;
	tNode* left;
	tNode* right;
};

tNode* BST_create(){
	return NULL;
}

tNode* BST_delete(tNode* root){
	if(root){
		BST_delete(root->left);
		BST_delete(root->right);
		free(root);
	}
	return NULL;
}

/* Retorna o ASCII, caso encontrar. Retorna NULL se nao encontrar. */
char* BST_search(tNode* root, int key){
	if(root){
		if(root->ascii == key) return root->morseCode;
		else if(key < root->ascii) return BST_search(root->left, key);
		else return BST_search(root->right, key);			
	} else return NULL;
}

tNode* BST_insert(tNode* root, int ascii, char* morseCode){
	tNode* new;
	if(!root){
		new = (tNode*)malloc(sizeof(tNode));
		new->ascii = ascii;
		new->morseCode = morseCode;
		return new;
	} else {
		if(ascii < root->ascii) return root->right = BST_insert(root, ascii, morseCode);
		else return root->right = BST_insert(root, ascii, morseCode);
	}
}

void BST_prefixado(tNode* root){
	if(root){
		BST_prefixado(root->left);
		BST_prefixado(root->right);
		printf("Ascii: %d, Morse: %s", root->ascii, root->morseCode);

	}
}
