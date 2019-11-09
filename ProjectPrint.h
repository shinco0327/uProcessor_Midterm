;uProcessor Midterm Project
;File name: ProjectPrint.h
;Date: 2019/11/3
;Author: Yu Shan Huang
;StudentID: B10707049
;National Taiwan University of Science Technology
;Department of Electrical Engineering
;ProjectPrint.h included two macroes which are used to display message or number

printStr macro para1                        ;The macro prints a string          
    push ax                                 ;push ax
    push dx                                 ;push dx
    mov dx, offset para1                    ;mov the starting address of para1 to dx
    mov ah, 09h
    int 21h                                 ;DOS interrupt
    pop dx                                  ;pop dx
    pop ax                                  ;pop ax
    endm                                    ;end of macro

printNum macro result                       ;This macro prints number in cx
    Local ADD_1, ADD_2, ADD_3, ADD_4, L1, Exit_L1
    push bp                                 ;push following register bp, bx, ax, si, cx
    push bx
    push ax
    push si
    push cx                                 
    mov bp, sp                              ;Make the bp point to sp
    mov bx, SS:[bp]                         ;mov the data orginally stored in cx to bx 

    mov cl, 4                               
	shr bh, cl                              ;Only the first nibble will be left                              
    cmp bh, 9h                              ;If the number is in hex form, and is between A to F
    jle ADD_1                               ;Store the result
    add bh, 07h                             ;add 07h first, add 30h after
    ADD_1:                                  ;if the number is between 0-9, adding 30h only
	add bh, 30h                             ;add 30h 
    mov result[0], bh 

	mov bx, SS:[bp]                         ;mov the data orginally stored in cx to bx  
	shl bh, cl                              ;shift
	shr bh, cl                              ;Only the second nibble will be left
    cmp bh, 9h                              ;If the number is in hex form, and is between A to F
    jle ADD_2
    add bh, 07h                             ;add 07h first, add 30h after
    ADD_2:                                  ;if the number is between 0-9, adding 30h only
	add bh, 30h                             ;add 30h
	mov result[1], bh                       ;Store the result

    mov bx, SS:[bp]                         ;mov the data orginally stored in cx to bx 
	shr bl, cl                              ;Only the third nibble will be left                                                         
    cmp bl, 9h  
    jle ADD_3                               ;If the number is in hex form, and is between A to F
    add bl, 07h                             ;add 07h first, add 30h after
    ADD_3:                                  ;if the number is between 0-9, adding 30h only
	add bl, 30h                             ;add 30h
	mov result[2], bl                       ;Store the result

	mov bx, SS:[bp]                         ;mov the data orginally stored in cx to bx 
	shl bl, cl                              ;Only the fourth nibble will be left 
	shr bl, cl
    cmp bl, 9h                              ;If the number is in hex form, and is between A to F
    jle ADD_4
    add bl, 07h                             ;add 07h first, add 30h after
    ADD_4:                                  ;if the number is between 0-9, adding 30h only
	add bl, 30h
	mov result[3], bl                       ;Store the result

    mov result[4], '$'                      ;End of the string
    mov si, 0                                     
    L1:                                     ;Blanking 0
        cmp result[si], 30h                 ;if result[si] equals to '0'
        jne Exit_L1                         ;else exit L1
        mov result[si], 20h                 ; mov ' ' to it
        inc si                              
        jmp L1                              ;next result[si]
    Exit_L1:
    mov ah, 09h                             
    mov dx, offset result                   ;mov the starting address of result to dx
    int 21h                                 ;DOS interrupt
    pop cx                                  ;pop the register
    pop si
    pop ax
    pop bx
    pop bp
    endm                                    ;end of macro

