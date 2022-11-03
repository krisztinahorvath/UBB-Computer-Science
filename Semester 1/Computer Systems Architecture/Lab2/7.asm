bits 32
global start

extern exit
import exit msvcrt.dll

; multiplications, divisions
; a,b,c,d-byte, e,f,g,h-word
; ex:5
; a*(b+c)+34

segment data use32 class = data
    a db 03h
    b db 0Ah
    c db 10h
    

segment code use32 class = code
start:
    mov AL, 0
    mov BL, 0
    mov CL, 0
    
    mov AL, [b]
    mov BL, [c]
    add AL, BL
    add BL, [a]
    mul BL
    add AL, 34h


push dword 0
call [exit]