#include "tabelas.h"

const opTab tabela_instrucoes[14] = {
	{"ADD", 1, 1}, {"SUB", 1, 2},
	{"MULT", 1, 3}, {"DIV", 1, 4},
	{"JMP", 1, 5}, {"JMPN", 1, 6},
	{"JMPP", 1, 7}, {"JMPZ", 1, 8},
	{"COPY", 2, 9}, {"LOAD", 1, 10},
	{"STORE", 1, 11}, {"INPUT", 1, 12},
	{"OUTPUT", 1, 13}, {"STOP", 0, 14}
};

const dirTab tabela_diretivas[7] = {
	//-1 Indica q numero de operandos e tamanho
	// eh variavel
	{"SECTION", 1, 0}, {"SPACE", 0, 1},
	{"CONST", 1, 1}, {"PUBLIC", 0, 0},
	{"EXTERN", 0, 0}, {"BEGIN", 0, 0},
	{"END", 0, 0}

};

addrTab* tabela_simbolos;
addrTab* tabela_definicoes;
addrTab* tabela_uso;

void imprime_instrucoes_diretivas(){
	int i = 0;

	printf("\n\nTabela Insrucoes:\n");
	for(i=0; i<14; i++){
		printf("Nome: <%s>; Ops: <%d>; Opcode: <%d>\n", tabela_instrucoes[i].nome, tabela_instrucoes[i].ops, tabela_instrucoes[i].opcode);
	}
	printf("\n\nTabela Diretivas:\n");

	for(i=0; i<7; i++){
		printf("Nome: <%s>; Ops: <%d>; Tamanho: <%d>\n", tabela_diretivas[i].nome, tabela_diretivas[i].ops, tabela_diretivas[i].tamanho);
	}
}
//Retorna numero de operandos da instrucao de interesse
int tamanho_instrucao(char *operacao){
	int i, achou = 0, retorno = 0;

	for (i = 0; i<14; i++){
		//Se achou a instrucao
		if(!(strcmp(operacao, tabela_instrucoes[i].nome))){
			achou = 1;
			retorno = tabela_instrucoes[i].ops;
		} // if
	} // for

	//Se nao achou instrucao
	if(achou == 0){
		return -1;
	}

	return retorno;
}

int opcode(char *simbolo){
	int i, achou = 0, retorno = 0;

	for (i = 0; i<14; i++){
		//Se achou a instrucao
		if(!(strcmp(simbolo, tabela_instrucoes[i].nome))){
			achou = 1;
			retorno = tabela_instrucoes[i].opcode;
		} // if
	} // for

	//Se nao achou instrucao
	if(achou == 0){
		return -1;
	}

	return retorno;
}


int tamanho_diretiva(char *diretiva){
	int i, achou = 0, retorno = 0;
	int op_space = 0;


	for (i = 0; i<7; i++){
		//Se achou a instrucao
		if(!(strcmp(diretiva, tabela_diretivas[i].nome))){
			achou = 1;
			retorno = tabela_diretivas[i].tamanho;
		} // if
	} // for


	//Se nao achou instrucao
	if(achou == 0){
		return -1;
	}

	return retorno;
}


//Cria a TS, TD e Tab de Uso
void inicializa_tabelas(){
	tabela_simbolos = (addrTab *) malloc(sizeof(addrTab));
	tabela_simbolos->prox = NULL;

	tabela_definicoes = (addrTab *) malloc(sizeof(addrTab));
	tabela_definicoes->prox = NULL;

	tabela_uso = (addrTab *) malloc(sizeof(addrTab));
	tabela_uso->prox = NULL;
}

/*addrTab* cria_tabela(){
	addrTab *aux = (addrTab*) malloc(sizeof(addrTab));

	aux->prox = NULL;
	return aux;
}*/

addrTab* busca_simbolo(addrTab* tabela, char* nome){
	addrTab* aux = tabela;

	while(aux!=NULL){
		if(!strcmp(nome, aux->simbolo)){
			return aux;
		}
		aux = aux->prox;
	}

	return NULL;
}

//Funcao que copia as posicoes dos simbolos para
//a tabela definicoes ao final da passagem 1
void copia_para_definicoes(){
	addrTab* aux = tabela_definicoes;
	addrTab* simbolo;

	while(aux!=NULL){
		simbolo = busca_simbolo(tabela_simbolos, aux->simbolo);
		if(simbolo != NULL){
			aux->posicao_memoria = simbolo->posicao_memoria;
			aux->data = simbolo->data;
		}
		aux = aux->prox;
	}
}

int pertence_tabela(addrTab* tabela, char* nome){
	addrTab *aux = busca_simbolo(tabela, nome);

	if(aux == NULL){
		return 0;
	}

	return 1;
}

int busca_posicao_memoria(addrTab* tabela, char* nome){
	addrTab *aux = busca_simbolo(tabela, nome);

	if(aux == NULL){
		return -1;
	}

	return aux->posicao_memoria;
}

int esta_vazia(addrTab* tabela){
	if(tabela == NULL){
		return 0;
	}
	if(tabela->prox == NULL){
		return 1;
	}

	return 0;
}

int eh_dado(char*simbolo){
	addrTab *aux = busca_simbolo(tabela_simbolos, simbolo);

	if(aux == NULL){
		return -1;
	}

	return aux->data;
}

int eh_externo(char *simbolo){
	addrTab *aux = busca_simbolo(tabela_simbolos, simbolo);

	if(aux == NULL){
		return 0;
	}

	return aux->externo;
}

void insere_tabela(addrTab *tabela, char *nome, int posicao, int externo, int data){
	//Tabela de uso pode ter mais de um label repetido
	if(pertence_tabela(tabela, nome) && tabela !=tabela_uso){
	 	return;
		}

	addrTab *novo = (addrTab *) malloc(sizeof(addrTab));

	strcpy(novo->simbolo, nome);
	novo->posicao_memoria = posicao;
	novo->externo = externo;
	novo->data = data;
	novo->prox = tabela->prox;

	tabela->prox = novo;

	return;
}


void imprime_tabela(addrTab *tabela){
	if(tabela==NULL){
		return;
	}

	if (esta_vazia(tabela)){
		printf("Tabela esta vazia\n\n");
		return;
	}


	addrTab *aux = tabela->prox;
	while(aux!=NULL){
		printf("Simbolo = %s, Posicao = %d, Externo = %d, Dado = %d\n",
		aux->simbolo, aux->posicao_memoria, aux->externo, aux->data);

		aux = aux->prox;
	}

	printf("\n\n");
	return;
}
