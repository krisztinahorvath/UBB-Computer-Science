/*
Write a c program that recives as command line arguments as many pairs formed by a file (f) 
containing only numbers (as may as you like) and a number (n). 
For each such pair the program will create a thread. 
Each thread will receive a pair and will add the first n even numbers from f to a global variable. 
The threads must be dynamically allocated in memory. 
The access to the global variable must be efficiently synchronized using mutex variables 
(putting a mutex_lock at the begnnig of the thread and mutex_unlock at the end of the thread 
IS NOT EFFICIENT SYNCHRONIZATION) NOTE: When you compile use the -pthread obtion. 
The source file must be compiled using gcc with -Wall -g options WITHOUT WARNINGS OR SYNTAX ERRORS!!!

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>


int sum;

typedef struct
{
        char* file;
        int n;
} arg_t;

pthread_mutex_t m;

void* thread(void* arg){
        arg_t a = *(arg_t*)arg;

        FILE* fd = fopen(a.file, "r");

        int nr;
        while(fscanf(fd, "%i", &nr) != EOF && a.n != 0){
                if(nr%2 == 0){
                        pthread_mutex_lock(&m);
                        sum = sum + nr;
                        pthread_mutex_unlock(&m);
                        a.n = a.n - 1;

                }
        }
        fclose(fd);
        free(arg); 
        return 0;
}

int main(int argc, char** argv)
{
        pthread_t *t = malloc((argc-1)/2* sizeof(pthread_t));

        pthread_mutex_init(&m, 0);

        int i;
        for(i = 0; i < argc - 1; i = i + 2){
                arg_t *a = malloc(sizeof(arg_t));
                a->file = argv[i+1];
                a->n = atoi(argv[i+2]);
                pthread_create(&t[i/2], 0, thread, (void*)a);
        }
        for(i = 0; i < argc-1; i = i + 2){
                pthread_join(t[i/2], 0);
        }

        printf("sum=%i\n", sum);

        pthread_mutex_destroy(&m);
        free(t);
        return 0;
}
