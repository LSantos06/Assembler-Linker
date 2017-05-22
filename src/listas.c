#include "listas.h"

// Listas globais
lista_t *mapa_bits;
lista_t *lista_zeros;
lista_t *lista_ctes;
lista_t *mapa_provisorio;
lista_t *lista_tamanhos_vetores;

/*
 *  instancia_listas_globais()
 *
 *  Inicializacao e instanciamento das listas globais
 */
void instancia_listas_globais(){
	//Inicia mapa de bits pra mandar enderecos de relocacao
	//Mapa bits vai conter dados invertidos, pra passar pro mapa provisorio dps
	mapa_provisorio = (lista_t*)  malloc(sizeof(lista_t));
	inicializa_lista(mapa_provisorio);
	mapa_bits = (lista_t *) malloc(sizeof(lista_t));
	inicializa_lista(mapa_bits);

	//Inicia lista de zeros para checar divisao por zero
	lista_zeros = (lista_t *) malloc(sizeof(lista_t));
	inicializa_lista(lista_zeros);

	//Lista de alterados para verificar alteracoes em constantes
	lista_ctes = (lista_t *) malloc(sizeof(lista_t));
	inicializa_lista(lista_ctes);

	//Lista com tamanhos dos vetores, para analisar excecao de tamanho
	lista_tamanhos_vetores = (lista_t *) malloc(sizeof(lista_t));
	inicializa_lista(lista_tamanhos_vetores);
}

/*
 *  inicializa_lista()
 *
 *  Inicializacao de uma lista
 */
void inicializa_lista(lista_t *lista){
	lista->proximo = NULL;
}

/*
 *  vazia_lista()
 *
 *  Verifica se a lista esta vazia
 */
int vazia_lista(lista_t *lista){
	if(lista->proximo == NULL)
		return 1;
	else
		return 0;
}

/*
 *  insere_elemento()
 *
 *  Insercao de um elemento na lista
 */
void insere_elemento(lista_t *lista, char *id, char *valor){
  lista_t *novo;
  novo = (lista_t *) malloc (sizeof (lista_t));

	// Tira \n
	if(id[strlen(id)-1] < 48
	|| id[strlen(id)-1] > 122){
		 id[strlen(id)-1] = '\0';
	}
	if(valor[strlen(valor)-1] < 48
	|| valor[strlen(valor)-1] > 122){
		 valor[strlen(valor)-1] = '\0';
	}

	strcpy(novo->id,id);
	strcpy(novo->valor,valor);
	novo->proximo = lista->proximo;

	lista->proximo = novo;
}

/*
 *  insere_lista()
 *
 *  Insercao de uma lista em uma lista ja existente
 */
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

/*
 *  busca_elemento()
 *
 *  Busca um ID em uma lista e retorna o elemento associado a este ID
 */
lista_t * busca_elemento(lista_t *lista, char *id_buscado){
  lista_t *aux = lista;

	string_alta(id_buscado);
	// Tira \n
	if(id_buscado[strlen(id_buscado)-1] < 48
	|| id_buscado[strlen(id_buscado)-1] > 122){
		 id_buscado[strlen(id_buscado)-1] = '\0';
	}

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

/*
 *  exibe_lista()
 *
 *  Exibicao de todos os elementos de uma lista
 */
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

/*
 *  libera_lista()
 *
 *  Libera a memoria alocada para uma lista
 */
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

/*
 *  pega_valor()
 *
 *  Retorna o VALOR associado a um ID da lista
 */
char *pega_valor(lista_t *lista, char *id_buscado){
	lista_t *aux = busca_elemento(lista, id_buscado);

	return aux->valor;
}
