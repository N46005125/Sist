all: teatro visualizzatore

teatro: procedure.o semafori.o teatro.o
	gcc -o teatro procedure.o semafori.o teatro.o

teatro.o: teatro.c procedure.h
	gcc -c teatro.c

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

visualizzatore.o: visualizzatore.c procedure.h
	gcc -c visualizzatore.c

visualizzatore: procedure.o semafori.o visualizzatore.o
	gcc -o visualizzatore procedure.o semafori.o visualizzatore.o


clean:
	rm -rf *.o
	rm -rf teatro