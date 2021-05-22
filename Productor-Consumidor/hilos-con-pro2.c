#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
//libreria de semaforos
#include<semaphore.h>
#define N 5

char buffer[N];
int in = 0, out = 0;
//crear un semaforo
sem_t chars;
//ejecucion de hebras
void * producer(void *);
void * consumer(void*);

//proceso principal
int main(int argc, char *argv[]){
    //inicializacion del semaforo
    sem_init(&chars, 0, 0);
    //identificadores procesos hebras
    pid_t pid = getpid();
    //crear lista de letras al azar
    srand((int)pid);
    //Crear los hilos
    pthread_t tid1, tid2;
    printf("Creamos productor\n");
    pthread_create(&tid1, NULL, producer, NULL);
    printf("Creamos consumidor\n");
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("Fin de la ejecucion\n");
    //Eliminar semaforo
    sem_destroy(&chars);
    exit(0);
}

void *producer(void * argument){
    int counter = 0;
    char c; 
    while(counter < 4){
        c = (rand() % (90 - 65)) + 65;
        buffer[in] = c;
        in = (in + 1)%N;
        printf("PRODUCTOR -> Letra : %c en posicion (%d)\n", c, in);
        in = (in + 1)%N;
        //signal - p
        sem_post(&chars);
        sleep(rand()%2);
        counter++;
    }
    pthread_exit(0);
}

//proceso consumidor

void *consumer(void * argument){
    int counter = 0; 
    char c;
    while(counter < 4){
        //test - v
        sem_wait(&chars);
        c = buffer[out];
        printf("CONSUMIDOR <- letra : %c en posicion (%d)\n", c, out);
        out = (out + 1) % N;
        sleep(rand() % 2);
        counter++;
    }
    pthread_exit(0);
}