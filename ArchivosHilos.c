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

typedef struct Dat{
    char caracter;
    char archivo[MAXLONG];
}Datos;


void* cuenta_Caracteres(void*);



int main(int argc, char *argv[]){
    
    
    if(argc != 2){
        printf("Dame el nombre de un archivo\n");
        exit(0);
    }

    void* numCaracter_1 = 0;
    void* numCaracter_2 = 0;
    pthread_t hilo1, hilo2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    Datos datos;
    Datos datos2;
    strcpy(datos.archivo, argv[1]);
    strcpy(datos2.archivo, argv[1]);
    datos.caracter = 'a';
    datos2.caracter = 'b';

    pthread_create(&hilo1, &attr, cuenta_Caracteres, &datos);
    pthread_create(&hilo2, &attr, cuenta_Caracteres, &datos2);

    pthread_join(hilo1, &numCaracter_1);
    pthread_join(hilo2, &numCaracter_2);
    printf("# a or A: %d\n# b or B: %d\n", (int)numCaracter_1, (int)numCaracter_2);

    return 0;
}

void * cuenta_Caracteres(void* datos){
    int pos, cont = 0, leidos;
    char cadena[MAXLONG];
    int fd;

    fd = open(((Datos*)datos)->archivo, O_RDONLY);
    while((leidos = read(fd, cadena, MAXLONG)) != 0)
        for(pos = 0; pos < leidos; pos++)
            if((cadena[pos] == ((Datos*)datos)->caracter) || (cadena[pos] == toupper(((Datos*)datos)->caracter)))
                cont++;

    close(fd);
    return (void*)cont;
}
