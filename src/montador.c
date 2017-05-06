#include "montador.h"

char *tokens_linha[10];

/*
 *  seleciona_operacao()
 *
 *  Funcao responsavel pela execucao de uma operacao de acordo
 * com o segundo argumento
 */
void seleciona_operacao(int argc, char* argv[]){
	Operacoes_t operacao;

	operacao = validacao_argumentos(argc, argv);

	// Se a operacao eh ligacao -l
	if(operacao == LIGACAO){
		// Variaveis que checam as extensoes
		char *validade_entrada_o = ".o";
		int contador = 2;

		while(contador < (argc-1)){
			// Se o arquivo de entrada nao contem a extensao valida, ERROR -4
			if((strstr(argv[contador], validade_entrada_o))==NULL){
				printf("Erro: %d Arquivo a ser ligado nao contem extensao '.o'!\n", contador-1);
				exit(-4);
			}
			contador++;
		}

		// Ligacao
		ligador(contador-2, argv);

	} // ligacao

	// Se a operacao eh -p ou -o
	else{
		// Variaveis que checam as extensoes
		char *validade_entrada_pre = ".pre";
		char *validade_entrada_asm = ".asm";

		//Cria as tabelas de simbolos e de definicoes vazias
		inicializa_tabelas();

		// Se a operacao eh pre processamento -p
		if(operacao == PRE_PROC){
			// Se o arquivo de entrada nao contem a extensao valida, ERROR -4
			if((strstr(argv[2], validade_entrada_asm))==NULL){
				printf("Erro: Arquivo a ser pre-processado nao contem extensao '.asm'!\n");
				exit(-4);
			}

			// Abertura do arquivo para leitura
			FILE* fp = fopen(argv[2], "r");
			// Se o arquivo nao conseguiu ser aberto, ERROR -5
			if(fp == NULL){
				printf("Erro na abertura do arquivo!\n");
				exit(-5);
			}

			// Pre processamento
			pre_processamento(fp, argv[3]);

		} // preproc

		// Se a operacao eh montagem -o
		if(operacao == MONTAGEM){
			// Se o arquivo de entrada nao contem as extensoes validas, ERROR -4
			if((strstr(argv[2], validade_entrada_pre)==NULL && strstr(argv[2], validade_entrada_asm)==NULL)){
				printf("Erro: Arquivo a ser montado nao contem extensao '.pre' ou '.asm'!\n");
				exit(-4);
			}

			// Abertura do arquivo para leitura
			FILE* fp = fopen(argv[2], "r");
			// Se o arquivo nao conseguiu ser aberto, ERROR -5
			if(fp == NULL){
				printf("Erro na abertura do arquivo!\n");
				exit(-5);
			}

			// Se a extensao for .asm
			if(strstr(argv[2], validade_entrada_pre)==NULL){
				// Pre-processamento seguido da passagem 1
				passagem1(pre_processamento(fp, argv[3]));
			}
			// Se for .pre
			else if (strstr(argv[2], validade_entrada_asm)==NULL){
				// Passagem 1
				passagem1(fp);
			}
			// passagem2(fp);

		} // montagem
	} // preproc ou montagem
}

/* scanner()
 * Verifica erros lexicos no programa
 * 		- contador_linha : para impressao de erro
*/
void scanner(char *linha, int contador_linha){
	if(linha == NULL){
		return;
	}

	char *token;
	int erro = 0, i = 0;

	//Espacao como caractere limitador
	token = strtok(linha, " \t,\n");

	while(token!=NULL){
		tokens_linha[i] = strdup(token);
		//Se token comeca com numero e n vem depois de uma diretiva: ERROR -6
		if(i>0 && token[0]>='0' && token[0]<='9' && (tamanho_diretiva(tokens_linha[i-1], "\0"))==-1){
			printf("Erro lexico com token '%s': inicio com digito (linha %d)\n", token, contador_linha);
			erro = 1;
		}
		//Mesma condicao da anterior, mas sem acessar fora dos limites do vetor
		else if(i==0 && token[0]>='0' && token[0]<='9'){
			printf("Erro lexico com token '%s': inicio com digito (linha %d)\n", token, contador_linha);
			erro = 1;
		}
		if(i>8){
			printf("\nExcedeu numero de tokens! (linha %d)\n", contador_linha);
			break;
		}
		// printf("<%s>\n", token);
		i++;
		//Avanca pro proximo token
		token = strtok(NULL, " \t,\n");
	}
	tokens_linha[i] = "\0";

	// for(i=0; tokens_linha[i]!="\0"; i++){
	// 	printf("Valida_Token[%d] = %s\n", i, tokens_linha[i]);
	// }

	// if(erro == 1){
	// 	exit(-6);
	// }

}

