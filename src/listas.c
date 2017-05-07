#include "listas.h"

// Inicializa lista
void inicializa_lista(lista_t *lista){
	lista->proximo = NULL;
}

// Lista vazia
int vazia_lista(lista_t *lista){
	if(lista->proximo == NULL)
		return 1;
	else
		return 0;
}

// Insere no fim da lista
void insere_elemento(lista_t *lista, char *id, char *valor){
  lista_t *novo;
  novo = (lista_t *) malloc (sizeof (lista_t));

	if(valor[strlen(valor)-1] < 30
	|| valor[strlen(valor)-1] > 122){
		 valor[strlen(valor)-1] = '\0';
	}

	lista_t *busca;

	busca = busca_elemento(lista, id);

	if(valor[strlen(valor)-1] < 30
	|| valor[strlen(valor)-1] > 122){
		 valor[strlen(valor)-1] = '\0';
	}

	// Elemento ja esta na lista
	if(busca!=NULL){
		strcat(busca->valor, " ");
		strcat(busca->valor, valor);
	}
	// Elemento ainda nao esta na lista
	else{
		strcpy(novo->id,id);
		strcpy(novo->valor,valor);
		novo->proximo = lista->proximo;

		lista->proximo = novo;
	}

}

// Insere uma lista em outra
lista_t * insere_lista(lista_t *lista, lista_t *lista2){
	if(vazia_lista(lista)){
		return lista2;
	}
	else{
		lista_t *aux = lista;

		while(aux->proximo != NULL){
			aux = aux->proximo;
			insere_elemento(lista2, aux->id, aux->valor);
		}
		return lista2;
	}
}

// Busca um id na lista e retorna elemento
lista_t * busca_elemento(lista_t *lista, char *id_buscado){
  lista_t *aux = lista;

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
void exibe_lista(lista_t *lista){
  printf("\n");
	if(vazia_lista(lista)){
		printf("Lista vazia!\n\n");
		return;
	}

	lista_t *aux = lista->proximo;

	while(aux!=NULL){
		printf("(id: %s ", aux->id);
    printf("valor: %s)", aux->valor);
    printf("->");
		aux = aux->proximo;
	}
	printf("\n\n");
}

// Libera a memoria alocada pela lista
void libera_lista(lista_t *lista){
	if(!vazia_lista(lista)){
		lista_t *proximoNo, *noAtual;

		noAtual = lista->proximo;
		while(noAtual != NULL){
			proximoNo = noAtual->proximo;
			free(noAtual);
			noAtual = proximoNo;
		}
	}
}
