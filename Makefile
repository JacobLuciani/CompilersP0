CC=g++
CFLAGS=-g
EX=main
DEPS=tree.h node.h
OBJ=tree.o

all: $(EX)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(EX): main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean
clean :
	rm -rf *.o $(EX)