#include "montador.h"
#include "listas.c"

// Definicao do tamanho maximo de uma linha
#define TLINHA 100

/*
 *  seleciona_operacao()
 *
 *  Funcao responsavel pela execucao de uma operacao de acordo
 * com o segundo argumento
 */
void seleciona_operacao(Operacoes_t operacao, char* argv[]){
	// Variaveis que checam as extensoes
	char *validade_entrada_pre = ".pre";
	char *validade_entrada_asm = ".asm";

  // Abertura do arquivo para leitura
  FILE* fp = fopen(argv[2], "r");
  // Se o arquivo nao conseguiu ser aberto, ERROR -4
  if(fp == NULL){
    printf("Erro na abertura do arquivo!\n");
    exit(-4);
 	}

	// Se a operacao eh pre processamento -p
	if(operacao == PRE_PROC){
		// Se o arquivo de entrada nao contem a extensao valida, ERROR -5
		if((strstr(argv[2], validade_entrada_asm))==NULL){
			printf("Erro: Arquivo especificado nao contem extensao '.asm'!\n");
			exit(-5);
		}
    // Pre processamento
    pre_processamento(fp, argv[3]);
	}

	// Se a operacao eh montagem -o
	if(operacao == MONTAGEM){
		// Se o arquivo de entrada nao contem as extensoes validas, ERROR -5
		if((strstr(argv[2], validade_entrada_pre)==NULL || strstr(argv[2], validade_entrada_asm)==NULL)){
			printf("Erro: Arquivo especificado nao contem extensao '.pre' ou '.asm'!\n");
			exit(-5);
		}
    // Montagem
    //passagem1(fp);
    //passagem2(fp);
	}
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

  // Variaveis para verificacao das linhas
  char linha[TLINHA];
	char escrita[TLINHA];
  char *instrucao;
  char *token;

  // Variaveis para armazenar os EQUs
  struct Equ_t *lista_equs = (struct Equ_t *) malloc(sizeof(struct Equ_t));
  inicializa_equ(lista_equs);
  char *label;
  struct Equ_t *resultado_busca;

	// Variaveis para criacao do arquivo pre processado
	FILE *pre;
	char *arquivo_saida;

	// Elaborando o nome do arquivo .pre
	arquivo_saida = strcat(nome_arquivo_pre, ".pre");
	printf("%s\n", arquivo_saida);

	// Abertura do arquivo para escrita
  pre = fopen(arquivo_saida, "w");
	// Se o arquivo nao conseguiu ser aberto, ERROR -4
  if(pre == NULL){
    printf("Erro na abertura do arquivo!\n");
    exit(-4);
 	}

  // Variaveis para escrita das linhas
	int linha_anterior_if = 0;
	int linha_atual_if = 0;
	int escreve = 0;

  while(!feof(entrada)){
    // Funcao fgets() lê até TLINHA caracteres ou até o '\n'
    instrucao = fgets(linha, TLINHA, entrada);

    // Se a linha nao eh nula
    if(instrucao[0] != '\n' && instrucao[1] != '\0'){
			// Armazena a linha para escrita futura
			strcpy(escrita, instrucao);

      // 1 token, que pode ser um "IF" ou qualquer outra coisa
      // Funcao strtok() corta uma string em tokens a partir de um separador
      token = strtok(instrucao, " ");

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

          // Busca o rotulo na lista de equs
          resultado_busca = busca_equ(lista_equs, token);

					//printf("%s\n", resultado_busca->id);
					//printf("%s\n", resultado_busca->valor);

          // IF 1, proxima linha eh escrita
          if(!strcmp(resultado_busca->valor, "1\n")){
            printf("escreve prox\n");
						escreve = 1;
          }
          // IF 0, proxima linha nao eh escrita
          else{
						escreve = 0;
            //printf("nao escreve prox\n");
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

        // Pega o 2 token para ver se eh um EQU
        if(token!=NULL){
          token = strtok(NULL, " ");
          //printf("OUTRO %s\n", token);

          // LABEL: EQU, linha nao eh escrita no .pre
          if(!strcmp(token,"EQU")){
						printf("nao escreve atual\n");

            // Pega o 3 token, que eh o operando de EQU
            if(token!=NULL){
              token = strtok(NULL, " ");
              //printf("EQU %s\n", token);

              // Insere na lista de equs
							insere_equ(lista_equs, label, token);
            } // 3 token
          }
          // Linha eh escrita no .pre
          else{
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

	// Rebobina o arquivo de entrada
	rewind(entrada);

	//exibe_equ(lista_equs);

	// Libera a memoria alocada para a lista de EQUS
	libera_equ(lista_equs);
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
*/
FILE* passagem1(FILE *pre_processado){
	if(pre_processado == NULL){
		//printf("")
	}
	int contador_posicao = 0;
	int contador_linha = 1;
}
