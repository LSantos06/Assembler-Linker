#ifndef TABELAS_H
#define TABELAS_H

#include <stdio.h>
#include <string.h>

/* Modulo que contem estruturas das tabelas, assim
 * como funcoes para manipulacoes delas
*/

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


//Funcoes de manipulacao das tabelas

int tamanho_instrucao(char *operacao);

int tamanho_diretiva(char *diretiva); 


#endif 