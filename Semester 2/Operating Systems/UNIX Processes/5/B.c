#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
        char* fifo_name = argv[1];
        int fifo = open(fifo_name, O_RDONLY);
        int rw[2];
        pipe(rw);
        int fork_res = fork();
        if(fork_res == 0){ /// child P1
                int nr, sum = 0;
                while(read(fifo, &nr, sizeof(int)) > 0){
                        sum = sum + nr;
                }
                close(fifo);
                close(rw[0]);
                write(rw[1], &sum, sizeof(int));
                close(rw[1]);
                exit(0);

        }
        else if(fork_res > 0){ /// parent P2
                close(rw[1]);
                int sum;
                read(rw[0], &sum, sizeof(int));
                close(rw[0]);
                printf("The sum is: %i\n", sum);
        }

        close(fifo);
        unlink(fifo_name);
        wait(0);
        return 0;
}