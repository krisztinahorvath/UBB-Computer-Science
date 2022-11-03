bits 32
global start

extern exit
import  exit msvcrt.dll
    ;20.x-b+8+(2*a-b)/(b*b)+e;  
    ;a-word; b-byte; e-doubleword; x-qword - multiplication, division - signed representation
segment data use32 class = data
    a dw 0101h
    b db 0Ah
    e dd 02b
    x dq 0Bh
    r dq 0h
segment code use32 class = code
start:
    mov ebx, dword[x+0]
    mov ecx, dword[x+4]
    
    mov dl, b
    cbw; dl->dx
    cwde; dx->edx
    
    sub ebx, edx; 
    sub ebx, 8
    
    mov [r+0], ebx; 
    mov [r+4], ecx; 
    ; we store the result here so that we can use register ebx in other operations without losing the data just computed
    
    mov al, 2
    cbw; convert al->ax
    imul word[a]; =>dx:ax->ax*2; 2*a
    
    push dx
    push ax
    pop eax; eax->dx:ax
    
    mov cl, [b]
    cbw; cl->cx
    cwde;cx->ecx
    sub eax, ecx;2*a-b
    
    mov ecx, eax; so that we can use eax at the following imul/idiv operations
    
    mov eax, 0
    mov al, [b]
    imul byte[b]; b*b; result stored on a word-ax
    mov bx, ax; again we need eax for the division
    
    mov eax, ecx; the result of 2*a-b we move to eax
    idiv bx; dw/w->result stored in dx:ax
    
    push dx
    push ax
    pop eax
    
    sub dword[r+0], eax; we sub the high parts, [r+4] stays the same because eax is only a dd not dq
    add dword[r+0], [e]; x-b+8+(2*a-b)/(b*b)+e
    
    mov eax, dword[r+0]
    mov edx, dword[r+4]
    ; result stored in registers EDX:EAX
    
    
    push dword 0
	call [exit]