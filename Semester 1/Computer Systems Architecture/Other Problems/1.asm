
; read a file, read a key, xor between the file and the key

bits 32 


global start        

 
extern exit, scanf, fopen, fclose, fread, fwrite, rename, remove, perror               
import exit msvcrt.dll    
import scanf msvcrt.dll 
import fopen msvcrt.dll 
import fclose msvcrt.dll 
import fread msvcrt.dll 
import fwrite msvcrt.dll
import rename msvcrt.dll
import remove msvcrt.dll
import perror msvcrt.dll    


segment data use32 class=data
    inputfile   db 'file.txt', 0
    outputfile  db 'b.text', 0
    moderead    db 'r', 0
    modewrite   db 'w', 0
    fd1         dd -1
    fd2         dd -2
    key         resb 2
    readformat  db '%s', 0
    buffer      times 4 db -1
 
segment code use32 class=code
    start:
        ; FILE * fopen(const char* nume_fisier, const char * mod_acces); asc mihai suciu
        push moderead
        push inputfile
        call [fopen]
        add esp, 4*2
        
        mov [fd1], eax; eax=return value of fopen
        cmp eax, 0
        je the_end
        
        push modewrite
        push outputfile
        call [fopen]
        add esp, 4*2
        
        mov [fd2], eax; eax=return value of fopen
        cmp eax, 0
        je the_end
        ;read key
        ;...
        
        read_file:
            ;int fread(void * buffer, int size, int count, FILE * stream)
            push dword[fd1]
            push dword 4
            push dword 1
            push buffer
            call [fread]
            add esp, 4*4
            
            
            cmp eax, 4
            je read_file
            ; xor buffer key
            ;....
            ;write result in open file
            ;.... 
        
        ;int fclose(FILE * descriptor)
        push dword [fd1]
        call [fclose]
        the_end:
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
