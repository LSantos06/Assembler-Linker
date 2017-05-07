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
  char tabela_realocao[num_objetos][TLINHA];
  char codigo[num_objetos][TLINHA];

  // Tamanho do objeto que determina o fator de correcao
  char aux_tamanho[TLINHA];
  int tamanho_objeto[num_objetos];
  int fator_correcao[num_objetos];

  //// Obtendo as informacoes de cada .o
  // Enquanto os arquivos objetos nao foram processados
  while(contador_objetos!=num_objetos){

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
            insere_elemento(tabela_uso[contador_objetos], token, token2);
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
            insere_elemento(tabela_definicao[contador_objetos], token, token2);
            //exibe_lista(tabela_definicao[contador_objetos]);
          }
        } // definicao

        else if(flag == 3){
          // Insere na tabela de realocacao do arquivo corrente
          strcpy(tabela_realocao[contador_objetos], elemento);
          //printf("%s\n", tabela_realocao[contador_objetos]);

          // Armazenamento da linha em um vetor
          strcpy(aux_tamanho, elemento);

          // Fator de correcao
          contador = 0;
          // Conta o numero de enderecos sinalizados na tabela de realocao
          while(aux_tamanho[contador] != '\0'){
            contador++;
          }
          // Armazena o fator de correcao
          tamanho_objeto[contador_objetos] = contador-1;

        } // realocacao

        else if(flag == 4){
          elemento[strlen(elemento)-1] = ' ';
          // Guarda o codigo objeto do arquivo corrente
          strcpy(codigo[contador_objetos], elemento);
          //printf("%s\n", codigo[contador_objetos]);

        } // codigo

      } // linha != \n

    } // feof

    // Determinando os fatores de correcao
    if(contador_objetos == 0){
      // Se for o primeiro objeto eh 0
      fator_correcao[contador_objetos] = 0;
    }
    else{
      // Fator de correcao eh igual ao tamanho do objeto anterior
      fator_correcao[contador_objetos] = tamanho_objeto[contador_objetos-1];
    }

    // Fecha o arquivo objeto atual
    fclose(fp);

    // Passa para o proximo arquivo objeto
    contador_objetos++;
  }

  contador = 0;
  while(contador < num_objetos){
    printf("\n::::::::::::ARQUIVO OBJETO %d\n\n", contador+1);
    printf("Tabela de USO");
    exibe_lista(tabela_uso[contador]);
    printf("Tabela de DEFINICAO");
    exibe_lista(tabela_definicao[contador]);
    printf("Tabela de REALOCACAO\n");
    printf("%s\n", tabela_realocao[contador]);
    printf("CODIGO OBJETO\n");
    printf("%s\n\n", codigo[contador]);
    printf("TAMANHO OBJETO\n");
    printf("%d\n\n", tamanho_objeto[contador]);
    printf("FATOR CORRECAO\n");
    printf("%d\n", fator_correcao[contador]);

    contador++;
  }

  // Variavel que contem o código final a ser impresso no .e
  char *codigo_final;

  //// Processo de ligacao
  // Alinhamento dos dois codigos
  codigo_final = strcat(codigo[0], codigo[1]);
  printf("\n:::::::::::::CODIGO INICIAL\n%s\n", codigo_final);

  //// Tabela global de definicoes (TGD)
  lista_t *TGD = (lista_t *) malloc(sizeof(lista_t));
  inicializa_lista(TGD);

  // Variavel para guardar o valor com o fator de correcao
  int valor_corrigido;
  // Variavel auxiliar para converter inteiro para string
  char string_valor_corrigido[15];

  lista_t *resultado_busca;

  // Aplicando o fator de correcao nas tabelas de definicoes
  contador = 1;
  while (contador < num_objetos) {
    lista_t *aux = tabela_definicao[contador];

    // Percorre a lista do objeto
    while(aux->proximo != NULL){
      aux = aux->proximo;

      // Aplicando o fator de correcao ao valor
      valor_corrigido = atoi(aux->valor) + fator_correcao[contador];

      // Passando o valor corrigido para string
      sprintf(string_valor_corrigido, "%d", valor_corrigido);

      // Insere o elemento corrigido na TGD
      insere_elemento(TGD, aux->id, string_valor_corrigido);
    }
    //exibe_lista(TGD);
    contador++;
  }

  // Insere a primeira tabela de definicoes sem fator de correcao
  TGD = insere_lista(TGD, tabela_definicao[0]);
  printf("\n:::::::::::::TGD");
  exibe_lista(TGD);

  resultado_busca = busca_elemento(tabela_uso[0], "Y");
  if(resultado_busca != NULL){
    printf("ID %s\n", resultado_busca->id);
    printf("VALOR %s\n", resultado_busca->valor);
  }
  //exibe_lista(resultado_busca);

  // Referencias cruzadas utilizando enderecos da TGD
  // Enderecos impares marcados com 0 na tabela de realocacao

  // Aplica fator de correcao aos enderecos relativos no codigo
  // Enderecos marcados com 1 na tabela de realocacao

  return;
}
