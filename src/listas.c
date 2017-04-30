#include "listas.h"

// Inicializa lista
void inicializa_equ(struct Equ_t *lista){
	lista->proximo = NULL;
}

// Lista vazia
int vazia_equ(struct Equ_t *lista){
	if(lista->proximo == NULL)
		return 1;
	else
		return 0;
}

// Insere no fim da lista
void insere_equ(struct Equ_t *lista, char *id, char *valor){
  struct Equ_t *novo;
  novo = (struct Equ_t *) malloc (sizeof (struct Equ_t));

  strcpy(novo->id,id);
  strcpy(novo->valor,valor);
  novo->proximo = lista->proximo;

  lista->proximo = novo;
}

// Busca um id na lista e retorna o valor associado ao mesmo
struct Equ_t * busca_equ(struct Equ_t *lista, char *id_buscado){
  struct Equ_t *aux = lista;

  while (aux != NULL){
		// Se o id buscado esta na lista, retorna o EQU encontrado
		if(!strcmp(aux->id, id_buscado)){
			return aux;
		}
		// Percorre a lista
    aux = aux->proximo;
  }
	// Nao achou o EQU na lista
	return NULL;
}

// Mostra a lista
void exibe_equ(struct Equ_t *lista){
  printf("\n");
	if(vazia_equ(lista)){
		printf("Lista vazia!\n\n");
		return;
	}

	struct Equ_t *aux = lista->proximo;

	while(aux!=NULL){
		printf("id %s", aux->id);
    printf("valor %s", aux->valor);
    printf("->");
		aux = aux->proximo;
	}
	printf("\n\n");
}

// Libera a memoria alocada pela lista
void libera_equ(struct Equ_t *lista){
	if(!vazia_equ(lista)){
		struct Equ_t *proximoNo, *noAtual;

		noAtual = lista->proximo;
		while(noAtual != NULL){
			proximoNo = noAtual->proximo;
			free(noAtual);
			noAtual = proximoNo;
		}
	}
}
