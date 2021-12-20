minimo-mutua-esclusione: main.o procedure.o semafori.o
	gcc -o minimo-mutua-esclusione main.o procedure.o semafori.o

main.o: main.c header.h
	gcc -c -g -o main.o main.c

procedure.o: procedure.c header.h semafori.h
	gcc -c -g -o procedure.o procedure.c

semafori.o: semafori.c
	gcc -c -g -o semafori.o semafori.c

clean:
	rm -f *.o
	rm -f minimo-mutua-esclusione
