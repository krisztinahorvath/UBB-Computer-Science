bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll  

;Two byte strings s1 and s2 are given. Build the byte string d such that, for every byte s2[i] in s2, d[i] contains either the position of byte s2[i] in s1, either the value of 0.

segment data use32 class=data
    s1 db 7, 33, 55, 19, 46
    l1 equ $-s1
    s2 db 33, 21, 7, 13, 27, 19, 55, 1, 46 
    l2 equ $-s2
    d times l2 db 0   ; 2,  0, 1, 0, 0, 4, 3, 0, 5     
  
; for (int i = 1; i<=len(s2); i++)
;{
;   int nr = s2[i]
;   int pos = 0
;   for(int j = 1; j<=len(s1); j++)
;       if(nr==s1[j])
;               pos = j
;       break
;   d[i]=pos
;}
segment code use32 class=code
    start:
        mov ecx, l2
        mov esi, s2
        mov ebx, 0; index for d
        
        loop_s2:
            lodsb ; al= the current element of s2;    al <- <DS:ESI>
            
            mov edi, s1  ; we move s1's address into edi, so that we can use scasb
            push ecx  
            mov ecx, l1  
            
            mov dl, 1; position where I find the number in s1
            loop_s1:
                scasb  ; CMP AL, <ES:EDI>
                je found
                inc dl
            loop loop_s1
            
            mov al, 0
            mov [d+ebx], al   
            jmp continue
            
            found:
                mov [d+ebx], dl; 
                
            continue:
                pop ecx 
                inc ebx
        loop loop_s2  
      
      
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
