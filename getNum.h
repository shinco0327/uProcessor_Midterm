;File name: getNum.h
;Date: 2019/11/1
;Author: Yu Shan Huang
;National Taiwan University of Science Technology
;Department of Electrical Engineering
;This macro is used to scan keyboard input
;The return type will be a 5 bytes string in the following format: "num1 num2"


getNum macro para1, para2
    Local L1, After_Back, check, check_Loop, find_Space, mainPosition, error_Format, exit_getNum
    push ax     ;push ax register
    push si     ;push si register
    mov si, 0   
    L1:
        mov ah, 00h
        int 16h     ;Get keyboard input
        cmp al, 0Dh     ;if the keyboard input equals to 'Enter', than terminates the input loop.
        je check        
        cmp al, 08h     ;if the keyboard input IS NOT equals to 'Backspace', than jmp to After_Back.
        jne After_Back

        ;after pressing backapce, the following actions will be done. 
        cmp si, 0       ;if si equals to 0, which means the user has not type anything.
        je L1           ;re-wating the keystroke
        mov ah, 02h     ;si is not equals to 0, delete the last word
        mov dl, 08h     ;print a backspace
        int 21h
        mov dl, 00h     ;print a null
        int 21h
        mov dl, 08h     ;print a backspace
        int 21h
        dec si          ;si-1
        jmp L1          ;re-wating the keystroke

        ;if the keyboard input is nethier Backspace nor Enter, store the data into string
        After_Back:
        cmp si, 4h      ;exceed the require format 5 bytes
        jg L1           ;re-wating the keystroke
        mov dl, al      ;displaying the input
        push ax
        mov ah, 02h
        int 21h         
        pop ax          ;store the input into para1
        mov para1[si], al   
        inc si          ;increase si
        jmp L1          ;re-wating the keystroke

    ;after pressing enter
    ;the input process was terminated.
    ;The following codes will check whether the input equals to the format  "num1 num2"   
    check:
    mov si, 4
    check_Loop:
        cmp si, 2       
        jne mainPosition        
        cmp para1[2], 20h   ;check the blank at para1[2]
        jne error_Format    ;error format
        je find_Space
        find_Space:
            dec si 
        mainPosition:       ;check other data is from 0-9 
            cmp para1[si], 39h
            ja error_Format 
            cmp para1[si], 30h
            jb error_Format
        dec si
        cmp si, 0          ;check process completed
        jle exit_getNum    ;jump to exit_getNum
        jmp check_Loop

    error_Format:          ;the format is error, displaying para2
        mov dx, offset para2
        mov ah, 09h
        int 21h 
        mov si, 0
        jmp L1             ;redo L1

    exit_getNum:
    pop si
    pop ax
    endm                   ;end macro