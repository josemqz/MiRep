CC=gcc
CFLAGS=-I.
DEPS = fun.h genetico.h linkedList.h
OBJ = main.c linkedList.o fun.o genetico.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
