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
    mov dx, bx
    mov ax, cx
    mul dx
    mov dx, ax
    
    endm