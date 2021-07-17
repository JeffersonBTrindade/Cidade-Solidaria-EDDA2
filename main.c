#include "QuickSort.h"
#include "converter_csv_para_dat.h"
#include <stdio.h>
#include <locale.h>

// separar este programa em um módulo chamado: ordenar_dat_por_cpf.h

typedef struct {
	char ENTIDADE[150];
	long long int CNPJ;
	char EMAIL[50];
	char TELEFONE[11];
	char COMUNIDADE[30];
	char ENDERECO[100];
	char ASSENTAMENTO[20];
	char SUBPREFEITURA[25];
	int QNTCESTAS;
} Registro;

int main () {
	FILE *fp;
    int countLines = 0;
    char c;
  
	setlocale(LC_ALL, "Portuguese");
	// abre os arquivos
	fp = fopen("OSC.csv", "r");
	FILE* dat = fopen("OSC.dat", "w");
	
	if (!dat) {
        printf("Unable to create file.\n");
        return 1;
    }
	if (!fp) {
		printf("Can't open file\n");
		return 1;
	}
	
	// invoca a função de conversão do csv para dat, passando como parâmetros os files
	conversion(fp, dat);
	
	//fp = fopen("OSC.dat", "r");
  
    if (fp == NULL)
    {
        printf("Could not open file %s", "OSC.dat");
        return 0;
    }
  
    for (c = getc(dat); c != EOF; c = getc(dat))
        if (c == '\n') // Increment count if this character is newline
            countLines = countLines + 1;
  
  	//fclose(fp);
  
  	//fp = fopen("OSC.dat", "wr");
    Registro arrayRegistros[countLines];
	
	char buffer[1024];
	int index = 0;
	int column = 0;
	while (fgets(buffer, 1024, dat)) {
        column = 0;
        char* value = strtok(buffer, ";");
        while (value) {
          	if (column == 0){
          		strcpy(arrayRegistros[index].ENTIDADE, value);
			}
			printf("%s\n\n", value);
			printf("%s", arrayRegistros[index].ENTIDADE);
			value = strtok(NULL, ";");
            column++;
        }
        index++;
    }
    //fclose(fp);

	// abre o dat para escrita
	/*FILE* sortDat = fopen("OSC.dat", "w");
	
	if (!sortDat) {
        printf("Unable to read file.\n");
        return 1;
    }
    
    char buffer[1024];
	char aux[] = "";
	int column = 0;
	while (fgets(buffer, 1024, sortDat)) {
        column = 0;
        char* value = strtok(buffer, ";");
        while (value) {
          	if (column = 0){
          		
			}
				
			value = strtok(NULL, ";");
            column++;
        }
    }*/
    
    
    
    // com isso é possível imprimir o arquivo linha por linha, mas não consegui
    // ler o arquivo e salvar dentro de um array
    /*
    char chunk[128]; // nota: deve-se usar alocação dinâmica
    
    while(fgets(chunk, sizeof(chunk), readDat) != NULL) {
        fputs(chunk, stdout);
        fputs("\n", stdout);  // marcador para observar que a string em chunk acabou
    }
    */
    // depois deve-se usar EOF (end of file) ?
    
    // salvo o arquivo em um array deve-se usar o quick sort pelo cpf, 
	// que deve ser lido como numero (?) para ordenação
    
	return 0;
}
