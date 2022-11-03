#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv){
        char name[16];
        printf("File name: \n");

        scanf("%15s", name);
        char* fifo_name = argv[1];
        mkfifo(fifo_name, 0600);
        int fifo = open(fifo_name, O_WRONLY);
        if(fifo < 0){
                perror("Mkfifo wasn't created\n");
                exit(0);
        }
        int fd = open(name, O_RDONLY);
        if(fd < 0){
                perror("The fifo wans't opened\n");
                exit(1);
        }
        FILE* file_read = fopen(name, "r");
        char c ; // here I store every character
        while((c = fgetc(file_read)) != EOF){
                if(c >= '0' && c <= '9'){
                        int a = c - '0';
                        if(write(fifo, &a, sizeof(int)) < 0){
                                perror("Unable to send nr");
                                exit(2);
                        }
                }
        }
        fclose(file_read);
        close(fifo);
        //free(file_read);
        return 0;
}
