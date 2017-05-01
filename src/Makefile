CC= gcc

CFLAGS=	-g -I$(IDIR)

ODIR= obj
LDIR = ../lib
IDIR = ../include

LIBS= -lm

_DEPS =	arquivo.h listas.h montador.h tabelas.h

DEPS =	$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = arquivo.o listas.o montador.o tabelas.o main.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)

	$(CC) -c -o $@ $< $(CFLAGS)

prog: $(OBJ)

	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:
	clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~

preproc:
	./prog -p pre_teste.asm pre_teste

valpreproc:
	valgrind ./prog -p pre_teste.asm pre_teste

monta_asm:
	./prog -o pre_teste.asm pre_teste

valmonta_asm:
	valgrind ./prog -o pre_teste.asm pre_teste

monta_pre:
	./prog -o pre_teste.pre pre_teste

valmonta_pre:
	valgrind ./prog -o pre_teste.pre pre_teste
