;File name: MathCompute.h
;Date: 2019/11/2
;Author: Yu Shan Huang
;National Taiwan University of Science Technology
;Department of Electrical Engineering

ASCIIDecimal macro
    Local L1
    mov cx, 5
    mov si, 0
    L1:
        add input_str[si] , 0D0h
        inc si
        loop  L1
    endm

Combine macro
    mov bx, 0
    add bl, input_str[0]
    mov al, 0Ah
    mul bl
    mov bl, al
    add bl, input_str[1]
    mov cx, 0
    add cl, input_str[3]
    mov al, 0Ah
    mul cl
    mov cl, al
    add cl, input_str[4]
    endm

MathCompute macro result
    Local GCD, L1, Leave
    mov dx, bx
    mov ax, cx
    mul dx
    push ax
    cmp bx, cx
    jge GCD
    push bx
    push cx
    pop bx
    pop cx
    GCD:
    mov ax, bx
    L1:
        mov dx, 0
        cmp cx, 0
        jle Leave
        div cx
        mov ax, cx
        mov cx, dx
        jmp L1
    Leave:
    mov cx, ax
    mov dx, 0
    pop ax
    div cx
    endm

HextoDecimal macro num_store
    Local L1
    push bx
    mov bp, sp
    mov cl, 4
    shl bl, cl
    shr bl, cl
    mov al, 1
    mul bl
    mov dx, ax

    mov bx, SS:[bp]
    shr bl, cl
    mov al, 10h
    mul bl
    add dx, ax

    push dx
    mov bp, sp
    mov bx, SS:[bp+2]
    shl bh, cl
    mov cl, 0ch
    shr bx, cl
    mov ax, 100h
    mul bx
    add ss:[bp], ax

    mov bx, SS:[bp+2]
    mov cl, 0ch
    shr bx, cl
    mov ax, 1000h
    mul bx
    add ss:[bp], ax

    mov dx, 0h
    mov ax, SS:[bp]
    mov bx, 03E8h
    div bx
    mov num_store[0], al

    mov ax, dx
    mov dx, 0
    mov bx, 0064h
    div bx
    mov num_store[1], al

    mov ax, dx
    mov dx, 0
    mov bx, 000Ah
    div bx
    mov num_store[2], al

    mov num_store[3], dl
    mov si, 0
    mov cx, 4
    L1:
        add num_store[si], 30h
        inc si
        loop L1
    mov num_store[4], '$'

    pop bx
    pop bx
    endm