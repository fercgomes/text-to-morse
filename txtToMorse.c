#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>

#define BUFFERSIZE 256
#define MORSEMAX 10

/* Para escolha de implementacao */
#define ABP 0 
#define AVL 1

/* TAD: Arvore Binaria de Pesquisa */
typedef struct treeNode tNode;
struct treeNode {
	char* morseCode;
	int ascii;
	int factor;
	tNode* left;
	tNode* right;
};

//#include "draw.c"

/* Contador de comparacoes na funcao de consulta */
static int search_count = 0;
/* Contador de letras convertidas */
static int char_count = 0;

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
char* BST_search(tNode* root, int key){
	if(root){
		if(root->ascii == key){
			search_count++;
			return root->morseCode;
		}
		else if(key < root->ascii){
			search_count++;
			return BST_search(root->left, key);
		}
		else return BST_search(root->right, key);			
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

int BST_factor(tNode *a){
	return(BST_height(a->left) - BST_height(a->right));
}

/* Retorna se a arvore eh AVL */
int isAVL(tNode* root){
	int leftHeight, rightHeight;
	if(root){
		/* Calcula altura da subarvore esquerda */
		leftHeight = BST_height(root->left);
		/* Calcula altura da subarvore direita */
		rightHeight = BST_height(root->right);

		/* Condicao para ser AVL:
		   Modulo da diferenca entre altura da subarvore esquerda e direita
		   tem que ser menor que 2, e subarvore esquerda direita tambem
		   tem que ser AVL. */
		return ((leftHeight - rightHeight < 2) &&
			(rightHeight - leftHeight < 2) &&
			isAVL(root->left) &&
			isAVL(root->right));
	} else return 1;
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
	else insert = &BST_insert;

	/* Inicializa a arvore */
	tNode* newTree = BST_create();

	table = fopen(filename, "r");  
	if(table == NULL){
		printf("Erro ao abrir o arquivo %s.", filename);
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
	clock_t start, end, elapsed; //para contar o tempo

	FILE *input_stream, *output_stream;

	int i, char_ascii;

	char *word,
             line[BUFFERSIZE],
	     *morse_found,
	     delimiters[] = {" 0123456789,.&*%\?!;/-'@\"$#=><()][}{:\r\n\t"};

	/* Decidir qual implementacao */
	tNode* morseTable = tree_constructor("TabelaMorse.txt", implem_flag);
	
	input_stream = fopen(input_file, "r");
	if (input_stream == NULL){
		printf ("Erro ao abrir o arquivo %s", input_file);
		return 1;
	} else {
		output_stream = fopen(output_file, "w");
		if(!output_stream){
			printf("Erro ao abrir o arquivo %s.\n", output_file);
			fclose(input_stream);
			return 1;
		} else { /* TODO: jogar pra dentro do else e retornar 0 */ 
			start = clock();
			/* Busca linha de texto */
			while(fgets(line, BUFFERSIZE, input_stream)){
				/* Busca palavra */
				word = strtok(line, delimiters);
				while(word != NULL){
					/* Recebe palavra */
					/* Percorre cada letra da palavra e imprime no arquivo o codigo Morse */
					for(i = 0; word[i] != '\0'; i++){
						/* Converte cada ASCII para maiusculo */
						char_ascii = (int)toupper(word[i]);
						/* Busca o ponteiro para a string que contem o codigo Morse
						   para a letra informada */
						morse_found = BST_search(morseTable, char_ascii);
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
			printf("*-------RELATORIO-------*\n");
			printf("* Implementacao utilizada: ");
			if(implem_flag) printf("AVL\n");
			else printf("ABP\n");
			printf("* Teste para AVL: ");
			if(isAVL(morseTable)) printf("TRUE\n");
			else printf("FALSE\n");
			printf("* Altura da arvore utilizada: %d\n", BST_height(morseTable));
			printf("* Comparacoes realizadas em consultas: %d\n", search_count);
			printf("* Caracteres convertidos para Morse: %d\n", char_count);
			printf("* O tempo gasto no processamento do arquivo %s foi de %ld ms\n", input_file, elapsed);
			printf("* Arquivo %s gerado com sucesso.\n", output_file);
		}
	}
	BST_delete(morseTable);
	fclose(input_stream);
	fclose(output_stream);
	return 0;
}

int main(int argc, char *argv[]){
	setlocale(LC_ALL,""); 
	if(argc != 4){
		printf("* Numero incorreto de argumentos.\nUSO: <programa> tabelamorse.txt entrada.txt saida.txt\n");
		return 1;
	} else txtToMorse(argv[1], argv[2], argv[3], AVL);
}
