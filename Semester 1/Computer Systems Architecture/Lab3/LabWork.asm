bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	m dq 1122334455667788h 
	n  dd 0ccddeeddh 
	rezd  resd 1 
	; our code starts here 
segment  code use32 class=code ; code segment
start: 
	mov  ebx, [n] 
	
	;11223344  55667788 h -> EDX : EAX 
	;   EDX   :   EAX 
	mov eax, dword [m+0] 
	mov edx, dword [m+4] 
	
	div ebx ; edx:eax/ebx=eax cat si edx rest 
	
	mov dword[rezd], eax 
	
	push  dword 0  ; push  the parameter for exit onto the stack 
	call  [exit] ; call exit to terminate the program