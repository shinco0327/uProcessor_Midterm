;printStr.h

printStr macro para1
    push ax
    push dx
    mov dx, offset para1
    mov ah, 09h
    int 21h
    pop dx 
    pop ax
    endm

printNum macro result
    Local ADD_1, ADD_2, ADD_3, ADD_4
    push bp
    push bx
    push cx
    mov bp, sp
    mov bx, SS:[bp]

    mov cl, 4
	shr bh, cl
    cmp bh, 9h
    jle ADD_1
    add bh, 07h
    ADD_1:
	add bh, 30h
    mov result[0], bh 

	mov bx, SS:[bp] 
	shl bh, cl
	shr bh, cl
    cmp bh, 9h
    jle ADD_2
    add bh, 07h
    ADD_2:
	add bh, 30h
	mov result[1], bh

    mov bx, SS:[bp]
	shr bl, cl
    cmp bl, 9h
    jle ADD_3
    add bl, 07h
    ADD_3:
	add bl, 30h
	mov result[2], bl

	mov bx, SS:[bp]
	shl bl, cl
	shr bl, cl
    cmp bl, 9h
    jle ADD_4
    add bl, 07h
    ADD_4:
	add bl, 30h
	mov result[3], bl 

    mov result[4], '$'
    mov ah, 09h
    mov dx, offset result
    int 21h
    pop cx
    pop bx
    pop bp
    endm