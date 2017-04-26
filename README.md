# MacroAssembler
Trabalho 1 de Software Básico 1/2017

### 1 - Introdução
O trabalho consiste em implementar em C/C++ um método de tradução de uma
linguagem de montagem simples para uma representação de código objeto. O tradutor
a ser implementado ser ́a um Macro-Assembler da linguagem hipotética vista em sala
de aula.

### 2 - Objetivo
Fixar o funcionamento de um processo de tradução.  Especificamente as etapas
de analise léxica, sintática e semântica, etapa de geração de código objeto e ligação


O montador deve ser capaz de:

• NÃO ser sensível ao caso, podendo aceitar instruções/diretivas/rótulos em maiúsculas
e minúsculas.

• A seção de dados deve vir depois da seção de códigos.

• Gerar um arquivo de de saída em formato TEXTO (mais detalhes serão descritos
a seguir).

• Desconsiderar tabulações e espacos desnecessários em qualquer lugar do código.

• A diretiva CONST deve aceitar números positivos e negativos (inteiros e hexa-
decimal);

• Deve ser possível trabalhar com vetores (SPACE com operando, e usar operações
do tipo:  LABEL+Número)

• Capacidade de aceitar comentários indicados pelo símbolo “;”

• O  comando  COPY  deve  utilizar  uma  vírgula  SEM  espaco  entre  os  operandos
(COPY A,B)

• Identificar erros durante a montagem. Montado sempre o programa inteiro e mos-
trando na tela aa LINHAS e TIPO DOS ERROS (léxico, sintático, semântico).

#### O programa deve pelo menos detectar os seguintes tipos de erro:
  
  
    – declarações ausentes;
    – declarações repetidas;
    – pulo para rótulos inválidos;
    – diretivas inválidas;
    – instru ̧cões inválidas;
    – diretivas ou instruções na seção errada;
    – divisão por zero;
    – instruções com a quantidade de operando inválida;
    – tokens inválidos;
    – dois rótulos na mesma linha;
    – rótulos repetidos;
    – seção TEXT faltante;
    – seção inválida;
    – tipo de argumento inválido;
    – endere ̧co de memória não reservado (incluındo tratamento de vetores, ou seja
    somente deve ser possível ter acesso a vetores dentro do tamano reservado
    para cada um deles);
    – modificação de um valor constante.
    – se  não  for  um  módulo  deve  possuir  pelo  menos  uma  instrução  de  STOP
    (podendo ter mais que uma, a não ser que seja utililzado as diretivas BEGIN
    e END. Nesse caso não deve ser verificado este erro)
    – Falta de diretive END ou BEGIN (caso exista a outra)
    – Erros de ligação (verificar parte de ligador)
