# MacroAssembler
### Trabalho 1 de Software Básico 1/2017
O trabalho consiste em implementar em C/C++ um método de tradução de uma
linguagem de montagem simples para uma representação de código objeto. O tradutor
a ser implementado ser ́a um Macro-Assembler da linguagem hipotética vista em sala
de aula.

### Integrantes do grupo
* Davi Rabbouni - 15/0033010
* Lucas Santos - 14/0151010

### Instruções de compilação
A compilação do projeto é feita por meio de um **makefile**, a seguir seguem as opções disponíveis para o mesmo:
```shell
make
  # Realiza a compilação do projeto 
  
make clean
  # Limpa os arquivos objeto
  
make preproc file_name=
  # Realiza o pre-processamento de um arquivo .asm 
  # Possui o argumento:
  #   file_name, que deve ser o nome do arquivo .asm, sem extensão  
  
make valpreproc file_name=
  # Realiza o pre-processamento de um arquivo .asm, com análise de memory leak por meio do valgrind
  
make monta_asm file_name=
  # Realiza a montagem de um arquivo .asm 
  # Possui o argumento:
  #   file_name, que deve ser o nome do arquivo .asm, sem extensão  
  
make valmonta_asm file_name=
  # Realiza a montagem de um arquivo .asm, com análise de memory leak por meio do valgrind
  
make monta_pre file_name=
  # Realiza a montagem de um arquivo .pre 
  # Possui o argumento:
  #   file_name, que deve ser o nome do arquivo .pre, sem extensão
  
make valmonta_pre file_name=
  # Realiza a montagem de um arquivo .pre, com análise de memory leak por meio do valgrind
  
make liga o1= o2= o3= e=
  # Realiza a ligação de 2 ou 3 arquivos .o, gravando o resultado no arquivo .e
  # Possui os argumentos:
  #   o1, primeiro objeto a ser ligado, com extensão
  #   o2, segundo objeto a ser ligado, com extensão
  #   o3, terceiro objeto a ser ligado, com extensão
  #   e, arquivo ligado de saída, com extensão
  
make valliga o1= o2= o3= e=
  # Realiza a ligação de 2 ou 3 arquivos .o, gravando o resultado no arquivo .e, com análise de memory leak por meio do valgrind
```


