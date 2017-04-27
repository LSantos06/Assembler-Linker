#include "arquivo.h"


void verificacao_parametros(int argc, char* argv[]){
	if(argc!=4){
		printf("Erro: numero de argumentos na chamada do programa invalido!\nObteve-se %d argumentos.\n", argc-1);
		exit(0);
	}
	if(tipo_operacao(argv[1])== ERRO){
		printf("Erro: operacao nao reconhecida.\n");
		exit(0);
	}
	char *validade_entrada = ".asm";
	char *validade_saida = ".";

	//Funcao strstr() checa se subselecao esta
	//dentro de uma string de interesse
	if((strstr(argv[2], validade_entrada))==NULL){
		printf("Erro: Arquivo especificado nao contem extensao '.asm'\n");
		exit(0);
	}
	//Verifica se arquivo de saida n tem extensao
	if((strstr(argv[3], validade_saida))!=NULL){
		printf("Erro: Arquivo de saida possui ja extensao\n");
		exit(0);
	}

    FILE* fp = fopen(argv[2], "r");

    if(fp == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(0);
	}

	return;
}


enum operacoes tipo_operacao(char* string){
	if (!(strcmp(string, "-p"))){
		return PRE_PROC;
	}
	else if (!(strcmp(string, "-o"))){
		return MONTAGEM;
	}
	else{
		return ERRO;
	}
}
