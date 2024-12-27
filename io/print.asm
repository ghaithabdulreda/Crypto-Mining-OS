print:
	mov ah,0Eh
	mov al,[bx]
	cmp al,0
	je .die
	inc bx
	int 10h
	jmp  print
	.die:
		ret