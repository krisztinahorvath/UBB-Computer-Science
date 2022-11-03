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
        mkfifo(fifo_name, 0600);
        char file_name[16];
        int rw[2];
        pipe(rw);
        int fork_res = fork();
        if(fork_res == 0){ /// child P1
                printf("File name: \n");
                scanf("%15s", file_name);
                close(rw[0]);
                write(rw[1], &file_name, sizeof(char));
                close(rw[1]);
                exit(1);
        }
        close(rw[0]);
        read(rw[1], &file_name, sizeof(char));
        close(rw[1]);
        FILE* file = fopen(file_name, "r");
        char c = '\0';
        int fr[5];
        int i = 0;
        for(i = 0; i < 5; i++){
                fr[i] = 0;
        }
        while((c = fgetc(file)) != EOF){
                if(c == 'A'){
                        fr[0] = fr[0] + 1;
                }
                if(c == 'E'){
                        fr[1] = fr[1] + 1;
                }
                if(c == 'I'){
                        fr[2] = fr[2] + 1;
                }
                if(c == 'O'){
                        fr[3] = fr[3] + 1;
                }
                if(c == 'U'){
                        fr[4] = fr[4] + 1;
                }
        }
        fclose(file);
        int fifo = open(fifo_name, O_WRONLY);
        for(int i = 0; i < 5; i++){
                write(fifo, &fr[i], sizeof(int));
        }
        close(fifo);
        wait(0);
        return 0;
}