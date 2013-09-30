
OPT=-O2

CFLAGS=\
	-std=c89 \
	-Wall -Wextra -pedantic \
	-g\
	$(OPT)

TARG=skilisp
OBJECTS=\
	lex.o\
	string_buffer.o\
	main.o

$(TARG): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)
clean:
	rm -f $(TARG) *.o