/*
 *  pre_processamento()
 *
 *  Funcao responsavel pelo pre processamento de um arquivo .asm de entrada
 * avaliando as diretivas:
 *   - EQU, 1 operando, sempre no inicio, cria um sinonimo textual para um simbolo;
 *   - IF, 1 operando, inclui a linha seguinte somente se o operando == 1.
 */
FILE* pre_processamento(FILE *entrada, char *nome_arquivo_pre){
  // while !EOF{
  // verificar se o inicio da linha eh um label e se a proxima palavra eh um EQU
  //  se for EQU, associar o label ao operando
  // verificar se o inicio da linha eh um IF
  //  se o valor do operando eh 1
  //   deixar a proxima linha
  //  se o valor do operando eh 0
  //   desconsiderar a proxima linha
  // }
  // rewind arquivo .asm
  // retornar novo arquivo .pre

	printf("\n\nPre Processamento: \n");

  // Variaveis para verificacao das linhas
  char linha[TLINHA];
  char escrita[TLINHA];
	char *aux_escrita;
  char *instrucao;
  char *token;

  // Variaveis para armazenar a lista de EQUs
  lista_t *lista_equs = (lista_t *) malloc(sizeof(lista_t));
  inicializa_lista(lista_equs);
  char *label;
  lista_t *resultado_busca;

	// Variaveis para criacao do arquivo pre processado
	FILE *pre;
	char *arquivo_saida;

	// Elaborando o nome do arquivo .pre
	arquivo_saida = strcat(nome_arquivo_pre, ".pre");
	//printf("%s\n", arquivo_saida);

	// Abertura do arquivo para escrita
  pre = fopen(arquivo_saida, "w");
	// Se o arquivo nao conseguiu ser aberto, ERROR -4
  if(pre == NULL){
    printf("Erro na abertura do arquivo!\n");
    exit(-4);
 	}

  // Variaveis para escrita das linhas e erros
	int linha_anterior_if = 0;
	int linha_atual_if = 0;
	int escreve = 0;
	int contador_linha = 0;
	int flag_equ = 0;

  while(!feof(entrada)){
    // Funcao fgets() lê até TLINHA caracteres ou até o '\n'
    instrucao = fgets(linha, TLINHA, entrada);
		contador_linha++;

		// fgets() retorna NULL, fim do pre processamento
		if(instrucao == NULL)
			break;

    // Se a linha nao eh nula
    if(instrucao[0] != '\n' && instrucao[0] != ';'){

			// Retirando os comentarios
			instrucao = strtok(instrucao, ";");

			//char c = instrucao[strlen(instrucao)-1];
			//printf("%c %d\n", c, c);

			// Formatando o arquivo .pre de acordo com a tabela ASCII
			if(instrucao[strlen(instrucao)-1] < 30
			|| instrucao[strlen(instrucao)-1] > 122){
				 instrucao[strlen(instrucao)-1] = '\n';
			}

			// Armazena a linha para escrita futura
			strcpy(escrita, instrucao);

      // 1 token, que pode ser um "IF" ou qualquer outra coisa
      // Funcao strtok() corta uma string em tokens a partir de um separador
      token = strtok(instrucao, " ");

			// Passando o token para caixa alta, para fins de comparacao
			string_alta(token);

      //// Se o 1 token eh "IF"
      if(!strcmp(token,"IF")){
        //printf("IF\n");

				// Variavel para avaliacao da escrita da linha apos o IF
				linha_anterior_if = linha_atual_if;
				linha_atual_if = 1;

        // Pega o 2 token para decidir se a linha continua ou eh desconsiderada
        if(token!=NULL){
          token = strtok(NULL, " ");
          //printf("IF %s\n", token);

					//exibe(lista_equs);

          // Busca o argumento do IF na lista de EQUs
          resultado_busca = busca_lista(lista_equs, token);

					//printf("%s\n", resultado_busca->id);
					//printf("%s\n", resultado_busca->valor);

					// Se o argumento do IF eh definido por EQU
					if(resultado_busca != NULL){
	          // IF 1, proxima linha eh escrita
	          if(!strcmp(resultado_busca->valor, "1\n")){
	            printf("IF: escreve prox\n");
							escreve = 1;
	          }
	          // IF 0, proxima linha nao eh escrita
	          else if(!strcmp(resultado_busca->valor, "0\n")){
							printf("IF: nao escreve prox\n");
							escreve = 0;
	            //printf("nao escreve prox\n");
	          }
					}
					// Operando eh 0
					else if(!strcmp(token,"1\n")){
						printf("IF: escreve prox\n");
						escreve = 1;
					}
					// Operando eh 1
					else if(!strcmp(token,"0\n")){
						printf("IF: escreve prox\n");
						escreve = 0;
					}
					// Se o operando do IF nao for EQU, nem 1, nem 0
					else if(strcmp(token, "1\n") && strcmp(token, "0\n")){
							printf("Erro Sintático (Linha %d): operando do IF possui tipo inválido!\n", contador_linha);
					}
        } // 2 token
      } // if

      //// Senao eh "IF"
      else{
        //printf("OUTRO\n");

				// Variavel para avaliacao da escrita da linha apos o IF
				linha_anterior_if = linha_atual_if;
				linha_atual_if = 0;

        // Armazena o label para guardar na lista de Equs
        label = token;
				// Retira o : do label para insercao na lista
				label[strlen(label)-1] = '\n';

        // Pega o 2 token para ver se eh um EQU ou alguma label que esta na lista de EQUS
        if(token!=NULL){
          token = strtok(NULL, " ");
          //printf("OUTRO %s\n", token);

					// Passando o token para caixa alta, para fins de comparacao
					string_alta(token);

					// Buscando o token na lista de EQUS
					resultado_busca = busca_lista(lista_equs, token);

					// INSTRUCAO OP, Eh uma instrucao com operando na lista de EQUS
					if(resultado_busca != NULL){
						// Separa o id associado da escrita
						aux_escrita = strtok(escrita, resultado_busca->id);

						// Acrescenta o valor associado na escrita
						strcat(aux_escrita, resultado_busca->valor);
						strcpy(escrita, aux_escrita);
					} // resultado_busca != NULL

          // LABEL: EQU, Eh um EQU, linha nao eh escrita no .pre
          if(!strcmp(token,"EQU")){
						printf("nao escreve atual\n");

						// Se as EQUs nao estao no comeco do codigo
						if(flag_equ == 1){
							printf("Erro semântico (Linha %d): EQU não está no início do código\n", contador_linha);
						}

            // Pega o 3 token, que eh o operando de EQU
            if(token!=NULL){
              token = strtok(NULL, " ");

							// Se o operando do EQU nao for um numero
							if(*token < 48 ||
							   *token > 57){
								 printf("Erro sintático (Linha %d): operando do EQU possui tipo inválido!\n\n", contador_linha);
							}

              // Insere na lista de equs
							insere_lista(lista_equs, label, token);
            } // 3 token
          } // token == EQU

          // INSTRUCAO OP || LABEL: DIRETIVA OP, linha eh escrita, dependendo se tem IF antes
          else{
						flag_equ = 1;

						// Pega o 3 token, se ele nao for nulo, eh uma diretiva
						if(token!=NULL){
							token = strtok(NULL, " ");

							// LABEL: DIRETIVA OP, diretivas podem conter operandos com elemento terminal
							if(token!=NULL){
								// Buscando o token na lista de EQUS
								resultado_busca = busca_lista(lista_equs, token);

								// Operando esta na lista de EQUS
								if(resultado_busca != NULL){
									// Separa o id associado da escrita
									aux_escrita = strtok(escrita, resultado_busca->id);

									// Acrescenta o valor associado na escrita
									strcat(aux_escrita, resultado_busca->valor);
									strcpy(escrita, aux_escrita);
								} // resultado_busca != NULL
							} // diretiva
						} // 3 token

            printf("escreve atual (depende se tem IF antes)\n");

						//printf("%d, %d\n", linha_anterior_if, linha_atual_if);

						// Depende do IF para saber se a linha sera escrita
						if(linha_anterior_if == 1){

							// So escreve quando a avaliacao do if for 1
							if(escreve == 1){
								fputs(escrita, pre);
							}
						}
						// Linha que nao possui diretivas e independe do IF
						else{
							fputs(escrita, pre);
						}
          }
        } // 2 token
      } // else

    } // instrucao != NULL

  } // while (!feof)

	// Fecha o arquivo .pre
	fclose(pre);

	// Fecha o arquivo .asm de entrada
	fclose(entrada);

	//exibe_equ(lista_equs);

	// Libera a memoria alocada para a lista de EQUS
	libera_lista(lista_equs);

	//Abre pra passar pra passagem1
	pre = fopen(arquivo_saida, "r");
	printf("\nArquivo pre-processado gerado!\n");
	return pre;
}



