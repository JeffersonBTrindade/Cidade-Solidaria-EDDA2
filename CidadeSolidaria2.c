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
#include <stdbool.h>
#include "lib.h"

int partition(registro_osc *vetorRegistro, int start, int pivot);
int quickSort(registro_osc *vetorRegistro, int start, int end); 
int buscaBinaria(registro_osc *v, char *cnpj, char* email, int ini, int fim);
long int findSize(char file_name[]);
void ordenaOscCNPJDAT(void);
void escreveNoDat (registro_osc  *v, int tam);
void errolerCSV (void);
void errogravarDAT (void);
void converte (void);
void converteAssistidos (void);
void mostraDAT(void);
void CadastroEntidade(void);
void ConsultaEntidades(void);
bool ValidaCNPJ(char *cnpj);
bool tipoAssentamento(char *tipo);
bool subprefeitura(char * subprefeitura);


int  MenuPrincipal (void);
void GerenciamentoEntidades (void);
void GerenciamentoAssistidos (void);
void GerenciamentoDonativos (void);
void MenuAtendimento (void);
void MaisInformacoes (void);
void Login (void);

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
   	 fread (&vet[ind], sizeof(registro_osc), 1, ArqDAT);
   	 if (!feof(ArqDAT))
   	    ind++;
   }
   
   fclose(ArqDAT);
   //printf("\nentidade 66 antes quick: %s", vet[65].entidade);

   //Ordena o vetor pelo CNPJ
   quickSort(vet, 0, ind-1) ;
   
   //printf("\nentidade 66 quick: %s", vet[65].entidade);
   //getch();
   // Mostra os CNPJs ordenados
   escreveNoDat(vet, ind);
   
   printf("\nDados do .dat ordenados a partir de CNPJ crescente!");
   getch();
}

void escreveNoDat (registro_osc  *v, int tam)
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
	
	fclose(DAT);
}

void  errolerCSV (void)
{
	system ("cls");
	printf ("\n  ERRO AO LER ARQUIVO CSV  ");
	getch();
	exit(0);
}

void errogravarDAT (void)
{
	system ("cls");
	printf ("\n  ERRO AO GRAVAR NO ARQUIVO DAT  ");
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
	printf ("\n[%i] registro(s) convertido(s) de csv para dat com sucesso!!", qtdRegistros);
	fclose (CSV);
	fclose (DAT);
	getch();
	system("cls");
}

