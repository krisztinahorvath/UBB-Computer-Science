bits 32
global start

extern exit
import exit msvcrt.dll

; additons, subtractions
; a, b, c, d - word
; ex:5
;(c+b+b)-(c+a+d)

segment data use32 class = data 
    a dw 02Ah
    b dw 0A4h
    c dw 0Bh 
    d dw 0102h
    

segment code use32 class = data
start:
    mov AX, 0
    mov BX, 0
    mov CX, 0
    mov DX, 0
    
    mov AX, [c]
    mov BX, [b]
    mov CX, [b]
    add BX, CX
    add AX, BX
    
    mov CX, [c]
    mov DX, [a]
    add CX, DX
    mov DX, [d]
    add CX, DX
    
    sub AX, CX
    

push dword 0
call [exit]