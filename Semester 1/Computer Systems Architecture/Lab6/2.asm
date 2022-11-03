bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit               
import exit msvcrt.dll    
                          

;20.Being given a string of words, obtain the string (of bytes) of the digits in base 10 of each word from this string


segment data use32 class=data
    s dw 12345, 20778, 4596 
    l equ ($-s)/2 
    result times l*16 db 0; because there are 16 bits in a word
    ten dw 10
    

segment code use32 class=code
    start:
      mov ecx, l
      mov esi, s
      mov ebx, 0; index for result
      repeta:
        lodsw; ax = the current nr from s
        mov dx, 0; for the divison we clear out dx 
        transf:
            div word[ten]
            mov [result+ebx], dx; the digit of the nr is in dx so we add it to the new string
            inc ebx
            cmp ax, 0; 
            jz repeta; if the zf=0, then there are no digits left in the number
        mov dx, 0
        jmp transf
        
      loop repeta
      
  
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
