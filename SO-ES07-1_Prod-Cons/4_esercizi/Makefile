all: teatro

teatro: procedure.o semafori.o teatro.o
	gcc -o teatro procedure.o semafori.o teatro.o

teatro.o: teatro.c
	gcc -c teatro.c

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c



clean:
	rm -rf *.o
	rm -rf prodcons_vettore_stato
