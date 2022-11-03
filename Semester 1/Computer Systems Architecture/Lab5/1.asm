bits 32 
global start
extern exit
import exit msvcrt.dll
;5.A character string S is given. Obtain the string D containing all small letters from the string S.
;Example:
        ;S: 'a', 'A', 'b', 'B', '2', '%', 'x'
        ;D: 'a', 'b', 'x'
segment data use32 class=data
	S db 'a', 'A', 'b', 'B', '2', '%', 'x'
    l equ  $-S
    D times l db 0
segment code use32 class=code
start:
    mov ecx, l; ecx=l for the loop to iterate through all positions 
    mov esi, -1
    mov eax, 0
    jecxz finish; short jump if ecx=0
    mov al, 'Z'; so that we can verify that the elements of S are lowercase
    start_loop:
        inc esi
        mov bl, [S+esi]
        ;sub bl; 
        cmp al, bl; if [S+esi] is lowecase, then this should be <0
        jns start_loop;jump near if not negative signed
        mov [D+eax], bl
        inc eax
     
    loop start_loop
    
    
finish:; end of program      
          
        push dword 0; push the parameter for exit onto the stack
        call [exit]; call exit to terminate the program
        