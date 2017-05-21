L1: eqU 1
L2: eqU 0

SECTION TEXT
iF l1
LOAD N+4		;faz esta operaçao se L1 for verdadeiro
iF L2
INPUT N  	;faz esta operaçao se L2 for verdadeiro
COPY n+20, N+1
COPY z, n
DIV n
STOP
SECTION DATA
N: SPACE 2
Z: CONST L2
