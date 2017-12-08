/*
	CONVERSOR DE TEXTO PARA CODIGO MORSE
	TRABALHO FINAL DA DISCIPLINA DE ESTRUTURA DE DADOS
	AUTORES:
		Fernando Correa Gomes (00274317)
		Daniel de Souza Novaes (00290193)

	UFRGS 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

#include "bst.h"
#include "splay.h"
#include "draw.c"

#define BUFFERSIZE 256
#define MORSEMAX 10
#define FILENAMEMAX 25

//#define SUPER_CMD

/* Para escolha de implementacao */
#define ABP 0 
#define SPLAY 1

static int debug_flag = 0;

/* Converte caracteres para maiusculo */
int generateUpperAscii(int code){
	/* Converte a - z para A - Z */
	if(code >= 97 && code <= 122) return toupper(code);
	else return code;
}

/* Constroi uma ABP ou AVL com a tabela Morse */
tNode* tree_constructor(const char* filename, int implem_flag){
	FILE* table;
	char line[BUFFERSIZE];
	char *word, *string_alloc, *temp;
	
	int ascii, i;
	size_t morse_size;
	
	/* Ponteiro para funcao que insere elementos na arvore */
	tNode* (*insert) (tNode*, int, char*);
	
	/* Se implementacao eh ABP, seta funcao que insere */
	if(implem_flag == ABP) insert = &BST_insert;
	else insert = &SPLAY_insert;

	/* Inicializa a arvore */
	tNode* newTree = BST_create();

	table = fopen(filename, "r");  
	if(table == NULL){
		fprintf(stderr, "Erro ao abrir o arquivo %s.", filename);
		return NULL; // Retorna uma arvore vazia
	} else {
		/* Abriu o arquivo com a tabela morse */
		/* Busca uma linha de texto */
		while(fgets(line, BUFFERSIZE, table)){
			/* Primeiro token: ascii */
			word = strtok(line, "\n\r\t");		// Garante portabilidade para LF e CR+LF
			ascii = word[0];	

			/* Segundo token: string com o codigo Morse */
			word = strtok(NULL, "\n\r\t");
			
			/* Aloca espaco para string e copia string do arquivo */
			/* OBS:
				O espaco alocado para a string que representa o
				codigo Morse fica alocado independentemente 
				e nao depende da alocacao da arvore em si.
			*/

			/* Calcula tamanho necessario para string com o codigo Morse.
			   Caso a funcao nao retorne um valor valido, usa MORSEMAX como
			   default. Adiciona espaco para \0 tambem.*/
			morse_size = strlen(word);
			if(!morse_size) morse_size = MORSEMAX;
			else morse_size++;

			string_alloc = (char*)malloc(morse_size * sizeof(char));
			strcpy(string_alloc, word);	
	
			/* Insere caracter na arvore */
			/* OBS:
				A funcao insere depende da implementacao
				escolhida.
			*/
			newTree = insert(newTree, ascii, string_alloc);	
			if(debug_flag) save_tree_state_2(newTree, ascii, string_alloc);
		}	
		fclose(table);
		return newTree;
	}
}

/* Converte um arquivo de texto para codigo Morse.
   USO: txtToMorse(|tabela_morse.txt|, |arquivo_de_entrada.txt|, |arquivo_de_saida.txt|, implem_flag)
	implem_flag: ABP (Implementacao em ABP) [0]
		     AVL (Implementacao em AVL)	[1]
   Retorna 1 em caso de erro e 0 em caso de sucesso . */
