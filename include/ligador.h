#ifndef LIGADOR_H
#define LIGADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"
#include "arquivo.h"

// Definicao do tamanho maximo de uma linha
#define TLINHA 100

/*
* Ligador a se implementado
*/
void ligador(int num_objetos, int argc, char* argv[]);
#endif
