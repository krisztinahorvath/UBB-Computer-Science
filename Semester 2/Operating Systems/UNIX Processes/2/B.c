
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

void P1(int fifo, int r)
{
        int nr, d;
        read(fifo, &nr, sizeof(int));
        for(d = 1; d <= nr; d++){
                if(nr%d == 0){
                        write(r, &d, sizeof(int));
                }
        }
}

void P2(int r){
        int nr;
        while(read(r, &nr, sizeof(int)) > 0){
                printf("%i\n", nr);
        }
}

int main(int argc, char** argv)
{
        char* fifo_name = argv[1];
        int fifo = open(fifo_name, O_RDONLY);

        int rw[2]; /// pipe ends
        pipe(rw);
        if(fork() == 0){
                close(rw[0]);

                P1(fifo, rw[1]);
                close(rw[1]);

                close(fifo);
                exit(0);
        }

        if(fork() == 0){
                close(rw[1]);
                close(fifo);
                P2(rw[0]);

                close(rw[0]);
                exit(1);
        }
        close(fifo);
        unlink(fifo_name);
        wait(0);
        return 0;
}
