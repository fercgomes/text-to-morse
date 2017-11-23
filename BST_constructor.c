#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructures/abp.c"

#define BUFFERSIZE 256

/* Constroi uma ABP com a tabela Morse */
tNode* BST_constructor(const char* filename){
	FILE* table = fopen(filename, "r");
	char line[BUFFERSIZE];
	char* word; 
	
	char* _morsecode;
	int _ascii;

	tNode* newTree = BST_create();

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
			printf("ASCII: %d - ", _ascii);	

			/* Segundo token: codigo morse */
			word = strtok(NULL, "\t");
			_morsecode = word;
			printf("Codigo: %s", _morsecode);
			
			newTree = BST_insert(newTree, _ascii, _morsecode); 	
		}	
		fclose(table);
		return newTree;
	}
}

/* Para teste das funcoes */

int main(int argc, char *argv[]){
	tNode* new;
	printf("%s\n", argv[1]);
	new = BST_constructor(argv[1]);
	if(new == NULL) printf("\nvazia\n");
	else BST_prefixado(new);
	BST_delete(new);
	return 0;
}
