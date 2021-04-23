#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void * factorial(void *dato){
    long long int  resultado = 1;
    int num, n = atoi((char*)dato);
    for(num = 2; num <= n; num++){
        resultado = resultado *num;
        printf("Factorial de %d, resultado parcial %lld\n",n,resultado);
        sleep(random()%3);
        printf("El factorial de %d es %lld \n", n,resultado);
        pthread exit(NULL);
    }
}

int main (int argc, char *argv[]){
    pthread_t hilo1, hilo2;
    if(argc != 3){
        printf("Indica dos numeros enteros\n");
        exit(0);
    }
    pthread_create(&hilo1, NULL, factorial, (void*)argv[1]);
    pthread_create(&hilo2, NULL, factorial, (void*)argv[2]);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    printf("Factoriales calculados\n");

    return 0;

}