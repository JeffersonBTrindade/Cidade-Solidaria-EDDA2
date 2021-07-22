#include "converter_csv_para_dat.h"
#include "ler_linhas_dat.h"
//#include "QuickSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct {
	char ENTIDADE[200];
	long long int CNPJ;
	char EMAIL[50];
	char TELEFONE[15];
	char COMUNIDADE[50];
	char ENDERECO[150];
	char ASSENTAMENTO[50];
	char SUBPREFEITURA[50];
	char QNTCESTAS[20];
} Registro;

// separar este programa em um módulo chamado: ordenar_dat_por_cpf.h
int quickSort(Registro *vetorRegistro, int start, int end); 

int partition(Registro *vetorRegistro, int start, int pivot) 
{
	Registro aux;
	int i; 
	int bigger = start;
	
	for (i = start; i < pivot; i++) {
		if (vetorRegistro[i].CNPJ < vetorRegistro[pivot].CNPJ) {
			aux = vetorRegistro[bigger];
			vetorRegistro[bigger] = vetorRegistro[i];
			vetorRegistro[i] = aux;
			bigger++;
		}
	}
	aux = vetorRegistro[bigger];
	vetorRegistro[bigger] = vetorRegistro[pivot];
	vetorRegistro[pivot] = aux;
	return bigger;
}

int quickSort(Registro *vetorRegistro, int start, int end) 
{
	int pivot;
	
	if (start < end) {
		pivot = partition(vetorRegistro, start, end);
		quickSort(vetorRegistro, start, pivot-1);
		quickSort(vetorRegistro, pivot+1, end);
	}
	
}

int main () {
	char line[150];
    int index = 0;
    char buffer[1024];
    int column;
	setlocale(LC_ALL, "Portuguese");
	
//	 abre os arquivos
//	FILE* fp = fopen("OSC.csv", "r");
//	FILE* dat = fopen("OSC.dat", "w");
//	
//	if (!dat) {
//        printf("Unable to create file.\n");
//        return 1;
//    }
//	if (!fp) {
//		printf("Can't open file\n");
//		return 1;
//	}

//  invoca a função de conversão do csv para dat, passando como parâmetros os files

//	conversion(fp, dat);


	
	// abre o dat para leitura
	
	FILE* sla = fopen("OSC.dat", "r");
//	
	if (!sla) {
        printf("Unable to read file.\n");
        return 1;
    }
    
    //printf("Lines: %i\n\n", getFileLines(sla));
    int qntlinhas = getFileLines(sla);
    //printf("%i", qntlinhas);
    //char c;
    fclose(sla);
    
    FILE* readDat = fopen("OSC.dat", "r");

	char array[] = "";
	Registro vetor[qntlinhas];
	int i = 0;
/*	for (i; i < 70; i++) {
		strcpy(vetor[i].ENTIDADE, "");
		strcpy(vetor[i].CNPJ, "");
		strcpy(vetor[i].EMAIL, "");
		strcpy(vetor[i].TELEFONE, "");
		strcpy(vetor[i].COMUNIDADE, "");
		strcpy(vetor[i].ENDERECO, "");
		strcpy(vetor[i].ASSENTAMENTO, "");
		strcpy(vetor[i].SUBPREFEITURA, "");
		strcpy(vetor[i].QNTCESTAS, "");
	}*/
    while (fgets(buffer, 1024, readDat)) {
    	column = 0;
		char* value = strtok(buffer, ";");
		while (value) {
			//printf("%s\n\n", value);
			if (column == 0) {
				strcpy(vetor[index].ENTIDADE, value);
			}
			
			if (column == 1) {
				vetor[index].CNPJ = atoll(value);
				//strcpy(vetor[index].CNPJ, value);
			}
			
			if (column == 2) {
				strcpy(vetor[index].EMAIL, value);			
			}
			
			if (column == 3) {
				strcpy(vetor[index].TELEFONE, value);
			}
			
			if (column == 4) {
				strcpy(vetor[index].COMUNIDADE, value);
			}
			
			if (column == 5) {
				strcpy(vetor[index].ENDERECO, value);
			}
			
			if (column == 6) {
				strcpy(vetor[index].ASSENTAMENTO, value);
			}
			
			if (column == 7) {
				strcpy(vetor[index].SUBPREFEITURA, value);
			}
			
			if (column == 8) {
				strcpy(vetor[index].QNTCESTAS, value);
				index++;	
			}
			
			value = strtok(NULL, ";");
			column++;
        }
	}
	
	int a = 0;
	for(a; a < qntlinhas; a++) {
		printf("Entidade: %lld\n", vetor[a].CNPJ);
	}
	
	
	quickSort(vetor, 0, (qntlinhas-1));
	
	printf("\n\n\n");
	
	for(a; a < qntlinhas; a++) {
		printf("Entidade: %lld\n", vetor[a].CNPJ);
	}
	/*printf("\n\n\n");
	printf("Entidade: %s", vetor[0].ENTIDADE);
	printf("CNPJ: %s", vetor[0].CNPJ);
	printf("email: %s", vetor[0].EMAIL);
	printf("telefone: %s", vetor[0].TELEFONE);
	printf("comunidade: %s", vetor[0].COMUNIDADE);
	printf("endereco: %s", vetor[0].ENDERECO);
	printf("asentamenteo: %s", vetor[0].ASSENTAMENTO);
	printf("sub: %s", vetor[0].SUBPREFEITURA);
	printf("cestas: %s", vetor[0].QNTCESTAS);*/
	
    // salvo o arquivo em um array deve-se usar o quick sort pelo cpf, 
	// que deve ser lido como numero (?) para ordenação
    fclose(readDat);
	return 0;
}



