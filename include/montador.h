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
//Funcao que separara os elementos da linha
void scanner(char *linha, int contador_linha, char *delimitador);

// Realiza o pre processamento sobre um arquivo .asm (-p), gerando um arquivo .pre
FILE* pre_processamento(FILE *entrada, char* nome_arquivo_pre);
// Realiza a montagem sobre um arquivo .asm ou .pre (-o)
FILE* passagem1(FILE *pre_processado);
FILE* passagem2(FILE *arq_intermediario, char* nome_arquivo_obj);

void imprime_tokens();
int checa_tipo_instrucao(FILE* obj, int i, int contador_linha, int *contador_posicao);

#endif
