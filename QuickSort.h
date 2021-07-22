#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
} RegistroAUX;

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
