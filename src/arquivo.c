#include "arquivo.h"

/*
 *  tipo_operacao()
 *
 *  Funcao que retorna o tipo de operacao de acordo com o segundo argumento de entrada
 * do programa de traducao
 */
Operacoes_t tipo_operacao(char* string){
	// Funcao strcmp() retorna 0 se strings forem iguais
	//// -p para pre processamento
	if (!(strcmp(string, "-p"))){
		return PRE_PROC;
	}
	//// -o para montagem
	else if (!(strcmp(string, "-o"))){
		return MONTAGEM;
	}
	//// -l para ligacao
	else if (!(strcmp(string, "-l"))){
		return LIGACAO;
	}
	else{
		return ERRO;
	}
}

/*
 *  validacao_argumentos()
 *
 *  Funcao responsavel pela checagem do numero de argumentos de entrada
 * do programa de traducao
 */
Operacoes_t validacao_argumentos(int argc, char* argv[]){
	// Variavel para retorno
	Operacoes_t operacao;

	//// Se o tipo de operacao eh diferente de -p -o e -l, ERROR -1
	if(tipo_operacao(argv[1])==ERRO){
		printf("Erro: operacao nao reconhecida!\n");
		exit(-1);
	}

	//// Operacao eh a ligacao
	if(tipo_operacao(argv[1])==LIGACAO){
		//// Se o numero de argumentos eh invalido para ERROR -2
		if(argc>6 || argc<5){
			printf("Erro: numero de argumentos na chamada do programa eh invalido!\nObteve-se %d argumentos.\n", argc-1);
			exit(-2);
		}

		//// Se o arquivo de saida tem extensao, ERROR -2
		// Variavel que checa a extensao do arquivo de saida
		char *validade_saida_e = ".e";

		// Se o arquivo de saida nao contem a extensao valida, ERROR -3
		if((strstr(argv[argc-1], validade_saida_e))==NULL){
			printf("Erro: Arquivo de saida nao contem extensao '.e'!\n");
			exit(-3);
		}
	}

	//// Operacao eh pre-processamento ou montagem
	else{
		//// Se o numero de argumentos eh invalido para -p e -o, ERROR -2
		if(argc!=4){
			printf("Erro: numero de argumentos na chamada do programa eh invalido!\nObteve-se %d argumentos.\n", argc-1);
			exit(-2);
		}

		//// Se o arquivo de saida tem extensao, ERROR -2
		// Variavel que checa a extensao do arquivo de saida
		char *validade_saida = ".";

		// Funcao strstr() checa se subselecao esta dentro de uma string de interesse
		if((strstr(argv[argc-1], "/")==NULL)){
				if((strstr(argv[argc-1], validade_saida))!=NULL){
					printf("Erro: Arquivo de saida ja possui extensao!\n");
					exit(-2);
				} //if validade_saida
			} //if /
	}

	operacao = tipo_operacao(argv[1]);
	// Retorna a operacao a ser realizada
	return operacao;
}

/*
 *  string_alta()
 *
 *  Funcao que passa uma string para caixa alta
 */
void string_alta(char *s){
	for(; *s; s++){
		if(('a' <= *s) && (*s <= 'z'))
			*s = 'A' + (*s - 'a');
		}
}

/*
 *  string_baixa()
 *
 *  Funcao que passa uma string para caixa baixa
 */
void string_baixa(char *s){
	for(; *s; s++)
		if(('A' <= *s) && (*s <= 'Z'))
			*s = 'a' + (*s - 'A');
}

/*
 *
 * remove_espacos()
 *
 * Remove os espacos dentro do token
 */
char* remove_espacos(char *in){
	char *out = in;

	int i = 0;
	while(i < strlen(in)){
		if(in[i] >= 48 && in[i] <= 122){
			out[i] = in[i];
		}
		else{
			out[i] = '\0';
			i++;
		}
		//printf("%d char %c ascii %d\n", i, in[i], in[i]);
		//printf("%d char %c ascii %d\n", i, out[i], out[i]);
		i++;
	}
	return out;
}

void imprime_tabelas_arquivo(int begin_end, FILE* obj, char *obj_provisorio_nome, lista_t *mapa){
	char ch;			//Para ler bit a bit do arquivo

	FILE *obj_provisorio = fopen(obj_provisorio_nome, "r");

	if(begin_end){
			fprintf(obj, "TABLE USE\n");

			addrTab *aux = tabela_uso->prox;
			while(aux!=NULL){
				fprintf(obj, "%s %d\n", aux->simbolo, aux->posicao_memoria);
				aux = aux->prox;
			}

			fprintf(obj, "\nTABLE DEFINITION\n");

			aux = tabela_definicoes->prox;
			while(aux!=NULL){
				fprintf(obj, "%s %d\n", aux->simbolo, aux->posicao_memoria);
				aux = aux->prox;
			}

			fprintf(obj, "\nTABLE REALOCATION\n");
			lista_t *l_aux = mapa->proximo;

			while(l_aux!=NULL){
				fprintf(obj, "%s", l_aux->valor);

				l_aux = l_aux->proximo;
			} //while
				fprintf(obj, "\n\n");

		} // if (begin_end)

		//Copiar conteudo do provisorio (parte do CODE) p/ objeto
		while (1) {
			ch = fgetc(obj_provisorio);

			if(!feof(obj_provisorio)){
				fputc(ch, obj);
			}
			else{
				break;
			}
		}

	 	fclose(obj_provisorio);
		remove(obj_provisorio_nome);			//Deleta arquivo provisorio
		fclose(obj);
}
