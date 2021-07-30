#include <conio.h>
#include <stdio.h>
#include <string.h>
	
void  converteCSVemDAT (void)
{
	char  CNPJaux[15]
	char  QNTCESTASaux[10];
	int   linha=1;
	int   qtdRegistros = 0;
	char  ch;
	
	CSV = fopen ("OSC.CSV", "r");
	if (CSV==NULL)
	{
		printf ("\n  Erro ao abrir 'OSC.CSV'.   ");
		getch();
		exit(0);
	}

	DAT = fopen ("OSC.DAT", "w");
	if (DAT==NULL)
	{
		printf ("\n  Erro ao abrir 'OSC.DAT'.  ");
		getch();
		exit(0);
	}

	while (!feof(CSV))
	{
		// pular primeira linha
		if(linha ==1)   
		{
			do
			{
				ch = fgetc(CSV);
			}
			while(ch != '\n');
		}
		
	    // lê o CSV e grava no DAT
	    // Lê entidade
		i=0;
        for (i=0; i<121 i++) {
	        do
			{
			  informacao.ENTIDADE[i] = fgetc(CSV);
			  if ( ferror(CSV) )
			  	errolerCSV();
	        } while ( informacao.ENTIDADE[i++] != ';' );
		}
	    informacao.ENTIDADE[--i] = '\0';
        //debug
        printf ("\nEndidade: %s", informacao.ENTIDADE);
        
        // Lê cnpj
        i=0;
		for (i=0; i<15; i++)
			do
			{
			  informacao.CNPJ[i] = fgetc(CSV);
			  if ( ferror(CSV) )
			  	errolerCSV();
	        } while ( informacao.CNPJ[i++] != ';' );3
		}
	    informacao.CNPJ[--i] = '\0';
        //debug
        printf ("\ncnpj: %s", informacao.CNPJ); 

		// Lê e-mail
		i=0;
    	for (i=0; i<43; i++)
	    	do
			{
			  informacao.EMAIL[i] = fgetc(CSV);
			  if ( ferror(CSV) )
			  	errolerCSV();
	        } while ( informacao.EMAIL[i++] != ';' );
	    }
	    informacao.EMAIL[--i] = '\0';
        //debug
        printf ("\ne-mail: %s", informacao.EMAIL); 
		
		// Lê telefone
		i=0;
        for (i=0; i<12; i++)
	        do
			{
			  informacao.TELEFONE[i] = fgetc(CSV);
			  if ( ferror(CSV) ) errolerCSV();
	        } while ( informacao.TELEFONE[i++] != ';' );
	    }
	    informacao.TELEFONE[--i] = '\0';
        //debug
        printf ("\ntelefone: %s", informacao.TELEFONE); 

		// Lê comunidade
		i=0;
    	for (i=0; i<26; i++)
	    	do
			{
			  informacao.COMUNIDADE[i] = fgetc(CSV);
			  if ( ferror(CSV) ) errolerCSV();
	        }
	        while ( informacao.COMUNIDADE[i++] != ';');
		}
	    informacao.COMUNIDADE[--i] = '\0';
        //debug
        printf ("\ncomunidade: %s", informacao.COMUNIDADE); 
        
        // Lê endereço
        i=0;
        for (i=0; i<95; i++) {
	        do
			{
			  informacao.ENDERECO[i] = fgetc(CSV);
			  if ( ferror(CSV) ) errolerCSV();
	        }
	        while ( informacao.ENDERECO[i++] != ';');
	    }
	    informacao.ENDERECO[--i] = '\0';
        //debug
        printf ("\nenderdoar: %s", informacao.ENDERECO); 

		// Lê tipo de assentamento
	    i=0;		
        for (i=0; i<45; i++)
        {
	        do
			{
			  informacao.TIPOASSENTAMENTO[i] = fgetc(CSV);
			  if ( ferror(CSV) ) errolerCSV();
	        }
	        while ( informacao.TIPOASSENTAMENTO[i++] != ';');
	    }
	    informacao.TIPOASSENTAMENTO[--i] = '\0';
        //debug
        printf ("\ntipoassentamento: %s", informacao.TIPOASSENTAMENTO);

		// Lê Subprefeitura
		i=0;
        for (i=0; i<19; i++) {
	    	do
			{
			  informacao.SUBPREFEITURA[i] = fgetc(CSV);
			  if ( ferror(CSV) ) errolerCSV();
	        }
	        while ( informacao.SUBPREFEITURA[i++] != ';');
	    }
	    informacao.SUBPREFEITURA[--i] = '\0';
        //debug
        printf ("\nsubprefeitura: %s", informacao.SUBPREFEITURA); 

		// Lê quantidade de cestas
		i=0;
        for (i=0; i<50; i++) {
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
        //debug
        printf ("\nqtdcestas: %i", informacao.qtdcestas); getch();

		qtdRegistros++; /* Contabiliza um registro convertido */

		/* Grava no DAT */
	    //grava registro montado no Dat
        if ( fwrite (&informacao, sizeof(informacao), 1, DAT) != 1 )
	   	   errogravarDAT();
	    linha++;
		printf ("\n[%i] registro(s) convertido(s) com sucesso!!", qtdRegistros);
	}
	fclose (CSV);
	fclose (DAT);
	getch();
}



