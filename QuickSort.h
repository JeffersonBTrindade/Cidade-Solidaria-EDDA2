#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int quickSort (FILE* dat){
	//int* CNPJ;
	int i;
	//CNPJ = (int *) malloc(900 * sizeof(int));
	
	char buffer[1024];
	char aux[] = "";
	int row = 0;
	int column = 0;
	while(fgets(buffer, 1024, dat)){
        //column = 0;
        //row++;
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
		printf("\n\n%c", aux[0]);

		
        
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
