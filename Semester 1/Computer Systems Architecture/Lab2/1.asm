bits 32 
global start


extern exit 
import exit msvcrt.dll          

; additons, subtractions
; a, b, c, d - byte
; ex:5
;(c-a-d)+(c-b)-a
segment data use32 class=data
    a db  07h
    b db  01h
    c db  09h
    d db  02h


segment code use32 class=code
start:
    mov AL, 0
    mov BL, 0
    mov CL, 0
    mov DL, 0
    
    mov AL, [c]
    mov DL, [a]
    sub AL, DL
    mov DL, [d]
    sub AL, DL
    
    mov BL, [c]
    mov CL, [b]
    sub BL, CL
    
    add AL, BL
    mov BL, [a]
    sub AL, BL
    
    
    push dword 0 
    call [exit] 