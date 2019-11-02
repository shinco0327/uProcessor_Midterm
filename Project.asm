;uProcessor Midterm Project
;File name: Project.asm
;Date: 2019/10/30
;Author: Yu Shan Huang
;National Taiwan University of Science Technology
;Department of Electrical Engineering
include printStr.h
include getNum.h
include MathCompute.h
.model small

.data
str1 db "Please enter two numbers between 1 to 99:" ,10,13,'$'
error_message db 10, 13, "Error Format. The example format is like 20 50.", 10, 13, "Please enter again!", 10 ,13, '$'
str2 db 10, 13, "in hex: $"
str3 db 10, 13, "in Decimal: $"
str4 db 10, 13, "GCD is $"
str5 db 10, 13, "LCM is $"
input_str db 5 dup(?)
mul_result dw ?

.stack 100h

.code
main proc
	mov ax, @data
    mov ds, ax
    printStr str1
    getNum input_str, error_message

    DataConvertion:
    ASCIIDecimal    
    Combine 
    MathCompute mul_result ;GCD cx L ax
    push ax
    printStr str2
    printStr str4
    printNum input_str
    printStr str5
    pop cx
    printNum input_str
    

    mov ax, 4c00h
    int 21h
main endp
end main
