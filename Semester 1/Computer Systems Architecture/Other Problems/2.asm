bits 32 


global start        


extern exit, printf, scanf               
import exit msvcrt.dll    
import printf msvcrt.dll
import scanf msvcrt.dll


                          
segment data use32 class=data
    a dd 0
    b dd 0
    r dd 0
    f1 db 'a = ', 0
    f2 db 'b = ', 0
    readformat db '%d', 0
    printformat db '%d + %d = %d', 0
    
segment code use32 class=code
    start:
        ; read two numbres and compute the sum
        ; int printf(const char * format, var_1, const_2, .....)
        push f1
        call [printf]
        add esp, 4*1
        
        ; int scanf(const char * format, adresa_variabila_1, ...)
        push dword a
        push readformat
        call [scanf]
        add esp, 4*2
        
        
        push f2
        call [printf]
        add esp, 4*1
        
        ; int scanf(const char * format, adresa_variabila_1, ...)
        push dword b
        push readformat
        call [scanf]
        add esp, 4*2
        
        mov eax, [a]
        add eax, [b]
        mov [r], eax
        
        push dword[r]
        push dword[b]
        push dword[a]
        push printformat
        call [printf]
        add esp, 4*4
        
        
        push    dword 0     
        call    [exit]      
