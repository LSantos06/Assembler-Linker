#ifndef MONTADOR_H
#define MONTADOR_H

#include "arquivo.h"

/*
* Montador a ser implementado sera de 2 passagens
*/

// Seleciona a operacao de acordo com o argumento
void seleciona_operacao(Operacoes_t, char* argv[]);
// Realiza o pre processamento sobre um arquivo .asm (-p), gerando um arquivo .pre
FILE* pre_processamento(FILE *entrada, char* nome_arquivo_pre);
// Realiza a montagem sobre um arquivo .asm ou .pre (-o)
FILE* passagem1(FILE *pre_processado);
FILE* passagem2(FILE *arq_intermediario);

#endif
