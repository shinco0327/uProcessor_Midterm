;uProcessor Midterm Project
;File name: Project.asm
;Date: 2019/10/30
;Author: Yu Shan Huang
;National Taiwan University of Science Technology
;Department of Electrical Engineering
include ProjectPrint.h      
include getNum.h
include MathCompute.h

.model small                

.data
str1 db "Please enter two numbers between 1 to 99:" ,10,13,'$'    
error_message db 10, 13, "Error Format. Please enter numbers between 1 to 99", 10, 13, "The example format is like 20 50. Please enter again!", 10 ,13, '$'
str2 db 10, 10, 13, "in Hex: $"
str3 db 10, 10, 13, "in Decimal: $"
str4 db 10, 13, "GCD is $"
str5 db 10, 13, "LCM is $"
str6 db 10, 10, 13, "Press esc to exit. Press other keys to continue. ", 10, 13, '$'
NumStore db 5 dup(?)
mul_result dw ?

.stack 100h

.code
main proc
Program_Start:                              ;Program start at here
	mov ax, @data
    mov ds, ax
    printStr str1                           ;Print "Please enter two numbers between 1 to 99:"
    getNum NumStore, error_message          ;Get keyboard input. Two parameters.
    DataConvertion:                         ;Received keyboard input, starting computation. 
    ASCIIDecimal NumStore                   ;ASCIIDecimal from mathCompute.h 
    Combine NumStore                        ;Combine from mathCompute.h
    Computation mul_result                  ;Computation from mathCompute.h Retun GCD at CX register, LCM at AX register
    printStr str2                           ;Print "in Hex:"
    printStr str4                           ;Print "GCD is "
    printNum NumStore                       ;Print GCD in Hex
    printStr str5                           ;Print "LCM is "
    push cx                                 ;push GCD
    mov cx, ax                              ;mov LCM to CX
    printNum NumStore                       ;Print LCM in hex
    pop bx                                  ;pop GCD
    push cx                                 ;push LCM                                  
    HextoDecimal NumStore                   ;HextoDecimal from mathCompute.h Result will be stored in NumStore
    printStr str3                           ;Print "in Decimal:" 
    printStr str4                           ;Print "GCD is "                           
    printStr NumStore                       ;Print GCD in Decimal
    pop bx                                  ;pop LCM
    HextoDecimal NumStore                   ;HextoDecimal from mathCompute.h Result will be stored in NumStore          
    printStr str5                           ;Print "LCM is"
    printStr NumStore                       ;Print LCM is Decimal
    printStr str6                           ;Print "Press esc to exit. Press other keys to continue. "
    mov ah, 00h                             ;Wait for keystroke
    int 16h
    cmp al, 1bh                             ;if input equals to esc, program terminates.
    jne Program_Start
    mov ax, 4c00h                           ;exit to DOS
    int 21h
main endp
end main
