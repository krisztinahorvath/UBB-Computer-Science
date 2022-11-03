#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int main(int argc, char** argv)
{
        int fork_res = fork();
        char* file_name = argv[1];
        char* fifo_name = argv[2];
        int rw[2];
        pipe(rw);
        if(fork_res == 0){ // child P1
                FILE* file = fopen(file_name, "r");
                printf("n = \n");
                int n;
                scanf("%d", &n);
                char c = '\0';
                while((c = fgetc(file)) != EOF && n != 0 ){
                        n = n - 1;
                }
                close(rw[0]);
                fclose(file);
                write(rw[1], &c, sizeof(char));
                close(rw[1]);
                exit(0);
        }
        mkfifo(fifo_name, 0600); /// P2 parent
        int fifo = open(fifo_name, O_WRONLY);
        close(rw[1]);
        char c = '\0';
        read(rw[0], &c, sizeof(char));
        printf("char = %c\n", c);
        close(rw[0]);
        if(c >= '0' && c <= '9'){
                printf("digit\n");
        }
        else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
                printf("letter\n");
        }
        else{
                printf("other\n");
        }
        write(fifo, &c, sizeof(char));
        close(fifo);
        wait(0);
        return 0;
}
