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
	//// -l para ligacao
	else if (!(strcmp(string, "-l"))){
		return LIGACAO;
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

	//// Se o numero de argumentos eh invalido para -p e -o, ERROR -1
	if(tipo_operacao(argv[1])!=LIGACAO && argc!=4){
		printf("Erro: numero de argumentos na chamada do programa eh invalido!\nObteve-se %d argumentos.\n", argc-1);
		exit(-1);
	}

	//// Se o numero de argumentos eh invalido para -l, ERROR -1
	if(argc>7){
		printf("Erro: numero de argumentos na chamada do programa eh invalido!\nObteve-se %d argumentos.\n", argc-1);
		exit(-1);
	}

	//// Se o arquivo de saida tem extensao, ERROR -2
	// Variavel que checa a extensao do arquivo de saida
	char *validade_saida = ".";
	// Funcao strstr() checa se subselecao esta dentro de uma string de interesse
	if((strstr(argv[argc-1], validade_saida))!=NULL){
		printf("Erro: Arquivo de saida ja possui extensao!\n");
		exit(-2);
	}

	//// Se o tipo de operacao eh diferente de -p -o e -l, ERROR -3
	if(tipo_operacao(argv[1])==ERRO){
		printf("Erro: operacao nao reconhecida!\n");
		exit(-3);
	}

	operacao = tipo_operacao(argv[1]);
	// Retorna a operacao a ser realizada
	return operacao;
}

/*
 *  string_alta()
 *
 *  Funcao que passa uma string para caixa alta
 */
void string_alta(char *s){
		for(; *s; s++)
			if(('a' <= *s) && (*s <= 'z'))
				*s = 'A' + (*s - 'a');
}

/*
 *  string_baixa()
 *
 *  Funcao que passa uma string para caixa baixa
 */
void string_baixa(char *s){
		for(; *s; s++)
			if(('A' <= *s) && (*s <= 'Z'))
				*s = 'a' + (*s - 'A');
}
