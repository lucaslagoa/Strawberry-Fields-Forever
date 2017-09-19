all: main

main: main.o tp2.o args.o 
	gcc -o tp2 main.o tp2.o args.o

clean:
	-rm -f *.o main *~
