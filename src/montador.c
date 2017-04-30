#include "montador.h"

// Definicao do tamanho maximo de uma linha
#define TLINHA 100

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
    //pre_processamento(fp);
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
	token = strtok(linha, " \t,");

	while(token!=NULL){
		//Se token comeca com numero, ERROR -6
		if(token[0]>='0' && token[0]<='9'){
			printf("Erro lexico com token '%s': inicio com digito (linha %d)\n", token, contador_linha);
			erro = 1;
		}
		if(i>8){
			printf("\nExcedeu numero de tokens!\n");
			break;
		}
		// printf("<%s>\n", token);

		tokens_linha[i] = strdup(token);
		i++;

		token = strtok(NULL, " \t,");
	}
	tokens_linha[i] = "\0";

	// for(i=0; tokens_linha[i]!="\0"; i++){
	// 	printf("Valida_Token[%d] = %s\n", i, tokens_linha[i]);
	// }

	// if(erro == 1){
	// 	exit(-6);
	// }	
}

// struct{
  
// };
/*
 *  pre_processamento()
 *
 *  Funcao responsavel pela pre pre_processamento de um arquivo .asm de entrada
>>>>>>> origin/lucas
 * avaliando as diretivas:
 *   - EQU, 1 operando, sempre no inicio, cria um sinonimo textual para um simbolo;
 *   - IF, 1 operando, inclui a linha seguinte somente se o operando == 1.
 */
FILE* pre_processamento(FILE *entrada){
  //while !EOF{
  // verificar se o inicio da linha eh um label e se a proxima palavra eh um EQU
  //  se for EQU, associar o label ao operando
  // verificar se o inicio da linha eh um IF
  //  se o valor do operando eh 1
  //   deixar a proxima linha
  //  se o valor do operando eh 0
  //   desconsiderar a proxima linha
  //}
  //rewind arquivo .asm
  //retornar novo arquivo .pre

  char linha[TLINHA];
  char *instrucao;
  char *token;
  //bool escreve_prox;

  while(!feof(entrada)){
    // Funcao fgets() lê até TLINHA caracteres ou até o '\n'
    instrucao = fgets(linha, TLINHA, entrada);

    // 1 token, que pode ser um "IF" ou qualquer outra coisa
    // Funcao strtok() corta uma string em tokens a partir de um separador
    token = strtok(instrucao, " ");

    // Se o 1 token eh "IF"
    if(!strcmp(token,"IF")){
      // Pega o 2 token para decidir se a linha continua ou eh desconsiderada
      if(token!=NULL){
        token = strtok(NULL, " ");

        // IF 1, proxima linha eh escrita
        if(!strcmp(token,"1")){
          //escreve_prox;
        }
        // IF 0, proxima linha nao eh escrita
        else{
          //!escreve_prox;
        } // if strcmp(token,"1")
      } // if (token!=NULL)
    }
    // Se o 1 token nao eh "IF"
    else{
      // Pega o 2 token para ver se eh um EQU
      if(token!=NULL){
        token = strtok(NULL, " ");

        // LABEL: EQU
        if(!strcmp(token,"EQU")){
          // Pega o 3 token, que eh o operando de EQU
          if(token!=NULL){
            token = strtok(NULL, " ");

          } // if (token!=NULL)
        }
        // Linha eh escrita
        else{
          //escreve_atual
        } // if strcmp(token,"EQU")
      } // if (token!=NULL)
    } // if strcmp(token,"IF")

  } // while (!feof)
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

	//Cria as tabelas de simbolos e de definicoes vazias
	inicializa_tabelas();
	
	char linha[TLINHA];
	char *instrucao;

	while(!feof(pre_processado)){
	    // Funcao fgets() lê até TLINHA caracteres ou até o '\n'
	    instrucao = fgets(linha, TLINHA, pre_processado);
	    //Scanner coloca em tokens_linha um vetor com os tokens da linha
	    scanner(instrucao, contador_linha);

  } // while (!feof)
}

