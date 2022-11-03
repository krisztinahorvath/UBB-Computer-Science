bits 32 

; function calls

;5.Two natural numbers a and b (a, b: dword, defined in the data segment) are given. 
;Calculate a/b and display the quotient and the remainder in the following format: 
;"Quotient = <quotient>, remainder = <remainder>". 
;Example: for a = 23, b = 10 it will display: "Quotient = 2, remainder = 3".
;The values will be displayed in decimal format (base 10) with sign.
global start        

 
extern exit, printf        
import exit msvcrt.dll    
import printf msvcrt.dll

segment data use32 class=data
    a dd 23
    b dd 10
    ;format db "Quotient = %d, remainder = %d ", 0
    format db "Quotient = %d, remainder = %d "
    remainder dd 0
    quotient dd 0
    
    
segment code use32 class=code
    start:
        mov eax, dword[a]
        cdq; edx:eax <- eax
        
        mov ebx, dword[b]
        
        idiv ebx;eax=edx:eax/ebx, edx=edx:eax%ebx
        
        
        mov [quotient], eax
        mov [remainder], edx
        
        
        push dword [remainder]
        push dword [quotient]
        push dword format
        call [printf]
        
        add esp, 4*3
         
        push    dword 0      
        call    [exit]       