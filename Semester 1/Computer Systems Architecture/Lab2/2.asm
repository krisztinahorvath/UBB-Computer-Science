bits 32
global start

extern exit
import exit msvcrt.dll

; additons, subtractions
; a, b, c, d - byte
; ex:20
;(a+a)-(c+b+d)
segment data use32 class = data
    a db 07h
    b db 02h
    c db 08h
    d db 01h

segment code use 32 class = code
start:
    mov AL, 0
    mov BL, 0
    mov CL, 0
    
    mov AL, [a]
    mov BL, [a]
    add AL, BL
    
    mov BL, [c]
    mov CL, [b]
    add BL, CL
    mov CL, [d]
    add BL, CL
    
    sub AL, BL


push dword 0
call [exit]