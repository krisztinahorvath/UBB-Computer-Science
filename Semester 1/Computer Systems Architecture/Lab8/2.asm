bits 32  


global start        

;text file operations

;A file name and a text (defined in the data segment) are given. 
;The text contains lowercase letters and spaces. 
;Replace all the letters on even positions with their position. 
;Create a file with the given name and write the generated text to file.
 

extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
    

segment data use32 class=data
   text db "ana has apples"
   len equ $-text
   
   file_name db "ana.txt", 0
   access_mode db "a", 0
   file_descriptor dd -1
   
   
segment code use32 class=code
    start:
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je final
        
        mov ecx, len
        mov esi, 0
        
        loop_replace:
            mov bl, [esi] ; look at the parity of the index
            test bl, 1
            jz even_number
            jmp continue
            
            even_number:
                mov bl, [text + esi]; the character that is on position esi
                mov bh, 'a'
                cmp bh, bl
                jb continue ; jump short if the ascii code of the character is not above or equal to a=>not a small letter
                mov [text+esi], bl
                
            continue:
                inc esi
           
        loop loop_replace
        
        ; append to the file
        push dword text
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*2

        ; close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        
        final:
            push    dword 0      
            call    [exit]       
