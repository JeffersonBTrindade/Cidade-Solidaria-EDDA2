/*Bibliotecas*/
#include <string.h>
#include <memory.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define TENT   121

/*tipos pre-definidos */
/*
typedef struct
{
	char	entidade			[116+1];
	char	cnpj				[14+1];
	char	email				[42+1];
	char	fone				[11+1];
	char	comunidade			[26+1];
	char	enderdoar			[93+1];
	char	tipoassentamento	[17+1];
	char	subprefeitura		[18+1];
	float	custo;
	int	qtdcestas;
}
registro_osc;
*/
typedef struct
{
	char 	entidade				[TENT];
	char    cnpj					[14+1];
	char    email                   [100+1];
	char    fone					[11+1];
    char    comunidade				[30+1];
    char    enderdoar				[150+1];
    char    tipoassentamento		[50+1];
    char    subprefeitura			[50+1];
    int		qtdcestas;
}
registro_osc;

typedef struct
{
	char	nomecompleto			[120+1];
	char	datanasc				[10+1];
	char	cpf						[11+1];
	char	municipio				[100+1];
	char	logradouro 				[150+1];
	char	nro						[7+1];
	char	complemento				[10+1];
	char	bairro					[300+1];
	char	celular					[11+1];
	char	possuipet;

}
registro_ass;


/*variaveis globais*/
long int 	TAMANHO_VETOR;
int			gerenciaOSC;

/*Fun��es*/

int validaTipoAssentamento(char *tipo){
	char	tiposValidos[15][30] =
	{
	"Favela",
	"Corti�o",
	"Ocupa��o",
	"Loteamento",
	"Comunidade ind�gena",
	"Grupo de mulheres",
	"Imigrantes ou Refugiados",
	"Crian�a e adolescente",
	"Idosos",
	"Minorias �ttnico-raciais",
	"LGBTI",
	"Pessoas em situa��o de rua",
	"Egresso do sistema prisional",
	"Pessoa com defici�ncia",
	"Outros"
	};
	int i, achou = 0;
	for(i=0; i<15; i++)
		if(strcmp(tipo,tiposValidos[i])==0)
		{
			achou = 1;
			break;
		}
	return(achou);
}

int validaSubprefeitura(char * subprefeitura)
{
	char subprefeiturasValidas[32][30] = {
	"Aricanduva",
	"Butant�",
	"Campo Limpo",
	"Capela do Socorro",
	"Casa Verde",
	"Cidade Ademar",
	"Cidade Tiradentes",
	"Ermelino Matarazzo",
	"Freguesia do �",
	"Guaianases",
	"Ipiranga",
	"Itaim Paulista",
	"Itaquera",
	"Jabaquara",
	"Ja�an� Trememb�",
	"Lapa",
	"M'Boi Mirim",
	"Mooca",
	"Parelheiros",
	"Penha",
	"Perus",
	"Pinheiros",
	"Pirituba Jaragu�",
	"Santana Tucuruvi",
	"Santo Amaro",
	"S�o Mateus",
	"S�o Miguel Paulista",
	"Sapopemba",
	"S�",
	"Vila Maria vila Guilherme",
	"Vila Mariana",
	"Vila Prudente",
	};
	int i, achou = 0;
	for (i=0; i<32; i++)
		if(strcmp(subprefeitura,subprefeiturasValidas[i])==0);
		{
			achou =1;
			
		}
		//break;
	return(achou);
}

int validaCNPJ(char* cnpj)
{
	int i;
	if(strlen(cnpj)!=14)
		return(0);
	for(i=0; cnpj[i]!='\0'; i++)
		if(cnpj[i]<'0' || cnpj[i]>'9')
			return(0);
	return(1);
}
