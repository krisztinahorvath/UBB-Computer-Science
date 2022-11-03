bits 32
global start

extern exit
import exit msvcrt.dll

; multiplications, divisions
; a, b, c - byte, d - word
; ex:5
; [d-2*(a-b)+b*c]/2

segment data use32 class = data
    a db 04h
    b db 02h
    c db 03h
    d dw 0011h

segment code use32 class = code
start:
    mov AX, 0
    mov BX, 0
    mov CX, 0
    
    mov CL, [a] ; 2*(a-b)
    mov BL, [b]
    sub CL, BL
    
    mov AL, 02h
    mul CL
    
    mov CX, [d] ; d-2*(a-b)
    sub CX, AX
    
    mov AL, [b] ; b*c
    mov BL, [c]
    mul BL             
    
    add AX, CX ; d-2*(a-b)+b*c
    
    add CL, 02h ; [d-2*(a-b)+b*c]/2
    div CL
   

push dword 0
call [exit]