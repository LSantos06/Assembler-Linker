#include "tabelas.h"

//Retorna numero de operandos da instrucao de interesse
int tamanho_instrucao(char *operacao){
	int i, achou = 0, retorno = 0;

	for (i = 0; i<14; i++){
		//Se achou a instrucao
		if(!(strcmp(operacao, tabela_instrucoes[i].nome))){
			achou = 1;
			retorno = tabela_instrucoes[i].ops;
		} // if
	} // for

	//Se nao achou instrucao
	if(achou == 0){
		return -1;
	}

	return retorno;
}
