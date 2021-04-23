#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(int argc, char *argv[]){
    pid_t nuevo;
    if(argc!=3){
        printf("Indica dos numeros enteros\n");
        exit(0);
    }
    nuevo = fork();
    if(nuevo != 0){
        nuevo = fork();
        if(nuevo != 0){
            wait(NULL);
            wait(NULL);
            printf("Factoriales calculados\n");
        }else{
            execl("./factorial", "./factorial", argv[2], NULL);
            printf("No se encuentra la aplicacion factorial\n");
            exit(0);
        }

    }else{
        execl("./factorial", "./factorial", argv[1], NULL);
        printf("No se encuentra la aplicacion factorial\n");
        exit(0);
    }

    return 0;
}