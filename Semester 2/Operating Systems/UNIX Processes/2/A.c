#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int cmmmc(int x, int y)
{
        int a;
        a = x;
        int b;
        b  = y;
        while(x!=y){
                if(x > y){
                        x  = x - y;
                }
                else {
                        y  = y -  x;
                }
        }
        return (a*b)/x;
}

int main(int argc, char** argv)
{
        int nr1, nr2;
        printf("nr1 = ");
        scanf("%i", &nr1); // use &nr1??

        printf("nr2 = ");
        scanf("%i", &nr2);

        char* fifo_name = argv[1];
        mkfifo(fifo_name, 0600);
        int fifo = open(fifo_name, O_WRONLY);

        int rez = cmmmc(nr1, nr2);
        write(fifo, &rez, sizeof(int));

        close(fifo);
        return 0;
}
