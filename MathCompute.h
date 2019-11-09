;uProcessor Midterm Project
;File name: MathCompute.h
;Date: 2019/11/2
;Author: Yu Shan Huang
;StudentID: B10707049
;National Taiwan University of Science Technology
;Department of Electrical Engineering
;MathCompute.h provides serveral macroes which are used to conduct mathematics computation.

ASCIIDecimal macro result                   ;Convert ASCII into Decimal
    Local L1
    mov cx, 5                               ;The keyboard input stored in the array "NumStore" as parameter "result" in this macro. 
    mov si, 0                                 
    L1:
        add result[si] , 0D0h               ;The keyboard input stored as ASCII code, minus 30 to obtain numbers input.
        inc si
        loop  L1
    endm                                    ;end of macro

Combine macro result                        ;After the macro ASCIIDecimal, the tens digit of the number input and units digit of input stored separately.  
    mov bx, 0                               ;This macro will combine the tens digit and the units digit.
    add bl, result[0]
    mov al, 0Ah                             
    mul bl                                  ;Multiply result[0] with 10 
    mov bl, al                              ;Store in the bx register   
    add bl, result[1]                       ;add the units digit from result[1]
    mov cx, 0       
    add cl, result[3]           
    mov al, 0Ah                 
    mul cl                                  ;Multiply result[3] with 10 
    mov cl, al                              ;Store in the cx register
    add cl, result[4]                       ;add the units digit from result[4] 
    endm                                    ;end of macro

Computation macro result                    ;This macro will produce GCD and LCM
    Local GCD, L1, Leave
    mov dx, bx                              ;mov one num to dx
    mov ax, cx                              ;mov another to ax
    mul dx                                  ;Multiply ax with dx
    push ax                                 ;push the result. result is X₁X₂*O₁O₂
    cmp bx, cx                              ;cmp bx, cx
    jge GCD                                 
    push bx                                 ;if value in bx is smaller than value in cx
    push cx                                 ;Swap value
    pop bx
    pop cx
    GCD:                                    ;Finding GCD
    mov ax, bx                              ;mov bx to ax. Now, the bigger value stored in ax, the smaller stored in cx. 
    L1:                                     ;Euclidean algorithm
        mov dx, 0                           
        cmp cx, 0                           ;if cx equals to 0, break the loop
        jle Leave                           
        div cx                              ;ax divided by cx
        mov ax, cx                          ;mov cx to ax
        mov cx, dx                          ;mov the remainder to cx
        jmp L1                              ;jmp L1
    Leave:                                  ;Got GCD
    mov cx, ax                              ;mov ax to cx
    mov dx, 0                           
    pop ax                                  ;pop X₁X₂*O₁O₂
    div cx                                  ;Retun GCD at CX register, LCM at AX register
    endm                                    ;end of macro

HextoDecimal macro num_store                ;This macro will go through some procedures to display GCD and LCM in Decimal
    Local L1, L2, Exit_L2
    push bx                                 ;push GCD
    mov bp, sp                              ;mov bp, sp
    
    mov dx, 0h
    mov ax, SS:[bp]
    mov bx, 03E8h                           ;div ax by 03E8h
    div bx
    mov num_store[0], al                    ;save the thousands digit

    mov ax, dx                              ;mov the remainder to ax
    mov dx, 0
    mov bx, 0064h                           ;div ax by 0064h
    div bx
    mov num_store[1], al                    ;save the hundreds digit 

    mov ax, dx                              ;mov the remainder to ax
    mov dx, 0
    mov bx, 000Ah                           ;div ax by 000Ah
    div bx
    mov num_store[2], al                    ;mov the tens digit

    mov num_store[3], dl                    ;save the remainder as units digit
    mov si, 0       
    mov cx, 4
    L1:                                     ;Convert to ASCII code
        add num_store[si], 30h
        inc si
        loop L1
    mov num_store[4], '$'
    mov si, 0
    L2:                                     ;Blanking 0
        cmp num_store[si], 30h              ;if num_store[si] equals to '0'
        jne Exit_L2                         ;else jmp Exit_L2
        mov num_store[si], 20h              ;mov ' ' to it
        inc si
        jmp L2                              ;Next num_store[si]
    Exit_L2:
    mov sp, bp
    pop bx                                  ;pop bx
    endm                                    ;end of macro