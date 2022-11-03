bits 32
global start

extern exit
import  exit msvcrt.dll
    ;5.Given the bytes A and B, compute the doubleword C as follows:
    ;the bits 16-31 of C have the value 1
    ;the bits 0-3 of C are the same as the bits 3-6 of B
    ;the bits 4-7 of C have the value 0
    ;the bits 8-10 of C have the value 110
    ;the bits 11-15 of C are the same as the bits 0-4 of A
segment data use32 class = data
    a db 0011_1001b
    b db 1011_0011b
    c dd 0
segment code use32 class = code
start:
    mov eax, [c] 
    ;the bits 16-31 of C have the value 1
    or eax, 1111_1111_1111_1111_0000_0000_0000_0000b; we force the value of bits 16-31 to 1
    
    ;the bits 0-3 of C are the same as the bits 3-6 of B
    mov edx, 0
    mov edx, [b]; edx = 0000_0000_0000_0000_0000_0000_1011_0011b
                ; 0110 - bits 3-6 of b
    and edx, 0000_0000_0000_0000_0000_0000_0111_1000b; we isolate the value of bits 3-6 of b => 0000_0000_0000_0000_0000_0000_0011_0000
    mov cl, 3
    ror edx, cl; 0000_0000_0000_0000_0000_0000_0000_0110b
    or eax, edx; we put the result in eax
    
    ;the bits 4-7 of C have the value 0
    mov edx, 1111_1111_1111_1111_1111_1111_0000_1111b
    and eax, edx; we force the values of the bits 4-7 in C to have the value 0

    ;the bits 8-10 of C have the value 110
    mov edx, 0000_0000_0000_0000_0000_0110_0000_0000b
    or eax, edx; we force the values of the bits 8-10 in C to have the value 110
    
    ;the bits 11-15 of C are the same as the bits 0-4 of A
    mov edx, 0
    mov edx, [a]; edx = 0000_0000_0000_0000_0000_0000_0011_1001b
    and edx, 0000_0000_0000_0000_0000_0000_0001_1111b ;=> edx = 0000_0000_0000_0000_0000_0000_0001_1001b
    mov cl, 11
    rol edx, cl ; edx = 0000_0000_0000_0000_1100_1000_0000_0000b
    or eax, edx; final result 
    
    
    push dword 0
	call [exit]