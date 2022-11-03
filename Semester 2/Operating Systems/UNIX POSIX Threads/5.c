#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

typedef struct
{
        char* file;
        int n;
        char* c;
} arg_t;

pthread_mutex_t m;
pthread_cond_t c;

void* thread(void* arg){
        arg_t a = *(arg_t*)arg;
        FILE* fd = fopen(a.file, "r");
        char ca = '\0';
        char cc;
        while(fscanf(fd, "%c", &ca)!= EOF && a.n != 0){
                cc = ca; /// because the last read in ca can be invalid
                a.n = a.n -1;
        }

        if(a.n != 0){
                printf("The file is too small\n");
        }
        else{
                if(cc == *(char*)a.c){
                        pthread_mutex_lock(&m);
                        pthread_cond_signal(&c);
                        pthread_mutex_unlock(&m);
                }
        }

        fclose(fd);
        free(arg);

        return 0;
}

void* watcher(void* arg){
        arg_t a = *(arg_t*)arg;
        printf("n= %i", a.n);
        pthread_mutex_lock(&m); 
        pthread_cond_wait(&c, &m);
        printf("The %i th char from file %s is equal to %s", a.n, (char*)a.file,(char*)a.c );
        pthread_mutex_unlock(&m);

        return 0;
}

int main(int argc, char** argv)
{
        pthread_t *t = malloc((argc-1)/3*sizeof(pthread_t));

        pthread_mutex_init(&m, 0);
        pthread_cond_init(&c, 0);

        int i;
        for(i = 0; i < (argc-1)/3; i++){
                arg_t *a = malloc(sizeof(arg_t));
                a->file = argv[i*3+1];
                a->n = atoi(argv[i*3 + 2]);
                a->c = argv[i*3 + 3];
                pthread_create(&t[i], 0, thread, (void*)a);
        }

        for(i = 0; i < (argc-1)/3; i++){
                pthread_join(t[i], 0);
        }

        pthread_cond_destroy(&c);
        pthread_mutex_destroy(&m);
        free(t);
        return 0;
}
