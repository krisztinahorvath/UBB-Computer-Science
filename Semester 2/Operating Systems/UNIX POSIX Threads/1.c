/*
Scrieti un program C care primeste ca si argumente in linia de comanda oricate fisiere. 
Fiecare fisier va cantine doua numere intregi a inter 1 si 100 si b intre 1000 si 100000. 
Prgramul va avea n variabile globale, n find numarul de fisiere date ca argument in linia de comanda. 
Programu va crea cate doua thread-uri x si y pentru fiecare fisier primit ca argument, 
Fiecare pereche de thread-uri x si y va primi ca argument un fisier dat ca argument, 
thread-ul x va citi numarul a si b din fisier si va adauga valoarea lui a la variabila globala 
asociata acestuia pana cand variabila globala va depasi valoarea lui b, 
moment in care x va trimite un semnal lui y si y va afisa pe ecran valoarea variabilei globale.
*/ 

     
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>


pthread_cond_t c;
pthread_mutex_t m;

typedef struct
{
        char* file;
        int index; /// the pos where we access nr
} t_arg;

int nr[100]; /// var for the sum

void* thread_x(void * arg){
        char* file = (*(t_arg*)arg).file;
        int index = (*(t_arg*)arg).index;

        FILE* fd = fopen(file, "r");
        int a, b;
        fscanf(fd, "%i", &a);
        fscanf(fd, "%i", &b);

        pthread_mutex_lock(&m);
        while(nr[index] <= b) {
                nr[index] = nr[index] + a;

        }

        pthread_cond_signal(&c);

        pthread_mutex_unlock(&m);

        fclose(fd);
        free(arg);
        return NULL;
}

void* thread_y(void * arg){ /// watcher
        t_arg a;
        a = *(t_arg*)arg;
        pthread_mutex_lock(&m);

        pthread_cond_wait(&c, &m);
        printf("nr[%i] = %i\n", a.index, nr[a.index]);

        pthread_mutex_unlock(&m);

        return NULL;
}

int main(int argc, char** argv)
{
        pthread_t *x, *y;
        x = malloc((argc - 1) * sizeof(pthread_t));
        y = malloc((argc - 1) * sizeof(pthread_t));

        pthread_cond_init(&c, 0);
        pthread_mutex_init(&m, 0);

        int i;

        for(i = 1; i < argc; i++){
                t_arg *a;
                a = malloc(sizeof(t_arg));
                a->file = argv[i];
                nr[i] = 0;
                a->index = i;
                pthread_create(&x[i-1], 0, thread_x, (void*)a);
                pthread_create(&y[i-1], 0, thread_y, (void*)a); /// watcher
        }

        for(i = 0; i < argc - 1; i++)   {
                pthread_join(x[i], 0);
                pthread_join(y[i], 0);
        }


        pthread_cond_destroy(&c);
        pthread_mutex_destroy(&m);

        free(x);
        free(y);
        return 0;
}

