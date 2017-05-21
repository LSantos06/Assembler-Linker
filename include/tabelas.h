#ifndef TABELAS_H
#define TABELAS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Modulo que contem estruturas das tabelas, assim
 * como funcoes para manipulacoes delas
*/

/// MONTADOR

//Definicao da Tabela de Instrucoes e respectiva instanciacao
typedef struct{
	char nome[10];
	int ops, opcode;
} opTab;

extern const opTab tabela_instrucoes[14];


//Definicao da Tabela de Diretivas e instanciacao
typedef struct{
	char nome[10];
	int ops, tamanho;

} dirTab;

extern const dirTab tabela_diretivas[7];


//Definicao da estrutura para tabela de simbolos
//e tabela de definicoes (subconjunto da TS)
typedef struct addr{
	char simbolo[50];
	int posicao_memoria;
	int externo;
  int data;
	struct addr* prox;
} addrTab;

extern addrTab* tabela_simbolos;
extern addrTab* tabela_definicoes;
//Tabela de uso usara apenas o simbolo + posicao_memoria
extern addrTab* tabela_uso;


/*********** Funcoes de manipulacao das tabelas ***********/
void imprime_instrucoes_diretivas();
//Funcao de encapsulamento de instrucoes e diretivas
int tamanho_instrucao(char *operacao);
int opcode(char *simbolo);
int tamanho_diretiva(char *diretiva);
char *pega_primeiro_simbolo(addrTab *tabela);

/*********** Tabela de simbolos e de definicoes ***********/
void inicializa_tabelas();
int esta_vazia(addrTab* tabela);
int pertence_tabela(addrTab* tabela, char* nome);
void insere_tabela(addrTab *tabela, char *nome, int posicao, int externo, int data);
void imprime_tabela(addrTab *tabela);
void copia_para_definicoes();
//Funcoes de encapsulamento das tabelas
int busca_posicao_memoria(addrTab* tabela, char* nome);
int eh_dado(char*simbolo);
int eh_externo(char *simbolo);

/// LIGADOR

#endif
