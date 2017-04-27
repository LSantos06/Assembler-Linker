#ifndef ARQ_H
#define ARQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum operacoes {
	PRE_PROC, MONTAGEM, ERRO
};

/*
* O  programa  de  traducao deve receber tres  argumentos  em  linha  de  comando
* (nessa ordem): um tipo de operacao, um arquivo de entrada contendo um programa em
* Assembly em formato texto (verificar que extensao seja “.asm”) na 
* linguagem hipotetica e um arquivo de saida (SO O NOME DO ARQUIVO DE SAIDA SEM EXTENSAO).
*/

//Validacao dos argumentos passados com a chamada de programa
void verificacao_parametros(int argc, char* argv[]); 
//Retorna tipo de operacao especificado na chamada do programa	
enum operacoes tipo_operacao(char* string);	

#endif 