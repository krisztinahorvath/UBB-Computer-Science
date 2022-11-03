
/// ./4 16 1 3 19 0 4 20 4 1 30 2 0 15 3 2



#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct
{
        int n;
        int next;
        int prev;
        int index;
} arg_t;

pthread_mutex_t* m;
int s;

void* thread(void *arg){
        arg_t tr = *(arg_t*)arg; /// one triplet

        while(1){
                pthread_mutex_lock(&m[tr.index]);
                if(s > 1000){
                        pthread_mutex_unlock(&m[tr.index]); /// ca sa continuam cu urmatorul thread
                        break;
                }
                s = s + tr.n;
                printf("s = %i index = %i\n", s, tr.index);
                if(s % 2 == 0){
                        printf("Thread %i unlocked %i\n", tr.index, tr.next);
                        pthread_mutex_unlock(&m[tr.next]);
                }
                else{

                        printf("Thread %i unlocked %i\n", tr.index, tr.prev);
                        pthread_mutex_unlock(&m[tr.prev]);
                }
        }
	free(arg);
        return 0;
}

int main(int argc, char** argv)
{
        arg_t triples[(argc-1)/3]; /// so that we can go through the list
        pthread_t *t = malloc((argc-1)/3*sizeof(pthread_t));
        m = (pthread_mutex_t*)malloc((argc-1)/3*sizeof(pthread_mutex_t));

        int i;
        for(i = 0; i < (argc - 1)/3; i++){

                triples[i].n = atoi(argv[3*i+1]);
                triples[i].next = atoi(argv[3*i+2]);
                triples[i].prev = atoi(argv[3*i+3]);

                triples[i].index = i;

                pthread_mutex_init(&m[i], 0);
                pthread_mutex_lock(&m[i]);

                pthread_create(&t[i], 0, thread, (void*)&triples[i]);
        }

        int j;
        for(i = 0; i < (argc-1)/3 - 1; i++){
                 if(triples[i].next > (argc-1)/3 || triples[i].prev > (argc-1)/3){
                                printf("Invalid input\n");
                                exit(0);
                        }
                for(j = i + 1; j < (argc-1)/3; j++){
                        if(triples[i].next == triples[j].next ||
                        triples[i].prev == triples[j].prev){
                                printf("Invalid data!\n");
                                printf("%i %i\n", triples[i].next, triples[j].next);
                                 printf("%i %i\n", triples[i].prev, triples[j].prev);

                                exit(1);
                        }

                }
        }
        pthread_mutex_unlock(&m[0]); /// so that we start with the first one

        for(i = 0; i < (argc - 1)/3; i++){
                pthread_join(t[i], 0);

                pthread_mutex_destroy(&m[i]);
        }

        return 0;
}

