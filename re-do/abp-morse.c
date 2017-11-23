#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define BUFFERSIZE 256

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
		free(root->morseCode);
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
		if(ascii < root->ascii) {
			root->left = BST_insert(root->left, ascii, morseCode);
		}
		else if(ascii > root->ascii){
			root->right = BST_insert(root->right, ascii, morseCode);
		}
		return root;
	}
}

void BST_prefixado(tNode* root){
	if(root){
	//	printf("Ascii: %d, Morse: %s \n", root->ascii, root->morseCode);
		BST_prefixado(root->left);
		BST_prefixado(root->right);
		printf("Ascii: %d, Morse: %s \n", root->ascii, root->morseCode);
	}
}

int Altura (tNode *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
      return 0;
    else
    {
       Alt_Esq = Altura (a->left);
       Alt_Dir = Altura (a->right);
       if (Alt_Esq > Alt_Dir)
         return (1 + Alt_Esq);
       else
         return (1 + Alt_Dir);
     }
}

int Calcula_FB(tNode *a){
	return (Altura(a->left) - Altura(a->right));
}

void Desenha(tNode *a , int nivel){
	int x;

	if (a !=NULL){
		for (x=1; x<=nivel; x++)
			printf("=");
		printf("%s FB= %d - ASCII: %d\n", a->morseCode, Calcula_FB(a), a->ascii);
		if (a->left != NULL) Desenha(a->left, (nivel+1));
		if (a->right != NULL) Desenha(a->right, (nivel+1));
	}
}


/* Constroi uma ABP com a tabela Morse */
tNode* BST_constructor(const char* filename){
	FILE* table;
	char line[BUFFERSIZE];
	char *word, *string_alloc;
	
	char* _morsecode;
	int _ascii, i;

	tNode* newTree = BST_create();
	table = fopen(filename, "r");  
	if(table == NULL){
		printf("Erro ao abrir o arquivo %s.", filename);
		return NULL; // Retorna uma arvore vazia
	} else {
		/* Abriu o arquivo com a tabela morse */
		while(fgets(line, BUFFERSIZE, table)){
			/* Buscou a linha */
	
			/* Primeiro token: ascii */
			word = strtok(line, "\t");
			_ascii = word[0]; 		// Usa os maiusculos.

			/* Segundo token: codigo morse */
			word = strtok(NULL, "\t");
			string_alloc = (char*)malloc(10*sizeof(char));
			strcpy(string_alloc, word);	
			_morsecode = word;
			
			newTree = BST_insert(newTree, _ascii, string_alloc); 	
		}	
		fclose(table);
		return newTree;
	}
}

/* Para teste das funcoes */

int main(int argc, char *argv[]){
	setlocale(LC_ALL,"");
	tNode* new;
	printf("%s\n", argv[1]);
	new = BST_constructor(argv[1]);
		if(new == NULL) printf("\nArvore vazia.\n");
	else BST_prefixado(new);
	//Desenha(new, 10);	

	BST_delete(new);
	return 0;
}
