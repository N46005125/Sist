all: ex_sem

ex_sem: mio.o semafori.o
	gcc -o ex_sem mio.o semafori.o

main.o: mio.c semafori.h
	gcc -c mio.c -o mio.o

semafori.o: semafori.c semafori.h
	gcc -c semafori.c -o semafori.o

clean:
	rm -f *.o
	rm -f ex_sem