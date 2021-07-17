#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int quickSort (FILE* dat){
	//int* CNPJ;
	//CNPJ = (int *) malloc(900 * sizeof(int));
	
	char buffer[1024];
	int aux[100];
	int row = 0;
	int i = 0, j = 0;
	int column = 0;
	int valor;
	char valueStr[20];
	while(fgets(buffer, 1024, dat)){
        //column = 0;
        //row++;
        char* value = strtok(buffer, ";");
        value = strtok(NULL, ";");
        for (j = 0; j < 20; j++){
        	valueStr[j] = value[j];
		}
        valor = atoi(valueStr);
        printf("%s", valueStr);
        //fputs(valueStr, stdout);
        printf("\n%i\n\n", valor);
        aux[i] = valor;
        //strcpy(aux, value);
        //fputs(aux, stdout);
        i++;
        
        /*
        char* value = strtok(buffer, "\n");
        
        while(value)
        {
        	strcpy(aux, value);
        	//fputs(value, stdout);
        	
        	//printf("\n\n%c", aux[0]);
        	value = strtok(NULL, "\n");
        	
        	//fputs(value, stdout);
		}
		fputs(aux, stdout);
}
		printf("\n\n%c", aux[0]);*/

		
        
         /*
        while (value) {
        	if (column == 1){
        		strcpy(aux, value);
        		i = (int) aux[0];
        		printf("%c\n", aux[0]);
			}
			value = strtok(NULL, ";");
			column++;
		}*/

}
/*
for (i = 0; i < 100; i++){
	printf("%i\n", aux[i]);
}*/
}
		
	
	
	
	/*
	fread (linha, sizeof(linha), 1, dat);
	
	for (i = 0; i < 1024; i++)
		printf("%c", linha[i]);
}

int partition(int *array, int start, int pivot) 
{
	float aux;
	int i; 
	int bigger = start;
	
	for (i = start; i < pivot; i++) {
		if (array[i] < array[pivot]) {
			aux = array[bigger];
			array[bigger] = array[i];
			array[i] = aux;
			bigger++;
		}
	}
	aux = array[bigger];
	array[bigger] = array[pivot];
	array[pivot] = aux;
	return bigger;
}*/
