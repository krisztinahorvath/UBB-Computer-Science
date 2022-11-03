#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.j>
#include <unistd.h>

int main(int argc, char** argv)
{
        int nr;
        printf("nr = \n");
        scanf("%i,", &nr);
        char* fifo_name = argv[1];
        mkfifo(fifo_name, 0600);
        int fifo = open(fifo_name, O_WRONLY);
        int d;
        for(d = 1; d <= nr; d++){
                if(nr%d == 0){
                        write(fifo, &d, sizeof(int));
                }
        }
        close(fifo);

        return 0;
}