;File name: getNum.h
;Date: 2019/11/1
;Author: Yu Shan Huang
;National Taiwan University of Science Technology
;Department of Electrical Engineering
;This macro is used to scan keyboard input
;The return type will be a 5 bytes string in the following format: "num1 num2"


getNum macro para1, para2
    Local L1, esc_NotPress, After_Back, check, check_Loop, find_Space, mainPosition, error_Format, exit_getNum, FirstNumA, FirstNumB, After_Space, LastNum, Clear_Loop
    push ax                         ;push ax register
    push si                         ;push si register
    push bp                         ;push bp register
    mov si, 0   
    L1:
        mov ah, 00h
        int 16h                     ;Get keyboard input
        cmp al, 1bh                 ;if the keyboard input equals to 'esc', than program terminate.
        jne esc_NotPress
        mov ax, 4c00h
        int 21h                     ;DOS interrupt
        esc_NotPress:
        cmp al, 0Dh                 ;if the keyboard input equals to 'Enter', than terminates the input loop.
        je check       
        cmp al, 08h                 ;if the keyboard input IS NOT equals to 'Backspace', than jmp to After_Back.
        jne After_Back

        ;after pressing backapce, the following actions will be done. 
        mov para1[si], 00h          ;delete data from para1
        cmp si, 0                   ;if si equals to 0, which means the user has not type anything.
        je L1                       ;re-wating the keystroke
        mov ah, 02h                 ;si is not equals to 0, delete the last word
        mov dl, 08h                 ;print a backspace
        int 21h
        mov dl, 00h                 ;print a null
        int 21h
        mov dl, 08h                 ;print a backspace
        int 21h
        dec si                      ;si-1
        jmp L1                      ;re-wating the keystroke

        ;if the keyboard input is nethier Backspace nor Enter, store the data into string
        After_Back:
        cmp si, 4h                  ;exceed the require format 5 bytes
        jg L1                       ;re-wating the keystroke
        mov dl, al                  ;displaying the input
        push ax
        mov ah, 02h
        int 21h                     ;DOS interrupt
        pop ax                      ;store the input into para1
        mov para1[si], al   
        inc si                      ;increase si
        jmp L1                      ;re-wating the keystroke

    ;after pressing enter
    ;the input process was terminated.
    ;The following codes will check whether the input equals to the format  "num1 num2"   
    ;The input result was put into the para1 which is a 5-byte array.

    check:
    mov si, 0               
    cmp para1[1], 20h               ;If the first byte of para1 equals to space
    je FirstNumA                    ;Jump to FirstNumA. It represents the format "X₁ O₁O₂" which X₁ and O₁O₂ is number.  
    cmp para1[2], 20h               ;If the second byte of para1 equals to space
    je FirstNumB                    ;Jump to FirstNumB  It represents the fotmat "X₁X₂ O₁O₂" which X₁X₂ and O₁O₂ is number.
    jmp error_Format                ;The format is nethier FirstNumA nor FirstNumB than it is a error format, jump to error_Format 
    FirstNumA:
        cmp para1[si], 39h          ;If the data is above 39h or below 30h, means the data is not between 0-9 in decimal
        ja error_Format             ;jmp to error_Format
        cmp para1[si], 30h
        jb error_Format     
        push word ptr para1[si+2]   ;push O₁O₂ in "X₁ O₁O₂"
        mov al, para1[si]           ;mov X₁ to al 
        mov para1[si+1], al         ;It will become "X₁X₁O₁O₂"
        mov para1[si], '0'          ;It will become "0X₁O₁O₂"
        mov para1[si+2], 20h        ;It will become "0X₁ O₂" 
        pop word ptr para1[si+3]    ;pop back O₁O₂, it becomes "0X₁ O₁O₂"
        inc si                      
        jmp After_Space             ;Start to process O₁O₂
    FirstNumB:
        cmp para1[si], 39h          ;If the data is above 39h or below 30h, means the data is not between 0-9 in decimal
        ja error_Format             ;jmp to error_Format
        cmp para1[si], 30h
        jb error_Format 
        cmp si, 1                   ;Finishing checking. Start to process O₁O₂
        jge After_Space     
        inc si          
        jmp FirstNumB               ;check the second number
    After_Space:
        add si, 2                   ;check O₁
        cmp para1[si], 39h          ;If the data is above 39h or below 30h, means the data is not between 0-9 in decimal
        ja error_Format             ;jmp to error_Format
        cmp para1[si], 30h  
        jb error_Format
        inc si                      ;Check the fifth in para1. Three possible circumstances. 
        cmp para1[si], 00h          ;The fifth is null which means the O₁O₂ is only a units digit.
        je LastNum                  ;jmp ti LastNum
        cmp para1[si], 39h          ;If the data is above 39h or below 30h, means the data is not between 0-9 in decimal
        ja error_Format             ;jmp to error_Format
        cmp para1[si], 30h
        jb error_Format
        jmp exit_getNum             ;The O₁O₂ pass checking. Jmp to exit_getNum.
    LastNum:                        ;The format will be "X₁X₂ O₁"
        mov al, para1[si-1]         ;push O₁
        mov para1[si], al           ;The result will become "X₁X₂ O₁O₁"
        mov para1[si-1], '0'        ;The result will become "X₁X₂ 0O₁"
        jmp exit_getNum             ;Completed. jmp to exit_getNum

    error_Format:                   ;the format is error, displaying para2
        mov dx, offset para2
        mov ah, 09h
        int 21h                     ;DOS interrupt
        mov si, 4               
        Clear_Loop:                 ;Clear the contents in para1
            mov para1[si], 00h
            dec si
            cmp si, 0
            jge Clear_Loop
        mov si, 0
        jmp L1                      ;redo L1

    exit_getNum:                    ;Finishing the getNum process
    cmp word ptr para1[0], '00'     ;Check whether the X₁X₂ equals to 0
    je error_Format                 ;jmp to error_Format
    cmp word ptr para1[3], '00'     ;Check whether the O₁O₂ equals to 0
    je error_Format                 ;jmp to error_Format
    pop bp
    pop si
    pop ax
    endm                            ;end of macro