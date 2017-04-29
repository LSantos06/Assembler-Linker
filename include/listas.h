#ifndef LISTAS_H
#define LISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao dos atributos de um equ
#define TEQU 10

// Lista para as definicioes de equ
struct Equ_t{
  char id[TEQU];
  char valor[TEQU];
  struct Equ_t *proximo;
};

void inicializa_equ(struct Equ_t *lista);
int vazia_equ(struct Equ_t *lista);
void insere_equ(struct Equ_t *lista, char *id, char *valor);
struct Equ_t* busca_equ(struct Equ_t *lista, char *id_buscado);
void exibe_equ(struct Equ_t *lista);
void libera_equ(struct Equ_t *lista);

#endif
