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
 *
 *  Erros: Terminal (operacao nao reconhecida)
 *         Terminal (numero de argumentos na chamada do programa eh invalido)
 *         Terminal (arquivo de saida nao contem extensao '.e'!)
 *         Terminal (arquivo de saida ja possui extensao)
 */
Operacoes_t validacao_argumentos(int argc, char* argv[]){
	// Variavel para retorno
	Operacoes_t operacao;

	//// Se o tipo de operacao eh diferente de -p -o e -l, ERROR -1
	if(tipo_operacao(argv[1])==ERRO){
		printf("Erro Terminal: operacao nao reconhecida!\n");
		exit(-1);
	}

	//// Operacao eh a ligacao
	if(tipo_operacao(argv[1])==LIGACAO){
		//// Se o numero de argumentos eh invalido para ERROR -2
		if(argc>6 || argc<5){
			printf("Erro Terminal: numero de argumentos na chamada do programa eh invalido!\nObteve-se %d argumentos.\n", argc-1);
			exit(-2);
		}

		//// Se o arquivo de saida tem extensao, ERROR -2
		// Variavel que checa a extensao do arquivo de saida
		char *validade_saida_e = ".e";

		// Se o arquivo de saida nao contem a extensao valida, ERROR -3
		if((strstr(argv[argc-1], validade_saida_e))==NULL){
			printf("Erro Terminal: Arquivo de saida nao contem extensao '.e'!\n");
			exit(-3);
		}
	}

	//// Operacao eh pre-processamento ou montagem
	else{
		//// Se o numero de argumentos eh invalido para -p e -o, ERROR -2
		if(argc!=4){
			printf("Erro Terminal: numero de argumentos na chamada do programa eh invalido!\nObteve-se %d argumentos.\n", argc-1);
			exit(-2);
		}

		//// Se o arquivo de saida tem extensao, ERROR -2
		// Variavel que checa a extensao do arquivo de saida
		char *validade_saida = ".";

		// Funcao strstr() checa se subselecao esta dentro de uma string de interesse
		if((strstr(argv[argc-1], "/")==NULL)){
				if((strstr(argv[argc-1], validade_saida))!=NULL){
					printf("Erro Terminal: Arquivo de saida ja possui extensao!\n");
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
 *  remove_espacos()
 *
 *  Remove os espacos dentro do token
 */
char* remove_espacos(char *in){
	char *out = in;

	int i = 0;
	while(i < strlen(in)){
		if((in[i] >= 48 && in[i] <= 122) || in[i]=='+'){
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

/*
 *  eh_digito()
 *
 *  Funcao que verifica se um char eh digito ou decimal a partir de uma base
 */
int eh_digito(char c, char base){
	switch(base){
		case 'd':
		case 'D':
					if(c < '0' || c > '9'){
						return 0;
					}
					else{
						return 1;
					}
					break;
		case 'h':
		case 'H':
					if(c<'0' || (c > '9' && c < 'A') || (c > 'F')){
						return 0;
					}
					else{
						return 1;
					}
					break;
		default:
					printf("\nBase nao identificada\n");
					return -1;
					break;
	}

}

/*
 *  eh_numero()
 *
 *  Funcao que verifica se um numero eh decimal ou hexadecimal a partir de uma base
 */
int eh_numero(char *numero, char base){
	int i = 0;
	switch(base){
		case 'd':
		case 'D':
				while(i < strlen(numero)){
					//Se tiver algum elemento que nao eh digito
					if(!eh_digito(numero[i], 'd')){
						return 0;
					}
					i++;
				}
				break;
		case 'h':
		case 'H':
				if(numero[0]!='0' || numero[1]!='X'){
					return 0;
				}
				i = 2;
				while(i < strlen(numero)){
					//Se tiver algum elemento que nao eh digito
					if(!eh_digito(numero[i], 'h')){
						return 0;
					}
					i++;
				}
				break;
		default:
					printf("\nBase nao identificada\n");
					return -1;
					break;
	}
	return 1;
}

/*
 *	pega_antes_mais()
 *
 *  Pega label ate '+'
 */
char* pega_antes_mais(char *token){
	int i = 0;
	char *resultado = token;

		for(i=0; i<strlen(token); i++){
			if(token[i]=='+'){
				resultado[i] = '\0';
				break;
			}
			resultado[i] = token[i];
		}
	return resultado;
}

/*
 *	pega_elemento_vetor()
 *
 *  Funcao que compara o elemento em uso de um vetor
 *  com o tamanho da estrutura respectiva, a fim de evitar
 *  manipulacoes fora dos limites do vetor
 *
 *  Erros: Sintatico (esperado um numero apos '+'!)
 *			   Semantico (endereco ultrapassa tamanho do vetor)
 *         Sintatico (label invalido)
 */
int pega_elemento_vetor(char *token, int linha, int contador_posicao){
	int depois_mais_num1 = 0;
	char *antes_mais, *depois_mais;
	int erro = 0;

	depois_mais = strstr(token, "+");
	//Se n tiver +, retorna 0
	if(depois_mais == NULL){
		return 0;
	}
	//Se possuir +
	else{
			//Vai para depois do +
			depois_mais++;
			//Se n for numero, erro
			if(!eh_numero(depois_mais, 'd')){
				printf("\nErro Sintatico (linha %d): Esperado um numero apos '+'!\n"
				, linha);
				erro = 1;
			}
			//Se for numero
			else{
				depois_mais_num1 = atoi(depois_mais);
				antes_mais = pega_antes_mais(token);
				//Tamanho do vetor - 1, pois endereco comeca em 0
				if(busca_elemento(lista_tamanhos_vetores, antes_mais)!=NULL){
					//printf("\n<%s>\n", pega_valor(lista_tamanhos_vetores, antes_mais));
					//printf("\n%s %d %d\n", antes_mais, depois_mais_num1, atoi(pega_valor(lista_tamanhos_vetores, antes_mais))-1);
					if(depois_mais_num1 > (atoi(pega_valor(lista_tamanhos_vetores, antes_mais))-1)){
						erro = 1;
						printf("\nErro Semantico (linha %d): Endereco ultrapassa tamanho do vetor\n"
						, linha);
						return -1;
					}
				}
				//Se for um simbolo externo, coloca na tabela de uso
				if(eh_externo(antes_mais)){
					//insere(tabela, instrucao, posicao, externo, eh_dado?)
					insere_tabela(tabela_uso, antes_mais, contador_posicao, 0, 0);
				}
				//Se n for externo, verifica se n eh dado valido
				else if(eh_dado(antes_mais)!=1){
					printf("\nErro Sintatico (linha %d): Label invalido!\n"
					, linha);
					erro = 1;
				}
			} //else numero
		} // else (depois_mais == NULL)

		if(erro){
			return -1;
		}

		return depois_mais_num1;
}

/*
 *	imprime_tabelas_arquivo()
 *
 *  Escrita das estruturas de dados no arquivo objeto
 */
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
