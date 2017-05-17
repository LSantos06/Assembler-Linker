#ifndef LISTAS_H
#define LISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho maximo dos atributos de uma lista
#define TAMAT 10

// Lista para as definicioes de equ
typedef struct lista{
  char id[TAMAT];
  char valor[TAMAT];
  struct lista *proximo;
} lista_t;

//Mapa de bits com enderecos de relocacao p/ ligador
extern lista_t *mapa_bits;

// Funcoes para manipulacao das listas de EQU
void inicializa_lista(lista_t *lista);
int vazia_lista(lista_t *lista);
void insere_elemento(lista_t *lista, char *id, char *valor);
lista_t* insere_lista(lista_t *lista, lista_t *lista2);
lista_t* busca_elemento(lista_t *lista, char *id_buscado);
void exibe_lista(lista_t *lista);
void libera_lista(lista_t *lista);

#endif
