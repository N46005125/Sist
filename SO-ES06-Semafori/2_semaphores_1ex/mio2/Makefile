all: ex_sem ex_sem2

ex_sem: mio.o semafori.o
	gcc -o ex_sem mio.o semafori.o

ex_sem2: mio2.o semafori.o
	gcc -o ex_sem2 mio2.o semafori.o

mmio.o: mio.c semafori.h
	gcc -c mio.c -o mio.o

mio2.o: mio2.c semafori.h
	gcc -c mio2.c -o mio2.o

semafori.o: semafori.c semafori.h
	gcc -c semafori.c -o semafori.o

clean:
	rm -f *.o
	rm -f ex_sem