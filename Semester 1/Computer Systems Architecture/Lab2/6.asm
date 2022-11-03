bits 32
global start

extern exit
import exit msvcrt.dll

; multiplications, divisions
; a, b, c - byte, d - word
; ex:20
; (50-b-c)*2+a*a+d

segment data use32 class = data
    a db 03h
    b db 0Ah
    c db 10h
    d dw 0100h


segment code use32 class = code
start:
    mov AX, 0
    mov BX, 0
    mov CX, 0
    mov DX, 0
    
    mov AL, 50
    mov BL, [b]
    sub AL, BL
    mov BL, [c]
    sub AL, BL
    mov BL, 02h
    mul BL
    
    mov DL, 0
    add DL, AL
    mov CL, [a]
    mov AL, [a]
    mul CL
    
    add DL, AL
    mov AX, [d]
    add DX, AX


push dword 0
call [exit]