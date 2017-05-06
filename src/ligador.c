#include "ligador.h"

/*
 *  ligador()
 *
 *  Funcao responsavel pela ligacao de 2 ou 3 arquivos objeto.
 */
void ligador(int num_objetos, char* argv[]){
  //ler os arquivos objetos
  //alinhar
  //fatores de correcao = tamanho do arquivo objeto lido
  //tabela global de definicoes usando fatores de correcao
  //corrige o endereco das entradas da tabela de uso
  //corrige os enderecos do codigo com fator de correcao
  //corrige os enderecos relativos usando fator de correcao
  //gera o aqruivo.e somente com os opcodes e operandos

  // Variaveis para obtencao da linha do .o
  int contador_objetos = 0;
  char linha[TLINHA];
  char *elemento;
  char *token;
  char *token2;

  // Sinaliza em qual parte do .o a info esta
  int flag = 0;

  // Vetores para armazenar as tabelas de cada arquivo
  int contador = 0;
  lista_t *tabela_uso[num_objetos];
  while (contador < num_objetos) {
    tabela_uso[contador] = (lista_t *) malloc(sizeof(lista_t));
    inicializa_lista(tabela_uso[contador]);
    contador++;
  }
  contador = 0;
  lista_t *tabela_definicao[num_objetos];
  while (contador < num_objetos) {
    tabela_definicao[contador] = (lista_t *) malloc(sizeof(lista_t));
    inicializa_lista(tabela_definicao[contador]);
    contador++;
  }
  char *tabela_realocao[num_objetos];
  char *codigo[num_objetos];

  // Variaveis auxiliares para armazenamento da tabela de realocao e do codigo
  char info_realocacao[TLINHA];
  char info_codigo[TLINHA];

  // Fatores de correcao de cada arquivo
  int fator_correcao[num_objetos];
  char *conta_char;

  // Enquanto os arquivos objetos nao foram processados
  while(contador_objetos!=num_objetos){
    printf(":::::::::::::::: ARQUIVO OBJETO %d\n", contador_objetos+1);

    // Abertura do arquivo para leitura
    FILE* fp = fopen(argv[contador_objetos+num_objetos], "r");
    // Se o arquivo nao conseguiu ser aberto, ERROR -5
    if(fp == NULL){
      printf("Erro na abertura do arquivo!\n");
      exit(-5);
    }

    while(!feof(fp)){
      // Funcao fgets() lê até TLINHA caracteres ou até o '\n'
      elemento = fgets(linha, TLINHA, fp);

      // fgets() retorna NULL, fim do pre processamento
      if(elemento == NULL)
        break;

      if(elemento[0] != '\n'){
        // Determinando qual eh o tipo da info adquirida
        if(!strcmp(elemento,"TABLE USE\n")){
          // Info eh um elemento da tabela de uso
          flag = 1;
        }
        else if(!strcmp(elemento,"TABLE DEFINITION\n")){
          // Info eh um elemento da tabela de definicao
          flag = 2;
        }
        else if(!strcmp(elemento,"TABLE RELOCATION\n")){
          // Info eh um elemento da tabela de realocacao
          flag = 3;
        }
        else if(!strcmp(elemento,"CODE\n")){
          // Info eh o codigo objeto
          flag = 4;
        }

        // Tratamento da info adquirida
        if(flag == 1){
          // Pega o primeiro token que representa o simbolo
          token = strtok(elemento, " ");

          // Variavel para nao alterar o valor do token
          token2 = token;

          // Pega o segundo token, que representa o endereco
          if(token2!=NULL && strcmp(token2,"TABLE")){
            token2 = strtok(NULL, " ");

            // printf("TK: %s\n", token);
            // printf("TK2: %s\n", token2);

            // Insere na tabela de uso do arquivo corrente
            insere_lista(tabela_uso[contador_objetos], token, token2);
            //exibe_lista(tabela_uso[contador_objetos]);
          }
        } // uso

        else if(flag == 2){
          // Pega o primeiro token que representa o simbolo
          token = strtok(elemento, " ");

          // Variavel para nao alterar o valor do token
          token2 = token;

          // Pega o segundo token, que representa o endereco
          if(token2!=NULL && strcmp(token2,"TABLE")){
            token2 = strtok(NULL, " ");

            // printf("TK: %s\n", token);
            // printf("TK2: %s\n", token2);

            // Insere na tabela de uso do arquivo corrente
            insere_lista(tabela_definicao[contador_objetos], token, token2);
            //exibe_lista(tabela_definicao[contador_objetos]);
          }
        } // definicao

        else if(flag == 3){
          // Armazenamento da linha em um vetor
          strcpy(info_realocacao, elemento);

          // Fator de correcao
          fator_correcao[contador_objetos] = 0;
          // Se nao for o primeiro .o
          if(contador_objetos > 0){
            contador = 0;
            // Conta o numero de enderecos sinalizados na tabela de realocao
            while(info_realocacao[contador] != '\0'){
              contador++;
            }
            // Armazena o fator de correcao
            fator_correcao[contador_objetos] = contador-1;
          }

          // Insere na tabela de realocacao do arquivo corrente
          tabela_realocao[contador_objetos] = info_realocacao;
          //printf("%s\n", tabela_realocao[contador_objetos]);

        } // realocao

        else if(flag == 4){
          // Armazenamento da linha em um vetor
          strcpy(info_codigo, elemento);
          // Guarda o codigo objeto do arquivo corrente
          codigo[contador_objetos] = info_codigo;
          //printf("%s\n", codigo[contador_objetos]);

        } // codigo

      } // linha != \n

    } // feof

    printf("Tabela de USO");
    exibe_lista(tabela_uso[contador_objetos]);
    printf("Tabela de DEFINICAO");
    exibe_lista(tabela_definicao[contador_objetos]);
    printf("Tabela de REALOCACAO\n");
    printf("%s\n", tabela_realocao[contador_objetos]);
    printf("CODIGO OBJETO\n");
    printf("%s\n", codigo[contador_objetos]);
    printf("FATOR CORRECAO\n");
    printf("%d\n", fator_correcao[contador_objetos]);

    // Fecha o arquivo objeto atual
    fclose(fp);

    // Passa para o proximo arquivo objeto
    contador_objetos++;
  }

  return;
}
