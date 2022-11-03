bits 32
global start

extern exit
import exit msvcrt.dll
    ;5.(c-a-d)+(c-b)-a
    ;a - byte, b - word, c - double word, d - qword - Unsigned representation
 

segment data use32 class = data
    a db 01b
    b dw 2h
    c dd 0Bh
    d dq 0Ah

segment code use32 class = code
start:
    mov edx, 0
    mov edx, [c]
    mov ebx, 0
    mov ebx, dword[a]
    sub edx, ebx; c-a
    
    mov ecx, 0
    mov ecx, [d]
    sub edx, ecx; c-a-d
    
    mov ecx, 0
    mov ecx, [c]
    mov ebx, 0
    mov ebx, dword[b]
    sub ecx, ebx; c-b
    
    sub edx, ecx; (c-a-d)+(c-b)
    
    mov ecx, 0
    mov ecx, dword[a]
    sub edx, ebx; (c-a-d)+(c-b)-a
  

push dword 0
call [exit]