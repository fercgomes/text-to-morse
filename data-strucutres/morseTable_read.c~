#include "abp.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 256



/* Constroi uma ABP com a tabela Morse */
int BST_constructor(const char* filename){
	FILE* table = fopen(filename, "r");
	char line[BUFFERSIZE];
	char* word; // Constante
	if(table == NULL){
		printf("Erro ao abrir o arquivo %s.", filename);
		return 1;
	} else {
		/* Abriu o arquivo com a tabela morse */
		while(fgets(line, BUFFERSIZE, table)){
			/* Buscou a linha */
			word = strtok(line, "\t");
			/* PRIMEIRO TOKEN -> ASCII */
			printf("Letra: %s - ", word);

			word = strtok(NULL, "\t");
			/* SEGUNDO TOKEN -> MORSECODE */	
			printf("Codigo: %s\n", word);
		}	
		return 0;
	}
}

int main(int argc, char* argv[]){
	BST_constructor(argv[0]);
	return 0;
}