int txtToMorse(const char* morsetable, const char* input_file, const char* output_file, int implem_flag){
	/* Contagem de tempo */
	clock_t start, end, elapsed;

	FILE *input_stream, *output_stream;

	
	int i, char_ascii;
	/* Contadores de comparacoes e caracteres convertidos */
	int search_count = 0, char_count = 0;

	char *word,
         line[BUFFERSIZE],
	     *morse_found,
	     delimiters[] = {" "};

	/* Decidir qual implementacao */
	tNode* morseTable = tree_constructor("TabelaMorse.txt", implem_flag);
	
	/* Abre arquivo com texto a ser traduzido */
	input_stream = fopen(input_file, "r");
	if (input_stream == NULL){
		fprintf(stderr, "Erro ao abrir o arquivo %s.\n", input_file);
		return 1;
	} else {
		/* Abre arquivo destino */	
		output_stream = fopen(output_file, "w");
		if(!output_stream){
			fprintf(stderr, "Erro ao abrir o arquivo %s.\n", output_file);
			fclose(input_stream);
			return 1;
		} else {
			/* Inicia leitura do arquivo */ 
			start = clock();
			/* Busca linha de texto */
			while(fgets(line, BUFFERSIZE, input_stream)){
				/* Busca palavra */
				word = strtok(line, delimiters);
				while(word != NULL){
					/* Recebe palavra */
					/* Percorre cada letra da palavra e imprime no arquivo o codigo Morse */
					for(i = 0; word[i] != '\0'; i++){

						/* TODO: FUNCAO ASCII */
						char_ascii = generateUpperAscii(word[i]);
						//printf("Convertendo de %d(%c) para %d(%c).\n", word[i], word[i], char_ascii, char_ascii);

						/* Busca o ponteiro para a string que contem o codigo Morse
						   para a letra informada */
						morse_found = BST_search(morseTable, char_ascii, &search_count);
						if(morse_found){
							char_count++;
							fprintf(output_stream, "%s ", morse_found);
						}
					}
					/* Insere delimitador de palavra */
					fprintf(output_stream, "/ ");
					/* Gera nova palavra */
					word = strtok(NULL, delimiters);
				}
			}
			end = clock();
			elapsed = 1000 * (end - start) / (CLOCKS_PER_SEC);
			/* Imprimir comparacoes */
			printf("+--------------------------------------------------------------------------------+\n");
			printf(">> Convertendo %s...\n", input_file);
			printf(">> Arquivo %s gerado com sucesso.\n", output_file);
			printf("+--------------------------------------------------------------------------------+\n");
			printf("* Implementacao utilizada:\t\t\t");
			if(implem_flag) printf("SPLAY\n");
			else printf("ABP\n");
						printf("* Altura da arvore utilizada:\t\t\t%d\n", BST_height(morseTable));
			printf("* Comparacoes realizadas em consultas:\t\t%d\n", search_count);
			printf("* Caracteres convertidos para Morse:\t\t%d\n", char_count);
			printf("* Tempo gasto no processamento:\t\t\t%ld ms\n", elapsed);
			if(debug_flag) printf("DEBUGGER ativado. Operacoes na arvore salvas em debug.txt\n");
			else printf("DEBBUGER desativado.\n");
			printf("+--------------------------------------------------------------------------------+\n");
		}
	}
	BST_delete(morseTable);
	fclose(input_stream);
	fclose(output_stream);
	return 0;
}

int main(int argc, char *argv[]){
	setlocale(LC_ALL,""); 

	#ifdef SUPER_CMD
	const char  *table_file = NULL,
				*input_file = NULL,
				*output_file = NULL;
	#endif

	/* Padrao: ABP */
	int implem = ABP;

	#ifdef SUPER_CMD
	/* TODO: Melhor esse algoritmo nos casos de erro */
	int c;
	while ((c = getopt(argc, argv, "t:i:o:ds")) != -1)
		switch (c)
		{
		case 't':
			table_file = optarg;
			break;
		case 'i':
			input_file = optarg;
			break;
		case 'o':
			output_file = optarg;
			break;
		case 'd':
			debug_flag = 1;
			break;
		case 's':
			// Implementacao de SPLAY
			implem = SPLAY;
			break;
		/*case '?':
			if (optopt == 't')
			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
			fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
			fprintf (stderr,
					"Unknown option character `\\x%x'.\n",
					optopt);
			return 1;*/
		//default:
			//abort ();
		}
		
		if(table_file && input_file && output_file){
			return txtToMorse(table_file, input_file, output_file, implem);
		}
		else{
			printf("* Arquivos obrigatorios nao especificados: ");
			if(!table_file) printf(" Tabela Morse ");
			if(!input_file) printf(" Arquivo de entrada ");
			if(!output_file) printf(" Arquivo de saida ");
			printf("\n");
			printf("* Uso correto:\n<programa> -t tabelamorse.txt -i entrada.txt -o saida.txt\n* Flags opcionais:\n* -s: Implementacao com arvore Splay (Default: ABP)\n* -d: Salva as operacoes em arvore em um arquivo de texto (Default: off)\n");	// Mudar para stderr
		}

	#else
	/* Caso o codigo de cima nao seja aceito! */
	if(argc != 4){
		fprintf(stderr, "* Numero incorreto de argumentos.\nUSO: <programa> tabelamorse.txt entrada.txt saida.txt\n");
		return 1;
	} else return txtToMorse(argv[1], argv[2], argv[3], implem);
	#endif
}
