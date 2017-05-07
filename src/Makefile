CC= gcc

CFLAGS=	-g -I$(IDIR)

ODIR = obj
LDIR = ../lib
IDIR = ../include

LIBS= -lm

_DEPS =	arquivo.h listas.h montador.h ligador.h tabelas.h

DEPS =	$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = arquivo.o listas.o montador.o tabelas.o ligador.o main.o

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
	./prog -p $(file_name).asm $(file_name)

valpreproc:
	valgrind ./prog -p $(file_name).asm $(file_name)

monta_asm:
	./prog -o $(file_name).asm $(file_name)

valmonta_asm:
	valgrind ./prog -o $(file_name).asm $(file_name)

monta_pre:
	./prog -o $(file_name).pre $(file_name)

valmonta_pre:
	valgrind ./prog -o $(file_name).pre $(file_name)

liga:
	./prog -l $(o1) $(o2) $(o3) $(e)

valliga:
	valgrind ./prog -l $(o1) $(o2) $(o3) $(e)
