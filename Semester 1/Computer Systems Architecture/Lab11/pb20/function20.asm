bits 32  
global prime
segment code use32 class= code        


prime:
    cmp eax, 0 ; eax = 0 =>not prime
    jz finish_not_prime
    
    cmp eax, 1; eax = 1 =>not prime
    jz finish_not_prime
    
    mov ecx, eax
    mov ebx, eax ; ebx = the number that we want to see if it is prime or not
    mov esi, 1
    
    repeta:
        inc esi; at start esi = 2; first iteration
        
        push eax
        push edx
        
        mov eax, ebx
        
        mov edx, 0
        div esi
        cmp edx, 0
        jz finish_not_prime
        
        pop edx
        pop eax
        
    loop repeta
    
    jmp finish_prime
    
    finish_not_prime:
        mov eax, 0
        ret 4*1; cleaning up the stack
        
    finish_prime:
        mov eax, 1
        ret 4*1
