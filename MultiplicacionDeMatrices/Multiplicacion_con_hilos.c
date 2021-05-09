#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>

typedef struct{
    pthread tid;
    long TID;
    char[N] M1;
    char[N] M2;
    int row;
    int col;
    int sum;
}TMultMat;

Print_result(long *Matrix_thread, int row, int col);
void *multiply_row_x_Col(void*parameter);

int main(int argc, char *argv[]){
    //checar parametrso completos
    FILE file = fopen(argv[1], "rb");
    if(!file){
        exit(-1);
    }

    void * value = NULL;
    int i, j, x = 0, y = 0, coutn = 0;
    int row, col;
    long thread_id, number_threads;

    fread(&row, sizeof(int), 1, file);
    fread(&col, sizeof(int), 1, file);
    fclose(file);
    
    long Result[row][col];
    number_threads = row*col;
    TMultMat multMatrix[row][col];

    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            multMatrix[i][j].M1 = argv[1];
            multMatrix[i][j].M2 = argv[2];
            multMatrix[i][j].row = i;
            multMatrix[i][j].col = j;

            pthread_create(&multMatrix[i][j].tid, NULL, multiply_row_x_Col, &multMatrix);
            multMatrix[i][j].TID = (unsigned long)multMatrix[i][j].tid;
            Result[i][j] = multMatrix[i][j].TID;
        }
    }

    pthread_join(multMatrix[x][y].tid, &value);
    thread_id = (long)value;
    while(coutn < number_threads){
        for(i = 0; i < row; i++){
            for(j = 0; j < col; j++){
                if(thread_id == Result[i][j]){
                    Result[i][j] = multMatrix[i][j].sum;
                    break;
                }
            }
        }
        y++;
        if(y == col){
            x++;
            y = 0;
        }
        pthread_join(multMatrix[x][y].tid, &value);
        thread_id = (long)value;
        coutn++;
    }

    Print_result(Result);
    exit(0);
}

void Print_result(long M[N][N], int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%lld ", M[i][j]);
        }
        printf("\n");
    }
}

void * multiply_row_x_Col(void *p){
    TMultMat Matrix_thread = (TMultMat)p;
    FILE file = fopen(Matrix_thread.M1, "rb");
    if(!file){
        printf("Error en apertura de archivo %s\n", Matrix_thread.M1);
        exit(-1);
    }
    int row, col, sum;
    fread(&row, sizeof(int), 1, file);
    fread(&col, sizeof(int), 1, file);
    fclose(file);

    int vector_row[row];
    int vector_col[col];

    read_row(Matrix_thread.M1, Matrix_thread.row, vector_row);
    read_col(Matrix_thread.M2, Matrix_thread.col, vector_col);

    for(int i = 0; i < col; i++){
        sum += vector_col[i] * vector_row[i];
    }

    pthread_exit(NULL);

}

void read_row(char f[], int row, int vector[]){
    FILE file = fopen(f, "rb");
    if(!file){
        printf("File Open Error read_row()\n");
        exit(1);
    }
    int n;
    fread(&n, sizeof(int), 1, file);
    int shifting = sizeof(int)*2 + col*n*(sizeof(int))
    fseek(file, shifting, SEEK_SET);
    fread(vector, sizeof(int), n, file);
    fclose(file);
}

void read_col(char *f, int col, int vector){
    FILE file = fopen(f, "rb");
    if(!file){
        printf("File Open Error read_col() \n");
        exit(1);
    }
    int n, shifting;
    fseek(file, sizeof(int), SEEK_SET);
    fread(&n, sizeof(int), 1, file);
    shifting = sizeof(int)*(n-1);

    for(int i = 0; i < n; i++){
        fread(&vector[i], sizeof(int), 1, file);
        fseek(file, shifting, SEEK_CUR);
    }

    fclose(file);
}