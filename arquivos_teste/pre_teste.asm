L1: eqU 1
L2: eqU 0

Y: EXTERN
PUBLIC N

SECTION TEXT
iF L1
LOAD Y		;faz esta operaçao se L1 for verdadeiro
iF L2
INPUT N  	;faz esta operaçao se L2 for verdadeiro

SECTION DATA
N: CONST L1
D: SPACE L2