bits 32     
segment code use32 public code
global sum

sum:
    add eax, ebx
    sub eax, edx 
    
    ret 4*3 ; cleaning up the stack
 
