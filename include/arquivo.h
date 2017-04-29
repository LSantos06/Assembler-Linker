#ifndef ARQ_H
#define ARQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum operacoes {
	PRE_PROC, MONTAGEM, ERRO
} Operacoes_t;

/*
*  O programa de traducao deve receber tres argumentos em linha de comando
* (nessa ordem):
*	  - Um tipo de operacao (-p ou -o);
*	  - Um arquivo de entrada contendo um programa em Assembly em formato texto
* (verificar que extensao seja “.asm” ou ".pre") na linguagem hipotetica;
*   - E um arquivo de saida sem extensao.
*
* EX: macroasssembler -p teste.asm teste
*/

// Retorna tipo de operacao especificado na chamada do programa
Operacoes_t tipo_operacao(char* string);
// Validacao dos argumentos passados com a chamada de programa
Operacoes_t validacao_argumentos(int argc, char* argv[]);	

#endif 