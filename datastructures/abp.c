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
		new->left = NULL;
		new->right = NULL;
		return new;
	} else {
		if(ascii < root->ascii) root->left = BST_insert(root->left, ascii, morseCode);
		else if(ascii > root->ascii) root->right = BST_insert(root->right, ascii, morseCode);
		return root;
	}
}

void BST_prefixado(tNode* root){
	if(root){
		printf("Ascii: %d, Morse: %s\n", root->ascii, root->morseCode);
		BST_prefixado(root->left);
		BST_prefixado(root->right);
	}
}
