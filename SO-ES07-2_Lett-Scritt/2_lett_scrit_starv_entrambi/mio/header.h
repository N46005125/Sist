#ifndef H_H
#define H_H


#define MUTEX_L 0
#define MUTEX_S 1
#define SYNC 2
#define MUTEX 3

#define NUM_PROD 5
#define NUM_CONS 5

typedef struct{
    long mess;
    int NUM_LETTORI;
    int NUM_SCRITTORI;
}Buffer;

void Scrittore(Buffer*,int,int);
void Lettore(Buffer*,int,int);

#endif