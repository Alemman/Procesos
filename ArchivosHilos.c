#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define MAXLONG 1000

typedef struct {
    char caracter;
    char archivo[MAXLONG];
}Datos;

void* cuenta_Caracteres(void*);
int numCaracter_1 = 0;
int numCaracter_2 = 0;


int main(int argc, char *argv[]){
    pthread_t hilo1, hilo2;
    
    if(argc != 2){
        printf("Dame el nombre de un archivo\n");
        exit(0);
    }
    Datos datos;
    strcpy(datos.archivo, argv[1]);
    datos.caracter = 'a';
    pthread_create(&hilo1, NULL, cuenta_Caracteres, (void*)datos);
    datos.caracter = 'b';
    pthread_create(&hilo2, NULL, cuenta_Caracteres, (void*)datos);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    printf("Factoriales calculados\n");

    return 0;
}

void * cuenta_Caracteres(void* datos){
    int pos, cont = 0, leidos;
    char cadena[MAXLONG];
    int fd;

    fd = open(datos.archivo, O_RDONLY);
    while((leidos = read(fd, cadena, MAXLONG)) != 0)
        for(pos = 0; pos  leidos; pos++)
            if((cadena[pos] == datos.caracter) || (cadena[pos] == toupper(datos.caracter)))
                cont++;

    close(fd);
    return 0;
}
