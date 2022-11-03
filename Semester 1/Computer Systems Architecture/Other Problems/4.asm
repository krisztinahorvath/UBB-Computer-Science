bits 32  
;Se citeste de la tastatura un nume de fisier, un caracter special s (orice caracter in afara de litere si cifre) si un numar n reprezentat pe octet. Fisierul contine cuvinte separate prin spatiu. Sa se scrie in fisierul output.txt aceleasi cuvinte transformate astfel: al n-lea caracter din fiecare cuvant se transforma in caracterul special. (Daca numarul de caractere al cuvantului este mai mic decat n, cuvantul se va prefixa cu caracterul special s )


global start        

 
extern exit, printf, fopen, fclose, scanf, fread, fwrite, fprintf           
import exit msvcrt.dll     
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import fread msvcrt.dll
import fwrite msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    input_file resb 1
    input_handle dd -1
    
    output_file db "output.txt", 0
    output_handle dd -1
  
    read_mode db "r", 0
    write_mode db "w", 0
    write_format db "%s ", 0
    
    file_read_format db "%s", 0
    file_message db "file name: ", 0
    
    s_read_message db "s= ", 0
    n_read_message db "n= ", 0
    s_read_format db "%c", 0
    n_read_format db "%d", 0
    s dd 0   ; special char
    n dd 0
    cuvant dw "0", 0
    litera db 0
    lung_cuv db 0
    cuvant_prefixat db "0", 0
    
segment code use32 class=code
    start:
        ;printf(const char * format, variabila_1, constanta_2, ...);
        ;push print_message_file_name
        ;call [printf]
        ;add esp, 4*1
        
        ;int scanf(const char * format, adresa_variabila_1, ...);
        push dword file_message
        call [printf]
        add esp, 4*1
        
        push dword input_file
        push dword file_read_format
        call [scanf]
        add esp, 4*2
        
        push dword s_read_message
        call [printf]
        add esp, 4*1
        
        push dword s       ; read s
        push dword s_read_format
        call [scanf]
        add esp, 4*2
        
        push dword n_read_message
        call [printf]
        add esp, 4*1
        
        push dword n        ; read n
        push dword n_read_format
        call [scanf]
        add esp, 4*2
        
        ; FILE * fopen(const char* nume_fisier, const char * mod_acces)  
        
        push dword read_mode   ; open input file
        push dword input_file
        call [fopen]
        add esp, 4*2
        
        mov [input_handle], eax 
        cmp eax, 0
        je final
        
        push dword write_mode    ; open output file 
        push dword output_file
        call [fopen]
        add esp, 4*2
        
        mov [output_handle], eax 
        cmp eax, 0
        je final
        
        ;  fread(void * buffer, int size, int count, FILE * stream)
        mov esp, 0
        mov ecx, 100 ; we read 100 chars
        read_:
            push [input_handle]
            push dword 1
            push dword 1
            push dword litera
            call [fread]
            
            cmp eax, 0
            je final
            
            cmp litera, ' '
            je cuvant_
            inc esp
            mov [cuvant+esp], [litera]
            
            
            cuvant_:
               mov byte[lung_cuv], 1
               
               cmp [lung_cuv], [n]
               je litera_n
               
               cmp [lung_cuv], [n]
               jb cuv_scurt
               
               
               litera_n:
                 pushad
                 mov esi, [lung_cuv]
                 mov [cuvant+esi], [s]
                 jmp print_cuv
                 popad
                 
               cuv_scurt:
                 mov [cuvant_prefixat], [s]
                 
                 pushad
                 mov esp, 0
                 mov ecx, lung_cuv
                 copiere_:
                   mov al, [cuvant+esp]
                   mov [cuvant_prefixat + esp + 1], al
                 loop copiere
                 
                 popad
                 
                 pushad
                 mov esi, cuvant_prefixat
                 mov edi, cuvant
                 rep movsb ; copiem in cuvant, noul cuvant prefixat
                 
                 popad
                 jmp print_cuv
                 
                
               print_cuv: 
                   ;int fprintf(FILE * stream, const char * format, , , <...>)
                   push dword cuvant
                   push dword write_format
                   push dword [output_handle]
                   call [fprintf]
                   add esp, 4*3
                   
                    cmp eax, 0
                    je final
                    
                   jmp afara
               
              
                   
               inc lung_cuv
               jmp cuvant_  
            afara:
            
        loop read_
        
        ; closing the files 
        push dword [input_handle]
        call [fclose]
        add esp, 4*1
        
        push dword [output_handle]
        call [fclose]
        add esp, 4*1 
        
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

        
