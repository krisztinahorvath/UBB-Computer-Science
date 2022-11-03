bits 32
global start

extern exit
import exit msvcrt.dll

; multiplications, divisions
; a,b,c,d-byte, e,f,g,h-word
; ex:20
; [(a+b+c)*2]*3/g

segment data use32 class = data
    a db 05h
    b db 02h
    c db 01h
    g dw 0010h


segment code use32 class = code
start:
    mov AL, 0
    mov BL, 0

    mov AL, [a]
    mov BL, [b]
    add AL, BL
    mov BL, [c]
    add AL, BL
    
    mov BL, 02h
    mul BL
    mov BL, 03h
    mul BL
    
    mov BL, [g]
    div BL

push dword 0
call [exit]