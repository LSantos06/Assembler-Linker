D: EXTERN
L1: eqU 1
L2: eqU 0

SECTION TEXT
iF l1
LOAD N		;faz esta operaçao se L1 for verdadeiro
iF L2
INPUT N  	;faz esta operaçao se L2 for verdadeiro
COPY D+20, D+1
COPY D, D+1
STOP
SECTION DATA
N: SPACE 2
Z: CONST L2
