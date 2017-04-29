#include "arquivo.h"
#include "montador.h"

int main(int argc, char* argv[]){

	Operacoes_t operacao;

	// Validacao dos argumentos e decisao da operacao
	operacao = validacao_argumentos(argc, argv);
	// Executa a operacao de acordo com o segundo argumento
	seleciona_operacao(operacao, argv);

	return 0;
}