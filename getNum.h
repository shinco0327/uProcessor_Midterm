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
    push bp     ;push bp register
    mov si, 0   
    L1:
        mov ah, 00h
        int 16h     ;Get keyboard input
        cmp al, 0Dh     ;if the keyboard input equals to 'Enter', than terminates the input loop.
        je check       
        cmp al, 08h     ;if the keyboard input IS NOT equals to 'Backspace', than jmp to After_Back.
        jne After_Back

        ;after pressing backapce, the following actions will be done. 
        mov para1[si], 00h ;delete data from para1
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
    mov si, 0
    cmp para1[1], 20h
    je FirstNumA
    cmp para1[2], 20h
    je FirstNumB
    jmp error_Format
    FirstNumA:
        cmp para1[si], 39h
        ja error_Format 
        cmp para1[si], 30h
        jb error_Format 
        push word ptr para1[si+2]
        mov al, para1[si]
        mov para1[si+1], al
        mov para1[si], '0'
        mov para1[si+2], 20h
        pop word ptr para1[si+3]
        inc si
        jmp After_Space
    FirstNumB:
        cmp para1[si], 39h
        ja error_Format 
        cmp para1[si], 30h
        jb error_Format 
        cmp si, 1
        jge After_Space
        inc si
        jmp FirstNumB
    After_Space:
        add si, 2
        cmp para1[si], 39h
        ja error_Format 
        cmp para1[si], 30h
        jb error_Format
        inc si
        cmp para1[si], 00h
        je LastNum
        cmp para1[si], 39h
        ja error_Format 
        cmp para1[si], 30h
        jb error_Format
        jmp exit_getNum
    LastNum:
        mov al, para1[si-1]
        mov para1[si], al
        mov para1[si-1], '0'
        jmp exit_getNum

    error_Format:          ;the format is error, displaying para2
        mov dx, offset para2
        mov ah, 09h
        int 21h 
        mov si, 4
        Clear_Loop:
            mov para1[si], 00h
            dec si
            cmp si, 0
            jge Clear_Loop
        mov si, 0
        jmp L1             ;redo L1

    exit_getNum:
    cmp word ptr para1[0], '00'
    je error_Format
    cmp word ptr para1[3], '00'
    je error_Format
    pop bp
    pop si
    pop ax
    endm                   ;end macro