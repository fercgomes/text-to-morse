#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.c"

#define BUFFERSIZE 256



/* Constroi uma ABP com a tabela Morse */
int BST_constructor(const char* filename){
	FILE* table = fopen(filename, "r");
	char line[BUFFERSIZE];
	char* word; 
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
			printf("Codigo: %s", word);
		}	
		return 0;
	}
}

int main(int argc, char *argv[]){
	printf("%s\n", argv[1]);
	BST_constructor(argv[1]);
	return 0;
}
