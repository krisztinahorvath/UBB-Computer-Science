bits 32  

 
global start        

import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll
extern exit, printf, scanf              


extern prime   
; 20.Read from the console a list of numbers in base 10. Write to the console only the prime numbers.
 
segment data use32 class=data
   a resd 1
   n dd 0
   res resd 100
   read_format db "%d", 0
   write_format db "%d ", 0
   read_message db "n = ", 0
   write_message db "The prime numbers are: ", 0
   
   
segment code use32 class=code
    start:
        push read_message
        call [printf]
        add esp, 4*1
        
        push dword n
        push read_format
        call [scanf]
        add esp, 4*2
        
        mov ecx, 0
        mov ecx, [n] 
        mov esi, 0
        
        repeta:
            push dword a
            push read_format
            call [scanf]
            add esp, 4*2
            
            push eax 
            
            mov eax, [a]
            
            push eax
            call prime
            
            cmp eax, 0
            jz repeta
            mov [res+esi], eax
            inc esi
            
            pop eax 
            
        loop repeta
           
        push write_message
        call [printf]
        add esp, 4*1
        
        
        mov ecx, 0
        mov ecx, esi
        mov esi, 0
            
        write:
            mov ebx, [res+esi]
            
            push dword ebx
            push write_format
            call [printf]
            add esp, 4*2
            
            inc esi
        
        loop write
       
        push    dword 0       
        call    [exit]        
