#ifndef MONTADOR_H
#define MONTADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "tabelas.h"
#include "listas.h"
#include "ligador.h"

/*
* Montador a ser implementado sera de 2 passagens
*/

// Seleciona a operacao de acordo com o argumento
void seleciona_operacao(int argc, char* argv[]);

// Funcao que separara os elementos da linha
int scanner(char *linha, int contador_linha, char *delimitador, int passagem);

// Realiza o pre processamento sobre um arquivo .asm (-p), gerando um arquivo .pre
FILE* pre_processamento(FILE *entrada, char* nome_arquivo_pre);

// Realiza a montagem sobre um arquivo .asm ou .pre (-o)
//Passagem 1 retorna 0 se houve um erro, 1 se nao houver erros
int passagem1(FILE *pre_processado);
FILE* passagem2(FILE *arq_intermediario, char* nome_arquivo_obj, int erro_passagem_1);

// Exibe os tokens de uma linha
void imprime_tokens();

/*********** Funcoes de checagem de tipos ***********/
int checa_tipo_instrucao(FILE* obj, int i, int contador_linha, int *contador_posicao);
int checa_tipo_diretiva(FILE* obj, int i, int contador_linha, int *contador_posicao);

#endif
