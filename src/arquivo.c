#include "arquivo.h"

/*
 *  tipo_operacao()
 *
 *  Funcao que retorna o tipo de operacao de acordo com o segundo argumento de entrada
 * do programa de traducao
 */
Operacoes_t tipo_operacao(char* string){
	// Funcao strcmp() retorna 0 se strings forem iguais
	//// -p para pre processamento
	if (!(strcmp(string, "-p"))){
		return PRE_PROC;
	}
	//// -o para montagem
	else if (!(strcmp(string, "-o"))){
		return MONTAGEM;
	}
	else{
		return ERRO;
	}
}

/*
 *  validacao_argumentos()
 *
 *  Funcao responsavel pela checagem do numero de argumentos de entrada
 * do programa de traducao
 */
Operacoes_t validacao_argumentos(int argc, char* argv[]){
	// Variavel para retorno
	Operacoes_t operacao;

	//// Se o numero de argumentos eh invalido, ERROR -1
	if(argc!=4){
		printf("Erro: numero de argumentos na chamada do programa eh invalido!\nObteve-se %d argumentos.\n", argc-1);
		exit(-1);
	}
	//// Se o tipo de operacao eh diferente de -p ou -o, ERROR -2
	if(tipo_operacao(argv[1])==ERRO){
		printf("Erro: operacao nao reconhecida!\n");
		exit(-2);
	}
	//// Se o arquivo de saida tem extensao, ERROR -3
	// Variavel que checa a extensao do arquivo de saida
	char *validade_saida = ".";
	// Funcao strstr() checa se subselecao esta dentro de uma string de interesse
	if((strstr(argv[3], validade_saida))!=NULL){
		printf("Erro: Arquivo de saida ja possui extensao!\n");
		exit(-3);
	}

	operacao = tipo_operacao(argv[1]);
	// Retorna a operacao a ser realizada
	return operacao;
}
