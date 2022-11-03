#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
        char* fifo_name = argv[1];
        int fifo = open(fifo_name, O_RDONLY);
        int nr;
        while(read(fifo, &nr, sizeof(int)) > 0){
                printf("%i ", nr);
        }
        close(fifo);
        unlink(fifo_name);
        return 0;
}