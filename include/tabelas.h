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

opTab tabela_instrucoes[14] = {
	{"ADD", 1, 1}, {"SUB", 1, 2},
	{"MULT", 1, 3}, {"DIV", 1, 4},
	{"JMP", 1, 5}, {"JUMPN", 1, 6},
	{"JMPP", 1, 7}, {"JMPZ", 1, 8},
	{"COPY", 1, 9}, {"LOAD", 1, 10},
	{"STORE", 1, 11}, {"INPUT", 1, 12},
	{"OUTPUT", 1, 13}, {"STOP", 1, 14}
};

//Definicao da Tabela de Diretivas e instanciacao
typedef struct{
	char nome[10];
	int ops, tamanho;
} dirTab;

dirTab tabela_diretivas[7] = {
	//-1 Indica q numero de operandos e tamanho
	// eh variavel
	{"SECTION", 1, 0}, {"SPACE", -1, -1},
	{"CONST", 1, 1}, {"PUBLIC", 0, 0},
	{"EXTERN", 0, 0}, {"BEGIN", 0, 0},
	{"END", 0, 0}

};


//Funcoes de manipulacao das tabelas

int tamanho_instrucao(char *operacao);

int tamanho_diretiva(char *diretiva); 


#endif 