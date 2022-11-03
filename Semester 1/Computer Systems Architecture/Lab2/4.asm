bits 32
global start

extern exit
import exit msvcrt.dll

; additons, subtractions
; a, b, c, d - word
; ex:20
;b-(b+c)+a

segment data use32 class = data
    a db 07h
    b db 0Ch
    c db 03h

segment code use32 class = code
start:
    mov AL, 0
    mov BL, 0
    
    mov AL, [b]
    mov BL, [c]
    add BL, AL
    
    sub AL, BL
    add AL, [a]

push dword 0
call [exit]
