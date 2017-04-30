#include "montador.h"
#include "tabelas.h"
#include "arquivo.h"

#define MAIN_TESTES

#ifdef MAIN_TESTES

void testes();
void teste_tabelas();
void teste_scanner();

int main(int argc, char* argv[]){

	testes();

	Operacoes_t operacao;

	// Validacao dos argumentos e decisao da operacao e
	// Executa a operacao de acordo com o segundo argumento
	seleciona_operacao(argc, argv);


	return 0;
}

void testes(){
	teste_tabelas();
	//teste_scanner();

}

void teste_scanner(){
	char teste[] = "Teste com espaco token";
	scanner(teste, 0);

	strcpy(teste, "1Teste mais um");
	scanner(teste,1);

	strcpy(teste, "1Teste           mais um");
	scanner(teste,2);

	strcpy(teste, "1Teste\tmais um");
	scanner(teste,3);

	strcpy(teste, "Teste mais um\n");
	scanner(teste,4);
}

void teste_tabelas(){
	inicializa_tabelas();

	insere_tabela(tabela_simbolos, "exemplo1", 10);
	insere_tabela(tabela_simbolos, "exemplo2", 5);
	insere_tabela(tabela_simbolos, "exemplo3", 15);

	insere_tabela(tabela_definicoes, "exemplo1", 15);
	insere_tabela(tabela_definicoes, "exemplo2", 3);

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
