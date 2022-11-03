#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void P1(int fifo, int w){
        int nr;
        int sum = 0;
        while(read(fifo, &nr, sizeof(int)) > 0){
                sum = sum + nr;
        }
        write(w, &sum, sizeof(int));
}

void P2(int r){
        int sum, d;
        read(r, &sum, sizeof(int));
        for(d = 1; d <= sum; d++){
                if(sum % d == 0){
                        printf("%d ", d);
                }
        }
}
int main(int argc, char** argv){
        char* fifo_name = argv[1];
        int fifo = open(fifo_name, O_RDONLY);

        int rw[2]; /// pipe
        if(pipe(rw) < 0 ){
                perror("Unable to create p channel!\n");
                exit(2);
        }
        if(fork() == 0){
                close(rw[0]);
                P1(fifo, rw[1]);
                close(rw[1]);
                close(fifo);
                exit(0);
        }
        if(fork() == 0){i
                close(rw[1]);
                close(fifo);

                P2(rw[0]);
                close(rw[1]);

                exit(1);
        }
        close(rw[0]);
        close(rw[1]);

        close(fifo);
        unlink(fifo_name);
        wait(0); // needed??
        return 0;
}