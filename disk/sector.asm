readSector:
    ; mov bx,0x7e00 ; mov now to this buffer
    mov bx,KERNEL_LOCATION ; READ kernel_entry.o and kernel.o FILE WHEN I COMPILED
    mov ah,02h
    mov al,50 ; How many Bytes i can read from my disk
    mov ch,0
    mov dh,0
    mov dl,0
    mov cl, 2
    int 13h


    jc whenErrorReadSector
    call delay_5_seconds

    mov bx, readSectorSu_msg
    call print
    call delay_5_seconds
    call delay_5_seconds
    ; ret
    ; mov bx,readDiskSu

    jmp loadGDT
    ; ret
    ; call goTo64Bit

whenErrorReadSector:
    mov bx,errorToReadDisk_msg
    call print
    jmp halt
