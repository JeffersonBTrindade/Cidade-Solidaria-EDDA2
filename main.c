#include "QuickSort.h"
#include "converter_csv_para_dat.h"
#include <stdio.h>
#include <locale.h>

// separar este programa em um módulo chamado: ordenar_dat_por_cpf.h

int main () {
	setlocale(LC_ALL, "Portuguese");
	// abre os arquivos
	/*FILE* fp = fopen("OSC.csv", "r");
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
	
	conversion(fp, dat);*/
	
	// abre o dat para leitura
	
	FILE* sortDat = fopen("OSC.dat", "r");
	
	if (!sortDat) {
        printf("Unable to read file.\n");
        return 1;
    }
    
    quickSort(sortDat);
    
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
