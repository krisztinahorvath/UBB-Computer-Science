bits 32 
global start
extern exit
import exit msvcrt.dll
;20.Two byte strings A and B are given. Obtain the string R by concatenating the elements of B in reverse order ;and the even elements of A.
;Example:
        ;A: 2, 1, 3, 3, 4, 2, 6
        ;B: 4, 5, 7, 6, 2, 1
        ;R: 1, 2, 6, 7, 5, 4, 2, 4, 2, 6
segment data use32 class=data
	A db 2, 1, 3, 3, 4, 2, 6
    la equ $-A
    B db 4, 5, 7, 6, 2, 1
    lb equ $-B
    R times la+lb db 0
segment code use32 class=code
start:
    mov ecx, lb+1 
    mov eax, 0
    mov esi, lb
    mov edx, 0
    
    loop_B:
        mov bl, [B+esi]
        mov [R+eax], bl
        inc eax
        dec esi
        
    loop loop_B
    mov esi, 0
    
    mov ecx, la
    loop_A:
        mov bl, [A+esi]
        test bl,1
        jz even_number
        jmp continue
        even_number:
            mov [R+eax], bl
            inc eax
        continue:
        
        inc esi
    loop loop_A
        
     
finish:; end of program     
        push dword 0; push the parameter for exit onto the stack
        call [exit]; call exit to terminate the program
        