bits 32
global start

extern exit
import  exit msvcrt.dll
    ;a-b-(c-d)+d
    ;a - byte, b - word, c - double word, d - qword - Signed representation
segment data use32 class = data
    a db 01b
    b dw 2h
    c dd 0Bh
    d dq 0Ah
    r dq 0 ; additional variable to help us with the subtraction of qwords
segment code use32 class = code
start:
    mov bl, [a]
    cbw; al-> ax=a
    sbb bx, [b]
    cwd; bx=> ebx = a-b
    
    mov eax, [c]
    cdq ; EDX:EAX<-EAX=c
    
    clc
    sub eax, dword[d+0]
    sbb edx, dword[d+4]; c-d
    
    clc
    sub ebx, eax
    mov ecx, 0
    sbb ecx, edx ;a-b-(c-d)
    
    clc 
    add ebx, dword[d+0]
    adc ecx, dword[d+4];
   

    push dword 0
	call [exit]