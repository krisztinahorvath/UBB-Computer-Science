#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>


int main(int argc, char** argv)
{
        char* fifo_name = argv[1];
        int fifo = open(fifo_name, O_RDONLY);
        char c;
        read(fifo, &c, sizeof(char));
        printf("%02X\n", c);
        close(fifo);
        unlink(fifo_name);

        return 0;
}
