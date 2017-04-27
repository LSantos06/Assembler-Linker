#ifndef MONTADOR_H
#define MONTADOR_H

#include "stdio.h"
#include "stdlib.h"

/*
* Montador a ser implementado sera de 2 passagens
*/

FILE* pre_processamento(FILE *entrada);
FILE* passagem1(FILE *pre_processado);
FILE* passagem2(FILE *arq_intermediario);

#endif