#ifndef HEADER__
#define HEADER__

#define TYPE 1

typedef char mess[20];

typedef struct {
	long type;		
	mess testo;	
}Messaggio;

void Sender(int, int);
void Receiver(int);

#endif 