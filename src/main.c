#include "montador.h"

#define MAIN_TESTES 1

#if MAIN_TESTES

void testes();
void teste_tabelas();
void teste_scanner();

int main(int argc, char* argv[]){

	Operacoes_t operacao;

	// Validacao dos argumentos e decisao da operacao e
	// Executa a operacao de acordo com o segundo argumento
	seleciona_operacao(argc, argv);

	testes();


	return 0;
}

void testes(){
	printf("\nTabela simbolos:\n");
	imprime_tabela(tabela_simbolos);
	printf("\nTabela definicoes:\n");
	imprime_tabela(tabela_definicoes);
	printf("\nTabela Uso:\n");
	imprime_tabela(tabela_uso);

	//teste_tabelas();
	//teste_scanner();

}

void teste_scanner(){
	char teste[] = "Teste com espaco token";
	scanner(teste, 0, " \n\t");
	imprime_tokens();

	strcpy(teste, "1Teste mais um");
	scanner(teste,1, " \n\t");
	imprime_tokens();

	strcpy(teste, "1Teste           mais um");
	scanner(teste,2, " \n\t");
	imprime_tokens();

	strcpy(teste, "1Teste\tmais um");
	scanner(teste,3, " \n\t");
	imprime_tokens();

	strcpy(teste, "Teste mais um\n");
	scanner(teste,4, " \n\t");
	imprime_tokens();

	strcpy(teste, "Teste\n");
	scanner(teste,5, " \n\t");
	imprime_tokens();

	strcpy(teste, "A,B\n");
	scanner(teste,5, " \n\t,");
	imprime_tokens();
}

void teste_tabelas(){
	inicializa_tabelas();

	//insere(tabela, instrucao, posicao, externo, eh_dado?)
	insere_tabela(tabela_simbolos, "exemplo1", 10, 0, 0);
	insere_tabela(tabela_simbolos, "exemplo2", 5, 0, 0);
	insere_tabela(tabela_simbolos, "exemplo3", 15, 0, 0);

	insere_tabela(tabela_definicoes, "exemplo1", 15, 0, 0);
	insere_tabela(tabela_definicoes, "exemplo2", 3, 0, 0);

	imprime_tabela(tabela_simbolos);
	imprime_tabela(tabela_definicoes);

	imprime_instrucoes_diretivas();
}

#else

int main(int argc, char* argv[]){

	Operacoes_t operacao;

	// Validacao dos argumentos e decisao da operacao e
	// Executa a operacao de acordo com o segundo argumento
	seleciona_operacao(argc, argv);


	return 0;
}

#endif
