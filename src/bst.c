#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "splay.h"

#define SPLAY 1

/* Inicializa uma ABP */
tNode* BST_create(){
	return NULL;
}

/* Desaloca uma ABP */
tNode* BST_delete(tNode* root){
	if(root){
		BST_delete(root->left);
		BST_delete(root->right);
		free(root->morseCode);
		free(root);
	}
	return NULL;
}

/* Retorna a string que contem o codigo Morse, caso encontrar. Retorna NULL se nao encontrar. */
char* BST_search(tNode* root, int key, int* search_count){
	if(root){
		if(root->ascii == key){
			(*search_count)++;
			return root->morseCode;
		}
		else if(key < root->ascii){
			(*search_count)++;
			return BST_search(root->left, key, search_count);
		}
		else if(key > root->ascii){
			(*search_count)++;	
			BST_search(root->right, key, search_count);			
		}
	} else return NULL;
}

/* Calcula a altura de uma arvore */
int BST_height(tNode *a){
	int leftHeight, rightHeight;
	if (a == NULL) return 0;
	else {
		leftHeight = BST_height(a->left);
		rightHeight = BST_height(a->right);
		if(leftHeight > rightHeight) return (1 + leftHeight);
		else return (1 + rightHeight);
	}
}

/* Insere um nodo em uma ABP, segundo os criterios de uma ABP */
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