void  converteAssistidos (void)
{
	int a = 0;
	assistidos_osc informacaoAssitidos;
	FILE *CSVAssitidos;
	FILE *DATAssitidos;
	int   linha=1;
	int   qtdRegistros;
	char  ch;
	
	
	CSVAssitidos = fopen ("ASSISTIDOS.CSV", "r");
	if (CSVAssitidos==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO ABRIR ARQUIVO 'ASSITIDOS.CSV'.  ");
		getch();
		exit(0);
	}
	//printf("abriu csv\n"); getch();

	DATAssitidos = fopen ("ASSISTIDOS.DAT", "w");
	if (DATAssitidos==NULL)
	{
		system ("cls");
		printf ("\n  ERRO AO CRIAR ARQUIVO 'ASSITIDOS.DAT'.  ");
		getch();
		exit(0);
	}
	//printf("abriu dat\n"); getch();

	/*----- CONVERSï¿½O DE CSV PARA DAT ------*/
	qtdRegistros=0;
	while ( !feof(CSVAssitidos) )
	{
		if(linha == 1)   /*pular primeira linha (tira cabeï¿½alho)*/
		{
			//printf("entrou linha 1\n"); getch();
			do
			{
				ch = fgetc(CSVAssitidos);
			}
			while(ch != '\n');
		}
	    
		/* Trata campos do CSV */
        i=0;
        do
		{
		  informacaoAssitidos.nomeCompleto[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.nomeCompleto[i++] != ';' );
	    informacaoAssitidos.nomeCompleto[--i] = '\0';
	    //printf("pa\n"); getch();
        
        i=0;
		do
		{
		  informacaoAssitidos.dataNascimento[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.dataNascimento[i++] != ';' );
	    informacaoAssitidos.dataNascimento[--i] = '\0';

		i=0;
    	do
		{
		  informacaoAssitidos.cpf[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.cpf[i++] != ';' );
	    informacaoAssitidos.cpf[--i] = '\0';

		i=0;
        do
		{
		  informacaoAssitidos.municipio[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.municipio[i++] != ';' );
	    informacaoAssitidos.municipio[--i] = '\0';

		i=0;
    	do
		{
		  informacaoAssitidos.logradouro[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.logradouro[i++] != ';');
	    informacaoAssitidos.logradouro[--i] = '\0';
        
        i=0;
        do
		{
		  informacaoAssitidos.numeroResidencial[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.numeroResidencial[i++] != ';');
	    informacaoAssitidos.numeroResidencial[--i] = '\0';
//printf("pazao\n"); getch();

	    i=0;		
        do
		{
		  informacaoAssitidos.complemento[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.complemento[i++] != ';');
	    informacaoAssitidos.complemento[--i] = '\0';

		i=0;
    	do
		{
		  informacaoAssitidos.bairro[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.bairro[i++] != ';');
	    informacaoAssitidos.bairro[--i] = '\0';
//printf("pazao bairro\n"); getch();

		i=0;
    	do
		{
		  informacaoAssitidos.numeroTelefone[i] = fgetc(CSVAssitidos);
		  if ( ferror(CSVAssitidos) ) errolerCSV();
        }
        while ( informacaoAssitidos.numeroTelefone[i++] != ';');
	    informacaoAssitidos.numeroTelefone[--i] = '\0';
//printf("pazao tel\n"); getch();

	    i=0;
	    do
		{
		   ch = fgetc(CSVAssitidos);
	   	   if ( ch != '\n' && ch != EOF)
	    	informacaoAssitidos.possuiPet[i++] = ch;
		   else break; 
        }
	    while ( ch != '\n' || ch != EOF );
	    informacaoAssitidos.possuiPet[i] = '\0';
		
		qtdRegistros++; /* Contabiliza um registro convertido */

		/* Grava no DAT */
	    //grava registro montado no Dat
        if ( fwrite (&informacaoAssitidos, sizeof(informacaoAssitidos), 1, DATAssitidos) != 1 ) 
			errogravarDAT();
	    linha++;
	    a++;
	    printf("%i\n", a);
	}
	
	printf(" ira\n");
	printf ("\n[%i] registro(s) convertido(s) de csv para dat com sucesso (assistidos)!!", qtdRegistros);
	fclose (CSVAssitidos);
	fclose (DATAssitidos);
	getch();
	system("cls");
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

void CadastroEntidade(void) {
	FILE *dat;
	FILE *datTest;
	registro_osc *novaEntidade;
	registro_osc informacao;
	bool cnpjValido = false;
	
	novaEntidade = (registro_osc *) malloc (sizeof(registro_osc)*2);
	
	system("color 0E");
	    
	system("cls"); 
	
	printf ("----------------------------------------------------------\n");
    printf ("        CADASTRAR NOVA ENTIDADE\n"); 
    printf ("----------------------------------------------------------\n\n");
    printf ("INSIRA AS INFORMAÇÕES QUE DESEJA CADASTRAR: \n\n\n");
	
	printf("Entidade, movimento ou instituição responsável: ");
	gets(novaEntidade[0].entidade); fflush(stdin);
	
	do {
		
		printf("\nCNPJ: ");
		gets(novaEntidade[0].cnpj); fflush(stdin);	
			
	} while(!ValidaCNPJ(novaEntidade[0].cnpj));
	
	printf("\nE-mail: ");
	gets(novaEntidade[0].email); fflush(stdin);
	
	printf("\nTelefone: ");
	gets(novaEntidade[0].fone); fflush(stdin);
	
	printf("\nLocalidade para a qual se destinarão as doações (comunidade beneficiada): ");
	gets(novaEntidade[0].comunidade); fflush(stdin);
	
	printf("\nEndereço da área de destino das doações: ");
	gets(novaEntidade[0].enderdoar); fflush(stdin);
		
	printf("\nTipos de assentamento precário/grupo disponíveis (digite uma das opções abaixo):\n");
	printf("\tFavela;\n");
	printf("\tCortico;\n");
	printf("\tOcupacao;\n");
	printf("\tLoteamento;\n");
	printf("\tComunidade indigena;\n");
	printf("\tGrupo de mulheres;\n");
	printf("\tImigrantes ou Refugiados;\n");
	printf("\tCrianca e Adolescente;\n");
	printf("\tIdosos;\n");
	printf("\tMinorias etnico-raciais;\n");
	printf("\tLGBTI;\n");
	printf("\tPessoas em situação de rua;\n");
	printf("\tEgresso do sistema prisional;\n");
	printf("\tPessoa com deficiencia;\n");
	printf("\tOutros;\n");
	printf("Insira sua escolha: ");
	
	do {
		
		gets(novaEntidade[0].tipoassentamento); fflush(stdin);
				
	} while(!tipoAssentamento(novaEntidade[0].tipoassentamento));
	
	printf("\nSubprefeitura (digite uma das opções abaixo):\n");
	printf("\tAricanduva;\n");
	printf("\tButanta;\n");
	printf("\tCampo Limpo;\n");
	printf("\tCapela do Socorro;\n");
	printf("\tCasa Verde;\n");
	printf("\tCidade Ademar;\n");
	printf("\tCidade Tiradentes;\n");
	printf("\tErmelino Matarazzo;\n");
	printf("\tFreguesia do O;\n");
	printf("\tGuaianases;\n");
	printf("\tIpiranga;\n");
	printf("\tItaim Paulista;\n");
	printf("\tItaquera;\n");
	printf("\tJabaquara;\n");
	printf("\tJacana Tremembe;\n");
	printf("\tLapa;\n");
	printf("\tM'Boi Mirim;\n");
	printf("\tMooca;\n");
	printf("\tParelheiros;\n");
	printf("\tPenha;\n");
	printf("\tPerus;\n");
	printf("\tPinheiros;\n");
	printf("\tPirituba Jaragua;\n");
	printf("\tSantana Tucuruvi;\n");
	printf("\tSanto Amaro;\n");
	printf("\tSao Mateus;\n");
	printf("\tSao Miguel Paulista;\n");
	printf("\tSapopemba;\n");
	printf("\tSe;\n");
	printf("\tVila Maria vila Guilherme;\n");
	printf("\tVila Mariana;\n");
	printf("\tVila Prudente;\n");
	printf("Insira sua escolha: ");

	do {
		
		gets(novaEntidade[0].subprefeitura); fflush(stdin);
				
	} while(!subprefeitura(novaEntidade[0].subprefeitura));
	
	printf("\nInsira a quantidade de cestas: ");
	scanf("%d", &novaEntidade[0].qtdcestas);
	
	
	dat = fopen("OSC.DAT", "a");
	
	if(!dat)
		printf("DEU RUIM NO DAT");
	
	if(fwrite (&novaEntidade[0], sizeof(registro_osc), 1, dat) != 1)
		printf("DEU RUIM");
	
	fclose(dat);
	
	ordenaOscCNPJDAT();
	
	/*datTest = fopen("OSC.DAT", "r");
	
	fread(&informacao, sizeof(informacao), 1, datTest);
	printf  ("\n%s;%s;%s;%s;%s;%s;%s;%s;%d;\n\n", informacao.entidade, informacao.cnpj,informacao.email,informacao.fone,informacao.comunidade,informacao.enderdoar,informacao.tipoassentamento,informacao.subprefeitura,informacao.qtdcestas);		
	
	getch();
	fclose(datTest);*/
	//escreveNoDat(novaEntidade, 1);
	getch();
}

void ConsultaEntidades() {
	char *cnpj;
	int ind = 0;
	int j;
	FILE *DAT;
	registro_osc *vet;
	
	cnpj = (char *) malloc(15);
	vet = (registro_osc *) malloc(findSize("OSC.DAT"));

	printf("\nInsira o CNPJ da entidade que deseja consultar: ");
	gets(cnpj);
	
	DAT = fopen("OSC.DAT", "r");
	if(DAT == NULL) {
		printf("\nErro ao ler dat");
		getch();
		exit(0);
	}
	
	while (!feof(DAT))
    {
   		fread (&vet[ind], sizeof(registro_osc), 1, DAT);
   	 	if (!feof(DAT))
   	    ind++;
    }
    
    fclose(DAT);
    
    for(j = 0; j < ind; j++) {
    	for (i = 0; i < strlen(vet[j].cnpj); i++) {
			if (vet[j].cnpj[i] != cnpj[i]) {
				break;	
			}
			
			if (i == strlen(vet[j].cnpj)-1) {
				printf("\n\nENTIDADE: %s", vet[j].entidade);
    			printf("\nCNPJ: %s", vet[j].cnpj);
    			printf("\nE-MAIL: %s", vet[j].email);
    			printf("\nTELEFONE: %s", vet[j].fone);
    			printf("\nCOMUNIDADES A SEREM BENEFICIADAS: %s", vet[j].comunidade);
    			printf("\nENDERECO DOADOR: %s", vet[j].enderdoar);
    			printf("\nTIPO DE ASSENTAMENTO/GRUPO PRECARIO: %s", vet[j].tipoassentamento);
    			printf("\nSUBPREFEITURA: %s", vet[j].subprefeitura);
    			printf("\nQUANTIDADE DE CESTAS: %d", vet[j].qtdcestas);
    			getch();
    			return;
			}
		}
	}
	
	printf("\n\n\tENTIDADE NÃO ENCONTRADA");
	getch();
} 

bool ValidaCNPJ(char *cnpj) {
	int i;
	
	if (strlen(cnpj) != 14) {
		printf("CNPJ invalido, tamanho deve ser de 14 dígitos");
		return false;
	}
	
	for (i = 0; i < 14; i++) {
		if (!isdigit(cnpj[i])) {
			printf("CNPJ invalido, digite apenas números!");
			return false;	
		}
	}
	
	return true;
}

bool tipoAssentamento(char *tipo) {
	int i, j;
	char tiposValidos[15][30] =
	{
		"Favela",
		"Cortico",
		"Ocupacao",
		"Loteamento",
		"Comunidade indigena",
		"Grupo de mulheres",
		"Imigrantes ou Refugiados",
		"Crianca e Adolescente",
		"Idosos",
		"Minorias etnico-raciais",
		"LGBTI",
		"Pessoas em situacao de rua",
		"Egresso do sistema prisional",
		"Pessoa com deficiencia",
		"Outros"
	};
	
	for(i=0; i<15; i++) {
		for(j = 0; j<strlen(tipo); j++) {
			if(tipo[j] != tiposValidos[i][j]) {
				break;
			};	
			
			if (strlen(tiposValidos[i]) == strlen(tipo) && j == strlen(tipo)-1) return true;
		}
	}
	printf("\ntipo de assentamento/grupo invalido, insira novamente: ");
	return false;
}

bool subprefeitura(char * subprefeitura)
{
	int i, j;
	char subprefeiturasValidas[32][30] = {
	"Aricanduva",
	"Butantã",
	"Campo Limpo",
	"Capela do Socorro",
	"Casa Verde",
	"Cidade Ademar",
	"Cidade Tiradentes",
	"Ermelino Matarazzo",
	"Freguesia do Ó",
	"Guaianases",
	"Ipiranga",
	"Itaim Paulista",
	"Itaquera",
	"Jabaquara",
	"Jaçanã Tremembé",
	"Lapa",
	"M'Boi Mirim",
	"Mooca",
	"Parelheiros",
	"Penha",
	"Perus",
	"Pinheiros",
	"Pirituba Jaraguá",
	"Santana Tucuruvi",
	"Santo Amaro",
	"São Mateus",
	"São Miguel Paulista",
	"Sapopemba",
	"Sé",
	"Vila Maria vila Guilherme",
	"Vila Mariana",
	"Vila Prudente",
	};
	
	for(i=0; i<32; i++) {
		for(j = 0; j<strlen(subprefeitura); j++) {
			if(subprefeitura[j] != subprefeiturasValidas[i][j]) {
				break;
			};	
			
			if (strlen(subprefeiturasValidas[i]) == strlen(subprefeitura) && j == strlen(subprefeitura)-1) return true;
		}
	}
	printf("\nSubprefeitura invalida, insira novamente: ");
	return false;
}

/*Programa principal*/
int main(){ 
	setlocale (LC_ALL, "Portuguese"); 
	
	converteAssistidos();
	converte();
	ordenaOscCNPJDAT();
	
    int opcao; 
	//Login();
	
    do{ 
        system ("cls"); 
        opcao = MenuPrincipal(); 

        switch (opcao) { 
            case 1: 
                GerenciamentoEntidades(); 
            	break;
				 
            case 2: 
                GerenciamentoAssistidos(); 
            	break; 
            	
            case 3: 
                GerenciamentoDonativos();
				break;
				
			case 4:
                MenuAtendimento();
            	break;
				 
            case 5:
                MaisInformacoes();
            	break;
            	               
            case 0: 
                printf ("Saindo....\n"); 
                exit(0); 
                
            default: 
				printf("\n\n\n\t\tOpção inválida, tente novamete\n\n"); 
                printf ("Tecle [Enter] para continuar..."); 
                getch(); 
        } 
        
    } while(1); 

return 0; 
}


/*Funï¿½ï¿½o MenuPrincipal*/
int MenuPrincipal (void){ 
	int imput;

    system("color 20");
	
    printf ("----------------------------------------------------------\n");
    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDÁRIA\n"); 
    printf ("----------------------------------------------------------\n\n");
    printf ("                   << MENU PRINCIPAL >>\n\n"); 
    printf ("      1 - Cadastro de entidades da sociedade civil\n"); 
    printf ("      2 - Cadastro de assistidos\n"); 
    printf ("      3 - Cadastro de donativos\n"); 
    printf ("      4 - Atendimento\n");
    printf ("      0 - Sair do Programa\n\n");
    
    printf ("      5 - Mais informações\n");
    printf ("----------------------------------------------------------\n\n");
    printf ("Digite a opção desejada e tecle [Enter]: ");
    scanf ("%d", &imput); 

	return imput; 
}

void GerenciamentoEntidades (void){ 
	int imput;
	bool opcaoValida = false;
	
	do {
	    system("color 0E");
	    
	    system("cls"); 
		
		printf ("----------------------------------------------------------\n");
	    printf ("        SOFTWARE DE GERENCIAMENTO CIDADE SOLIDÁRIA\n"); 
	    printf ("----------------------------------------------------------\n\n");
		printf ("         GERENCIAMENTO DE ENTIDADES DA SOCIEDADE CIVIL \n\n"); 
	    printf ("      1 - Cadastro de nova entidade\n"); 
	    printf ("      2 - Consulta entidades cadastradas\n"); 
	    printf ("      0 - Voltar ao MENU PRINCIPAL\n\n"); 
	    printf ("----------------------------------------------------------\n\n");
	    printf ("Digite a opção desejada e tecle [Enter]: ");
    	scanf("%d", &imput); fflush(stdin);

    
	    switch (imput) {
	    	case 1:
	    		CadastroEntidade();
	    		opcaoValida = true;
	    		break;
	    	
	    	case 2:
	    		ConsultaEntidades();
	    		opcaoValida = true;
	    		break;
	    		
	    	case 0:
				opcaoValida = true;
				break;
				
			default:
				printf("\n\n\n\t\tOpção inválida, tente novamete\n\n"); 
	            printf ("Tecle [Enter] para continuar..."); 
	            getch(); fflush(stdin);	
		}
		
	} while (!opcaoValida);
}

/*Funï¿½ï¿½o MenuAssitidos */
void GerenciamentoAssistidos (void){ 
	int imput;
	bool opcaoValida = false;
	
	/*cores do fundo e texto*/
	
	do {
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
	    printf ("Digite a opção desejada e tecle [Enter]: ");
    	scanf("%d", &imput); fflush(stdin);
    	
	    switch (imput) {
		    	case 1:
		    		//CadastroAssistido();
		    		opcaoValida = true;
		    		break;
		    	
		    	case 2:
		    		converteAssistidos();
		    		opcaoValida = true;
		    		break;
		    		
		    	case 3:
		    		//ConsultaAssistido();
		    		opcaoValida = true;
		    		break;
		    		
		    	case 0:
					opcaoValida = true;
					break;
					
				default:
					printf("\n\n\n\t\tOpção inválida, tente novamete\n\n"); 
		            printf ("Tecle [Enter] para continuar..."); 
		            getch(); fflush(stdin);	
			}
		
	} while (!opcaoValida);
    
    getch(); 
} 

/*Funï¿½ï¿½o MenuDonativos */
void GerenciamentoDonativos (void){ 
	
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
void MaisInformacoes (void){
   
    /*cores do fundo e texto*/
    system("color 10");
    
	system ("cls");
    printf ("---------------------------------------------------------------------------\n");
	printf ("			        MAIS INFORMAÇÕES   \n");
	printf ("---------------------------------------------------------------------------\n\n");
	system("color A0");
	printf ("  IFSP - INSTITUTO FEDERAL DE EDUCAÇÃO, CIÊNCIA E TECNOLOGIA DE SÃO PAULO\n\n");
	printf ("     TECNOLOGIA EM ANÁLISE E DESENVOLVIMENTO DE SISTEMAS (TADS) - SEGUNDO SEMESTRE\n\n\n\n");
    printf ("PROJETO: Cidade Solidária\n");
	printf ("\n");
    printf ("PROFESSORA: Eurides Balbino\n\n\n");
	printf ("DESENVOLVEDORES:\n\n");
    printf ("\tJefferson Trindade       Matr.: 3060128\n");
	printf ("\tHenrrique Cabral         Matr.: 3060632\n\n");
	printf ("---------------------------------------------------------------------------\n\n");
    printf ("Tecle [Enter] para voltar ao MENU PRINCIPAL...");
    getch();
    
}

void Login (void) {
	char *cnpj;
	char *email;
	FILE * ArqDAT;
	registro_osc  *vet;
	int  ind=0;
	int sucessoLogin = 0;
	
	cnpj = (char *) malloc(sizeof(char) * 15);
	email = (char *) malloc(sizeof(char) * 101);
	vet = (registro_osc  *) malloc (findSize("OSC.DAT"));

	if ( vet==NULL )
	{
		printf ("\nNão foi possível alocar %ld bytes em memória", findSize("OSC.DAT") );
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
	
	int aux;
	while (!feof(ArqDAT))
	{
		fread (&vet[ind], sizeof(registro_osc), 1, ArqDAT);

		if (!feof(ArqDAT))
			ind++;				
	}
	printf("\n%d\n", ind);/*--------------------------------------------------------------------------------------*/

	getch();
	fclose(ArqDAT);
	
	system("cls");
	do {
		system("color 40");
		
		printf("---------------------------------------------\n");
		printf("		INFORME LOGIN			\n");
		printf("---------------------------------------------\n");
		
		printf("Informe CNPJ: ");
		scanf("%s", cnpj);
		
		printf("\nInforme e-mail: ");
		scanf("%s", email);

		sucessoLogin = buscaBinaria(vet, cnpj, email, 0, ind);

		if (!sucessoLogin) {
			system("cls");
			printf("FALHA AO REALIZAR LOGIN, INFORMAÇÕES INCORRETAS\n\n");
		}
		
	} while (!sucessoLogin);	
}