/* passagem1()
 *
 * Funcao responsavel pela 1 passagem do montador, recebendo um arquivo .pre ou .o
 *
 * Passagem 1 : informacoes de definicoes de rotulos, simbolos, etc
 * Armazena os dados na Tabela de Simbolos e Tabela de definicoes (subconjunto da TS)

 * Estruturas de dados a ser usadas:
 * 		- Contador de linhas : indica qual linha do arquivo esta (envio de erros)
 *		- Contador de posicao: endereco de memoria a ser colocado simbolo
 *		- Tabela de simbolos : rotulos e simbolos declarados no programa
 *		- Tabela de diretivas: instrucoes e diretivas reconhecidas pelo montador
 *		- (TODO) Tabela de definicoes: subconjunto da TS, para o ligador usar
*/
FILE* passagem1(FILE *pre_processado){
	if(pre_processado == NULL){
	    printf("Erro na abertura do arquivo!\n");
	    exit(-4);
 	}
	int contador_posicao = 0;
	int contador_linha = 1;
	int i = 0;
	int pulo = 0;



	//Cria as tabelas de simbolos e de definicoes vazias
	inicializa_tabelas();


	char linha[TLINHA];
	char *instrucao;
	char *label;
	char *elemento;

	while(!feof(pre_processado)){
	    // Funcao fgets() lê até TLINHA caracteres ou até o '\n'
	    instrucao = fgets(linha, TLINHA, pre_processado);

	    if(instrucao==NULL){
	    	break;
	    }
	    //Se a linha nao for nula
	    if(instrucao[0]!='\n' && instrucao[1]!='\0'){

		    //Scanner coloca em tokens_linha um vetor com os tokens da linha
		    scanner(instrucao, contador_linha);

		    //Analisar todos os tokens da linha
		    for(i=0; tokens_linha[i]!="\0"; i++){
		    	elemento = tokens_linha[i];
		    	//Se ṕossuir : eh label
		    	if(strstr(elemento, ":")!=NULL){
		    		//Verifica se : esta no fim do token
		    		if(elemento[strlen(elemento)-1]!=':'){
		    			printf("\nErro na linha %d! Rótulo Inválido! ':' no meio do token\n", contador_linha);
		    		}
		    		else{
		    			label = elemento;
		    			//Retira ':'
		    			label[strlen(label)-1] = '\0';
		    			if(pertence_tabela(tabela_simbolos, label)){
		    				printf("\nErro na linha %d! Simbolo redefinido!\n", contador_linha);
		    			}
		    			else{
		    				insere_tabela(tabela_simbolos, label, contador_posicao);
		    			} //else pertence_tabela()
		    		} //else elemento :
		    	} //if(strstr(elemento, ":")!=NULL)
		    	//Se n for label, pode ser operacao ou diretiva
		    	else{
		    		//Se achou na tabela de instrucoes, retorna diferente de -1
		    		pulo = tamanho_instrucao(elemento);
		    		if(pulo!=-1){
		    			contador_posicao += pulo + 1;
		    			//Break pois n precisa olhar os operandos
		    			break;
		    		}
		    		//Se n tiver achado na Tab Instrucoes, procura na de diretivas
		    		else{
		    		pulo = tamanho_diretiva(elemento, tokens_linha[i+1]);
		    		//Se tiver achado na tabela de diretivas
			    		if(pulo!= -1){
			    			contador_posicao += pulo;
			    			break;
			    		}
			    	//Se n tiver achado em nenhuma das 2 tabelas, erro
			    		else{
			    			printf("\nErro na linha %d! Operacao nao identificada\n", contador_linha);
			    			break;
			    		} // else (pulo!=-1) (diretiva)
		    		} //else (pulo!=-1) (instrucao)
		    	} //else (strstr(elemento, ";"))
		    } //for
		} // if instrucao nao eh nula
		contador_linha = contador_linha + 1;
  } // while (!feof)

  fclose(pre_processado);
} //passagem1()


void imprime_tokens(){
	int i=0;

	for(i=0; tokens_linha[i]!="\0"; i++){
		printf("\nToken <%s>\n", tokens_linha[i]);

		if(strstr(tokens_linha[i],"\n")!=NULL){
			return;
		}
	}
}
