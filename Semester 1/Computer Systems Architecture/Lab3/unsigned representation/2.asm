bits 32
global start

extern exit
import  exit msvcrt.dll
    ;20.(a+c)-b+a + (d-c)
    ;a - byte, b - word, c - double word, d - qword - Unsigned representation
segment data use32 class = data
    a db 01b
    b dw 2h
    c dd 0Bh
    d dq 0Ah
segment code use32 class = code
start:
    mov eax, 0
    mov eax, [c]
    mov ecx, 0
    mov ecx, dword[a]
    add eax, ecx; a+c
    
    sub eax, dword[b]; (a+c)-b
    add eax, dword[a]; (a+c)-b+a
    
    mov ecx, 0
    mov ecx, [d]
    sub ecx, [c]; d-c
    
    add eax, ecx; (a+c)-b+a + (d-c)
    
    push dword 0
	call [exit]