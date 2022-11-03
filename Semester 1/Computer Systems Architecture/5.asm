bits 32
global start

extern exit
import  exit msvcrt.dll
    ;5.(a+b/c-1)/(b+2)-x; unsigned
    ;a-doubleword; b-byte; c-word; x-qword - multiplication, division - unsigned representation
segment data use32 class = data
    a dd 0102h
    b db 0Ah
    c dw 01h
    x dq 0Bh 
segment code use32 class = code
start:
    mov ebx, [a]
    
    mov eax, 0
    mov eax, [b]
    
    pop eax
    pop ax
    pop dx
    
    div word [c]; ax/c; remainder in dx
    
    push dx
    push ax
    pop eax; we store b/c in eax
    
    add ebx, eax; a+b/c
    dec ebx; a+b/c-1
    
    mov eax, ebx; we store the result in eax => we can make the division
    
    mov ecx, 0
    mov ecx, [b]; byte here???????????
    sub ecx, 2
    
    div word[b]; (a+b/c-1)/(b-2); dx:ax
    
    mov ecx, 0
    mov ebx, 0
    mov ecx, dx
    mov ebx, ax
    
    clc
    sub ebx, dword[x+0]
    sbb ecx, dword[x+4]; ECX:EBX ; we use sbb in case of an overflow
    ; final result in edx:eax
    

    push dword 0
	call [exit]