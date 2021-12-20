all: main 

main.o: main.c header.h
	gcc -c main.c 

main: main.o procedure.o
	gcc -o main main.o procedure.o -pthread

procedure.o: procedure.c header.h 
	gcc -c procedure.c

clean:
	rm -f main