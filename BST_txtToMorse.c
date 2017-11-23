/* Implementacao do conversor em ABP */
/* Programa principal que abre os arquivos fonte e destino,
   constroi a ABP, e executa a conversao */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>

#include "BST_constructor.c"

#define BUFFER_SIZE 256 
#define MORSEWORD 256 

/* Exemplo de uso dos argumentos para main O programa lê um arquivo texto como entrada e gera um arquivo como saída com o conteúdo do arquivo de entrada convertido para letras maiúsculas
Para chamar, digite "exemplo entrada.txt saida.txt" */


int main(int argc, char *argv[]) //argc conta o número de parâmetros e argv armazena as strings correspondentes aos parâmentros digitados
{
	setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados
	clock_t start, end, elapsed; //para contar o tempo

	FILE * entrada;
	FILE * saida;

	int i, char_ascii;

	char *palavra,
             linha[BUFFERSIZE],
             inMorse_word[MORSEWORD]; // linhas a serem lidas do arquivo
	char separador[]= {" 0123456789,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

	tNode* morseTable = BST_constructor("TabelaMorse.txt");

	if (argc!=3){
		printf ("Número incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
		return 1;
	} else {
		entrada = fopen (argv[1], "r"); // abre o arquivo para leitura -- argv[1] é o primeiro parâmetro após o nome do arquivo.
		if (entrada == NULL){
			printf ("Erro ao abrir o arquivo %s",argv[1]);
			return 1;
		} else {
			saida = fopen (argv[2], "w"); // abre o arquivo para saida -- argv[2] é o segundo parâmetro após o nome do arquivo.
			start=clock(); //inicia a contagem do tempo;
			//percorre todo o arquivo lendo linha por linha
			while(fgets(linha,BUFFERSIZE,entrada)){
				palavra = strtok(linha, separador);
				while(palavra != NULL){
					/* Recebe palavra */
					i = 0;
					while(palavra[i] != '\0'){
						char_ascii = (int)toupper(palavra[i]);
						printf("char: %c - ascii: %d\n morse: %s\n", toupper(palavra[i]), char_ascii, BST_search(morseTable, char_ascii));
						fprintf(saida,"%s ", BST_search(morseTable, char_ascii));
						i++;
					}	
					fprintf(saida, "/");
					/* Gera nova palavra */
					palavra = strtok (NULL, separador);
				}
			}
			end=clock(); //lê o tempo final
			elapsed = 1000 * (end - start) / (CLOCKS_PER_SEC); //calcula o tempo decorrido em milissegundos
			printf("\nO tempo gasto no processamento do arquivo %s foi de %ld ms\n",argv[1],elapsed);
			printf("\nArquivo %s gerado com sucesso.\n",argv[2]);
		}
		fclose (entrada); //fecha os arquivos
		fclose (saida);
		return 0;
	}
}
