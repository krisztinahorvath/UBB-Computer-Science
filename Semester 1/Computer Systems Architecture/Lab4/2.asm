bits 32
global start

extern exit
import  exit msvcrt.dll
     
;20.Given the words A and B, compute the doubleword C as follows:
;the bits 0-5 of C are the same as the bits 3-8 of A
;the bits 6-8 of C are the same as the bits 2-4 of B
;the bits 9-15 of C are the same as the bits 6-12 of A
;the bits 16-31 of C have the value 0


segment data use32 class = data
     a dw 0111_0111_0101_0111b
     b dw 1001_1011_1011_1110b
     c dd 0
segment code use32 class = code
start:
    mov eax, 0; the final result is stored in eax
    
    ;the bits 0-5 of C are the same as the bits 3-8 of A
    mov edx, 0
    mov edx, [a]; edx = 0000_0000_0000_0000_0111_0111_0101_0111b
    and edx, 0000_0000_0000_0000_0000_0001_1111_1000b; isolate bits 3-8 of A
    ; edx = 0000_0000_0000_0000_0000_0001_0101_0000b
    mov cl, 3
    ror edx, cl; edx = 0000_0000_0000_0000_0000_0000_0010_1010b
    or eax, edx; we put the result in eax
    
    ;the bits 6-8 of C are the same as the bits 2-4 of B
    mov edx, 0
    mov edx, [b]; edx = 0000_0000_0000_0000_1001_1011_1011_1110b
    and edx, 0000_0000_0000_0000_0000_0000_0001_1100b; isolate bits 2-4 of B
    ; edx = 0000_0000_0000_0000_0000_0000_0001_1100b
    mov cl, 4
    rol edx, cl
    or eax, edx; result in eax
    
    ;the bits 9-15 of C are the same as the bits 6-12 of A
    mov edx, 0
    mov edx, [a]; edx = 0000_0000_0000_0000_0111_0111_0101_0111b
    and edx, 0000_0000_0000_0000_0001_1111_1100_0000b; isolate bits 6-12 of A
    ; edx = 0000_0000_0000_0000_0001_0111_0100_0000b
    mov cl, 3
    rol edx, cl; ; edx = 0000_0000_0000_0000_1011_1010_0000_0000b
    or eax, edx; we put the result in eax
    
    ;the bits 16-31 of C have the value 0
    and eax, 0000_0000_0000_0000_1111_1111_1111_1111b; we force the values of the bits 16-31 to 0(in C)
   
    push dword 0
	call [exit]