bits 32  


global start        

 
import exit msvcrt.dll  
import printf msvcrt.dll  
import scanf msvcrt.dll 
extern exit, printf, scanf 

extern sum

; 5.Read the signed numbers a, b and c on type byte; calculate and display a+b-c.
segment data use32 class=data
    a resb 1
    b resb 1
    c resb 1 
    read_a db "a = ", 0
    read_b db "b = ", 0
    read_c db "c = ", 0
    read_format db "%d", 0
    print_format db "a+b-c = %d"
    
    
segment code use32 class=code
    start:
        push read_a
        call [printf]
        add esp, 4*1
        
        push dword a
        push read_format
        call [scanf]
        add esp, 4*2
        
        push read_b
        call [printf]
        add esp, 4*1
        
        push dword b
        push read_format
        call [scanf]
        add esp, 4*2
        
        push read_c
        call [printf]
        add esp, 4*1
        
        push dword c
        push read_format
        call [scanf]
        add esp, 4*2
        
        mov al, [a]
        cbw
        cwde
        mov bl, [b]
        cbw
        cwde
        mov dl, [c]
        cbw
        cwde
        
        push edx
        push ebx
        push eax
        
        call sum
        
        push eax
        push print_format
        call [printf]
        add esp, 4*2
        
        
        push    dword 0       
        call    [exit]        
