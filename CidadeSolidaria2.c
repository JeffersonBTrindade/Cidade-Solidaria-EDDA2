/*
  Programa: Cidade Solidï¿½ria
  Data....: 31/05/2021
*/

/*Bibliotecas*/
#include <string.h>
#include <memory.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "lib.h"

     
/*Protï¿½tipos*/
int  MenuPrincipal (void);
void MenuEntidades (void);
void MenuAssitidos (void);
void MenuDonativos (void);
void MenuAtendimento (void);
int buscaBinaria(registro_osc *v, char *cnpj, char* email, int ini, int fim);
void Login (void);
void Sobre (void);
void ordenaOscCNPJDAT(void);
long int findSize(char file_name[]) ;
int quickSort(registro_osc *vetorRegistro, int start, int end); 
int partition(registro_osc *vetorRegistro, int start, int pivot) ;
void mostraCNPJ (registro_osc  *v, int tam);

/* Variï¿½veis globais */
registro_osc 	informacao;
FILE      		*CSV;
FILE      		*DAT;
int       		i, cont=0;

/* Funï¿½ï¿½es */
int partition(registro_osc *vetorRegistro, int start, int pivot) 
{
	registro_osc aux;
	int i; 
	int bigger = start;
	
	for (i = start; i < pivot; i++) {
		if ( atoll(vetorRegistro[i].cnpj) < atoll(vetorRegistro[pivot].cnpj) )  {
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

int quickSort(registro_osc *vetorRegistro, int start, int end) 
{
	int pivot;
	if (start < end) {
		pivot = partition(vetorRegistro, start, end);
		quickSort(vetorRegistro, start, pivot-1);
		quickSort(vetorRegistro, pivot+1, end);
	}
}

int buscaBinaria(registro_osc *v, char *cnpj, char* email, int ini, int fim){
	int novoIni = ini;
	int novoFim = fim;
	int meio;
	
	meio = (ini + fim)/2;
	if (atoll(v[meio].cnpj) == atoll(cnpj)){
		if (strcmp(v[meio].email, email) == 0) {
			return 1;
		}
		return 0;
	}
		
	if (atoll(v[meio].cnpj) > atoll(cnpj))
		novoFim = meio - 1;
	if (atoll(v[meio].cnpj) < atoll(cnpj))
		novoIni = meio + 1;
	if (ini > fim)
		return 0;
	
	buscaBinaria(v, cnpj, email, novoIni, novoFim);
}


long int findSize(char file_name[]) 
{ 
    long int res;
    //Abre o arquivo para leitura
    FILE* fp = fopen(file_name, "r"); 
    //Verifica se o arquivo existe
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
    //"Salta" para o fim do arquivo 
    fseek(fp, 0L, SEEK_END); 
    //Calcula o tamanho do arquivo
    res = ftell(fp); 
    //Fecha o arquivo
    fclose(fp); 
    return res; 
}

void ordenaOscCNPJDAT(void)
{
   FILE * ArqDAT;
   registro_osc  *vet;   
   int  ind=0;
   
   // Alocar dinamicamente a memï¿½ria para o vetor (vet) de registros (registro_osc)
   vet = (registro_osc  *) malloc (findSize("OSC.DAT"));
   if ( vet==NULL )
   {
   	  	printf ("\nNï¿½o foi possï¿½vel alocar %ld bytes em memï¿½ria", findSize("OSC.DAT") );
   	  	getch();
   	  	exit(0);
   }
   //debug
   //printf ("\n OSC.DAT tem %ld bytes", findSize("OSC.DAT") );    getch();

   // Copiar o conteï¿½do do OSC.DAT para a memï¿½ria alocada   
   // abre o arquivo OSC.DAT para leitura (e depois transportï¿½-lo para memï¿½ria) 
   ArqDAT = fopen("OSC.DAT", "r");	
   if (  ArqDAT==NULL )
   {
      printf ("\nErro o ler OSC.DAT!");
	  getch();
	  exit(0);		
   }
   while (!feof(ArqDAT))
   {
   	 //Lï¿½ do arquivo para o vetor
   	 fread (&vet[ind], sizeof(registro_osc), 1, ArqDAT);
   	 if (!feof(ArqDAT))
   	    ind++;
   }
   fclose(ArqDAT);
   //debug
   //printf ("\nLeu %i registros", ind ); getch();
   
   //Ordena o vetor pelo CNPJ
   quickSort(vet, 0, ind-1) ;
   
   // Mostra os CNPJs ordenados
   mostraCNPJ(vet, ind);
}

void mostraCNPJ (registro_osc  *v, int tam)
{
	FILE *DAT;
	DAT = fopen("OSC.DAT", "w");

	if (!DAT)
    {
      printf ("\nErro o ler OSC.DAT!");
	  getch();
	  exit(0);		
    }

	int i = 0;
	for (i = 0; i < tam; i++) {
		fwrite (&v[i], sizeof(v[i]), 1, DAT);
	}
}

void  errolerCSV (void)
{
	system ("cls");
	printf ("\n  ERRO AO LER ARQUIVO PRODUTOS.CSV  ");
	getch();
	exit(0);
}

void errogravarDAT (void)
{
	system ("cls");
	printf ("\n  ERRO AO GRAVAR NO ARQUIVO PRODUTOS.DAT  ");
	getch();
	exit(0);
}

/* Funï¿½ï¿½es para converter */
void  converte (void)
{
	char  cestasaux [10];
	int   linha=1;
	int   qtdRegistros;
	char  ch;
	CSV = fopen ("OSC.CSV", "r");
	if (CSV==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO 'OSC.CSV'.  ");
		getch();
		exit(0);
	}

	DAT = fopen ("OSC.DAT", "w");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO CRIAR ARQUIVO 'OSC.DAT'.  ");
		getch();
		exit(0);
	}

	/*----- CONVERSï¿½O DE CSV PARA DAT ------*/
	qtdRegistros=0;
	while ( !feof(CSV) )
	{
		if(linha ==1)   /*pular primeira linha (tira cabeï¿½alho)*/
		{
			do
			{
				ch = fgetc(CSV);
			}
			while(ch != '\n');
		}
	    /* lï¿½ o CSV */
		/* Trata campos do CSV */
        i=0;
        do
		{
		  informacao.entidade[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.entidade[i++] != ';' );
	    informacao.entidade[--i] = '\0';
        
        i=0;
		do
		{
		  informacao.cnpj[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.cnpj[i++] != ';' );
	    informacao.cnpj[--i] = '\0';

		i=0;
    	do
		{
		  informacao.email[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.email[i++] != ';' );
	    informacao.email[--i] = '\0';

		i=0;
        do
		{
		  informacao.fone[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.fone[i++] != ';' );
	    informacao.fone[--i] = '\0';

		i=0;
    	do
		{
		  informacao.comunidade[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.comunidade[i++] != ';');
	    informacao.comunidade[--i] = '\0';
        
        i=0;
        do
		{
		  informacao.enderdoar[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.enderdoar[i++] != ';');
	    informacao.enderdoar[--i] = '\0';

	    i=0;		
        do
		{
		  informacao.tipoassentamento[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.tipoassentamento[i++] != ';');
	    informacao.tipoassentamento[--i] = '\0';

		i=0;
    	do
		{
		  informacao.subprefeitura[i] = fgetc(CSV);
		  if ( ferror(CSV) ) errolerCSV();
        }
        while ( informacao.subprefeitura[i++] != ';');
	    informacao.subprefeitura[--i] = '\0';

		i=0;
        do
		{
		   ch = fgetc(CSV);
	   	   if ( ch != '\n' && ch != EOF)
	    	cestasaux[i++] = ch;
		   else break; 
        }
	    while ( ch != '\n' || ch != EOF );
	    cestasaux[i] = '\0';
	    informacao.qtdcestas = atoi(cestasaux);

		qtdRegistros++; /* Contabiliza um registro convertido */

		/* Grava no DAT */
	    //grava registro montado no Dat
        if ( fwrite (&informacao, sizeof(informacao), 1, DAT) != 1 ) 
			errogravarDAT();
	    linha++;
	}
	printf ("\n[%i] registro(s) convertido(s) com sucesso!!", qtdRegistros);
	fclose (CSV);
	fclose (DAT);
	getch();
}

void mostraDAT (void)
{
    FILE * REL;
    REL = fopen ("RELOSC.TXT", "w");
    if (REL == NULL)
    {
		system ("cls");
		printf ("\n  ERRO AO CRIAR ARQUIVO RELOSC.TXT");
		getch();
		exit(0);
	}
	DAT = fopen ("OSC.DAT", "r");
	if (DAT==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO OSC.DAT  ");
		getch();
		exit(0);
	}
	
	printf ("\n----- CONTEï¿½DO DE OSC.DAT ------");
	printf ("\nENTIDADE		CNPJ		E-MAIL		TELEFONE		COMUNIDADE		ENDEREï¿½O DOAï¿½ï¿½O		TIPO ASSENTAMENTO		SUBPREFEITURA		QTD CESTAS");
	printf ("\n-------------------------------------");
	
	fprintf (REL, "\n----- CONTEï¿½DO DE OSC.DAT ------");
	fprintf (REL, "\nENTIDADE		CNPJ		E-MAIL		TELEFONE		COMUNIDADE		ENDEREï¿½O DOAï¿½ï¿½O		TIPO ASSENTAMENTO		SUBPREFEITURA		QTD CESTAS");
	fprintf (REL, "\n-------------------------------------");
	
	while ( !feof(DAT) )
	{
		/* lï¿½ o DAT */
		fread (&informacao, sizeof(informacao), 1, DAT);		
		if ( ferror(DAT) )
		{
			system ("cls");
			printf ("\n  ERRO AO LER ARQUIVO PRODUTOS.DAT  ");
			getch();
			exit(0);
		}
		if (!feof(DAT)) 	/* Mostra registro lido */
		{
			printf  ("\n%s;%s;%s;%s;%s;%s;%s;%s;%d;\n\n", informacao.entidade, informacao.cnpj,informacao.email,informacao.fone,informacao.comunidade,informacao.enderdoar,informacao.tipoassentamento,informacao.subprefeitura,informacao.qtdcestas);		
			fprintf (REL,"\n%s;%s;%s;%s;%s;%s;%s;%s;%d;\n\n", informacao.entidade, informacao.cnpj,informacao.email,informacao.fone,informacao.comunidade,informacao.enderdoar,informacao.tipoassentamento,informacao.subprefeitura,informacao.qtdcestas);		
		}
		getch();
	}
	fclose (DAT);
	fclose (REL);
	getch();
	system ("notepad RELOSC.TXT ");
}



/*Programa principal*/
int main(){ 

    /*Add acentos e ï¿½*/
	setlocale (LC_ALL, ""); 
	/*Tamanho da Janela*/
	//system("mode con:cols=75 lines=30");
	
	/*Declaraï¿½ï¿½o de variï¿½veis*/
    int opcao; 
	Login();
	/*Captura de opï¿½ï¿½o no MenuPrincipal*/
    do{ 
        system ("cls"); 
        opcao = MenuPrincipal(); 

            switch (opcao) { 
                case 1: 
                    MenuEntidades(); 
                break; 
                case 2: 
                    MenuAssistidos(); 
                break; 
                case 3: 
                    MenuDonativos();
				break; 
				case 4: 
                    MenuAtendimento();
                break;  
                case 5:
                    Sobre();
                break;
                case 6:
                    converte();
                break;
                case 7:
                    mostraDAT();
                break;
                case 8:
                    ordenaOscCNPJDAT();
                break;                
                case 0: 
                    printf ("Saindo....\n"); 
                    exit(0); 
                default: 
                
                    /*cores do fundo e texto*/
					system("color 0C");
					/*system("cls");*/ 
					printf ("\n\t\tOPï¿½ï¿½O INVï¿½LIDA!!!\n\n"); 
                    printf ("Tecle [Enter] para continuar..."); 
                    getchar(); 
                } 
    }while(1); 

return 0; 
}


/*Funï¿½ï¿½o MenuPrincipal*/
int MenuPrincipal (void){ 

	/*cores
	0 - Preto
	1 - Azul	2 - Verde	3 - Verde-ï¿½gua	4 - Vermelho	5 - Roxo	6 - Amarelo
	7 - Branco	8 - Cinza	9 - Azul claro	A - Verde Claro	B - Verde-ï¿½gua claro
	C - Vermelho Claro	D - Lilï¿½s	E - Amarelo Claro	F - Branco Brilhante*/
	
	/*cores do fundo e texto*/
    system("color B0");
    
	/* Declaraï¿½ï¿½o de variï¿½veis*/
    int opc;
	
    printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDï¿½RIA\n"); 
    printf ("----------------------------------------------------------\n\n");
    printf ("                   << MENU PRINCIPAL >>\n\n"); 
    printf ("      1 - Cadastro de entidades da sociedade civil\n"); 
    printf ("      2 - Cadastro de assistidos\n"); 
    printf ("      3 - Cadastro de donativos\n"); 
    printf ("      4 - Atendimento\n");
    printf ("      5 - Sobre este sistema\n");
    printf ("      6 - Converter CSV para DAT\n");
    printf ("      7 - Mostar conteï¿½do do DAT\n");
    printf ("      8 - Ordena OSC.DAT pelo CNPJ\n");
    printf ("      0 - Sair do Programa\n\n"); 
    printf ("----------------------------------------------------------\n");
    printf ("Digite a opï¿½ï¿½o desejada e tecle [Enter]: ");
    scanf ("%d", &opc); 
    printf ("----------------------------------------------------------\n");
    getchar(); 

return opc; 
}

/* Funï¿½ï¿½o MenuEntidades */
void MenuEntidades (void){ 

	/*cores do fundo e texto*/
    system("color 0B");

      FILE *arquivo; 

      system("cls"); 
	
	printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDï¿½RIA\n"); 
    printf ("----------------------------------------------------------\n\n");
	printf ("      << CADASTRO DE ENTIDADES DA SOCIEDADE CIVIL >>\n\n"); 
    printf ("      1 - Cadastro de nova entidade\n"); 
    printf ("      2 - Consulta entidades cadastradas\n"); 
    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n"); 
    printf ("----------------------------------------------------------\n");
    /*printf ("Digite a opï¿½ï¿½o desejada e tecle [Enter]: \n\n\n");*/
    printf ("Tecle [Enter] para voltar ao MENU PRINCIPAL...");
	getchar(); 


}

/*Funï¿½ï¿½o MenuAssitidos */
MenuAssistidos (void){ 
	
	/*cores do fundo e texto*/
    system("color F4");
	
    system("cls"); 
	printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDï¿½RIA\n"); 
    printf ("----------------------------------------------------------\n\n");
	printf ("	  << CADASTRO CADASTRO DE ASSISTIDOS >>\n\n"); 
    printf ("      1 - Cadastro de novo assistido\n"); 
    printf ("      2 - Cadastro default\n");
    printf ("      3 - Consulta assistidos cadastrados\n"); 
    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n"); 
    printf ("----------------------------------------------------------\n");
    /*printf ("Digite a opï¿½ï¿½o desejada e tecle [Enter]: \n\n\n");*/
    printf ("Tecle [Enter] para voltar ao MENU PRINCIPAL...");
    getchar(); 
} 

/*Funï¿½ï¿½o MenuDonativos */
void MenuDonativos (void){ 
	
	/*cores do fundo e texto*/
    system("color 0E");
	
	system("cls"); 
	printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDï¿½RIA\n"); 
    printf ("----------------------------------------------------------\n\n");
	printf ("	  << CADASTRO CADASTRO DE DONATIVOS >>\n\n"); 
    printf ("      1 - Cadastro de novo donativo\n"); 
    printf ("      2 - Consulta donativos cadastrados\n"); 
    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n"); 
    printf ("----------------------------------------------------------\n");
    /*printf ("Digite a opï¿½ï¿½o desejada e tecle [Enter]: \n\n\n");*/
    printf ("Tecle [Enter] para voltar ao MENU PRINCIPAL...");
    getchar(); 
 
} 

/*Funï¿½ï¿½o MenuAtendimento */
void MenuAtendimento (void){ 

	/*cores do fundo e texto*/
    system("color F2");

	system("cls"); 
	printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDï¿½RIA\n"); 
    printf ("----------------------------------------------------------\n\n");
	printf ("		      << ATENDIMENTO >>\n\n"); 
    printf ("   Nome: xxxxxxxxxx	             Ordem: [0000/0000]\n\n"); 
    printf ("   CPF:  00000000000000\n\n"); 
 /* printf ("      1 - Cesta entregue\n\n");
    printf ("      2 - Cesta nï¿½o entregue\n\n");
    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n"); */
    printf ("----------------------------------------------------------\n");
 /* printf ("Digite a opï¿½ï¿½o desejada e tecle [Enter]: \n\n\n");*/
    printf ("Tecle [Enter] para voltar ao MENU PRINCIPAL...");
    getchar(); 

}

/* Funï¿½ï¿½o Sobre Sistema */
void Sobre (void){
   
    /*cores do fundo e texto*/
    system("color 10");
    
	system ("cls");
    printf ("---------------------------------------------------------------------------\n");
	printf ("			        SOBRE O SISTEMA   \n");
	printf ("---------------------------------------------------------------------------\n\n");
	system("color A0");
	printf ("  IFSP - INSTITUTO FEDERAL DE EDUCAï¿½ï¿½O, CIï¿½NCIA E TECNOLOGIA DE Sï¿½O PAULO\n\n");
	printf ("     TECNOLOGIA EM ANï¿½LISE E DESENVOLVIMENTO DE SISTEMAS - 2ï¿½ SEMESTRE\n\n\n\n");
    printf ("PROJETO DA DISCIPLINA ESTRUTURA DE DADOS: Aï¿½ï¿½o Social Cidade Solidï¿½ria\n");
	printf ("\n");
    printf ("PROFESSORA: Eurides Balbino\n\n");
	printf ("EQUIPE DE DESENVOLVIMENTO:\n");
    printf ("Igor Kazuhiko       Matr.: 3061973\n");
	printf ("Rivaildo Ferreira   Matr.: 3063968\n\n");
	printf ("---------------------------------------------------------------------------\n\n");
    printf ("Tecle [Enter] para voltar ao MENU PRINCIPAL...");
    getchar();
    
}

void Login (void) {
	char *cnpj;
	cnpj = (char *) malloc(sizeof(char) * 15);
	char *email;
	email = (char *) malloc(sizeof(char) * 101);
	FILE * ArqDAT;	
    registro_osc  *vet;   
    int  ind=0;

	printf("---------------------------------------------\n");
	printf("		INFORME LOGIN			\n");
	printf("---------------------------------------------\n");
	printf("Informe CNPJ: ");
	scanf("%s", cnpj);
	//gets(cnpj);
	printf("\n\nInforme e-mail: ");
	//gets(email);
	scanf("%s", email);
	printf("daqui naõa passa");

    vet = (registro_osc  *) malloc (findSize("OSC.DAT"));
   if ( vet==NULL )
   {
   	  	printf ("\nNï¿½o foi possï¿½vel alocar %ld bytes em memï¿½ria", findSize("OSC.DAT") );
   	  	getch();
  	  	exit(0);
   }
 
   ArqDAT = fopen("OSC.DAT", "r");	
   if (  ArqDAT==NULL )
   {
      printf ("\nErro o ler OSC.DAT!");
	  getch();
	  exit(0);		
   }

   while (!feof(ArqDAT))
   {
   	 fread (&vet[ind], sizeof(registro_osc), 1, ArqDAT);
   	 if (!feof(ArqDAT))
   	    ind++;
   }
    fclose(ArqDAT);

	printf("%i", buscaBinaria(vet, cnpj, email, 0, ind));
	getch();
}
