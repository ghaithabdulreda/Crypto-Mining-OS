loadGDT:
    ; jmp KERNEL_LOCATION
    cli                                
    lgdt [gdt_pointer]             

    mov eax, cr0                   
    or eax, 0x1                    
    mov cr0, eax                   
    jmp CODE_SEG:boot2              ; jump to boot2

gdt_start:
    dd 0x0
    dd 0x0
gdt_code:
    dw 0xFFFF                               ; Limit 0xFFFF 
    dw 0x0                                  ; Base_LOW 0
    db 0x0                                  ; base_MIDDLE 0
    db 0x9A                                 ; Access byte
    db 11001111b                            ; Flags
    db 0x0                                  ; Base_HIGH 0
gdt_data:
    dw 0xFFFF                               ; Limit 0xFFFF 
    dw 0x0                                  ; Base_LOW 0
    db 0x0                                  ; Base_MIDDLE 0
    db 0x92                                 ; Access byte
    db 11001111b                            ; fLags
    db 0x0 
gdt_end:
gdt_pointer:
    dw gdt_end - gdt_start-1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start



goTo32Bit:


bits 32

boot2:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x300000     
    mov esp, ebp          



    
    ; mov byte [0xb8000], 'W'
    jmp KERNEL_LOCATION

; [extern main]
; call main
; jmp $

; vide_MEMORY equ 0xb8000


    ; mov cx,5
    ; lop:
    ; mov ax,0xf61 ; white "a" ; 61 = a ; 0x0f = white chat and black black background
    ; mov ax, word [0xf61]
    ; mov [0xb8000],ax ; print to the screen
        ; inc bx
    ; loop lop

    ; mov ax,0xf61 ; white "a" ; 61 = a ; 0x0f = white chat and black black background

    ; jmp $    ; mov [0xb8000],ax ; print to the screen
    ; jmp $

