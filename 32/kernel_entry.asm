bits 32
global _start  ; Make _start the entry point

KERNEL_LOCATION equ 0x1000

_start:
    ; Call the GDT
    ; call loadGDT

    mov eax, 0xB8000  
    mov byte [eax], 'A'  


    
    extern main
    call main

    jmp $




