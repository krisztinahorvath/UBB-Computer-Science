bits 32
global start

extern exit
import  exit msvcrt.dll
    ;5.(c+b+b)-(c+a+d)
    ;a - byte, b - word, c - double word, d - qword - Signed representation
segment data use32 class = data
    a db 01b
    b dw 2h
    c dd 0Bh
    d dq 0Ah
    r dd 0 ; to store the result of the first additions, temporarily
segment code use32 class = code
start:
    mov ebx, [c]
    mov ax, [b]
    cwd; convert with sign from word to double word => bx=>dx:ax
    
    push dx
    push ax
    pop eax 
    
    add ebx, eax; c+b; EBX<- EAX+EBX
    add ebx, eax; c+b+b; EBX<- EAX+EBX
    
    add [r], ebx; storing the result of c+b+b
    
    mov edx, [c]
    mov al, [a]
    cbw; convert with sign from byte to word => al=>ax
    cwd; convert with sign from word to double word => ax=>dx:ax
    
    mov eax, 0
    push dx
    push ax
    pop eax
    
    add eax, edx; c+a; EAX<-EAX+EDX
    cdq
    
    mov ecx, dword[d+0]
    mov ebx, dword[d+4]
    
    add eax, ecx   
    add edx, ebx   
    
    sub ecx, [r+0]
    mov ebx, [r+4]
    
    sub ecx, eax
    sbb ebx, edx ; EBX: EBX-EDX-CF
    
     
    push dword 0
	call [exit]