data segment
s db 100 dup(0)
t db 100 dup(0)
data ends
code segment
assume cs:code,ds:data
main:
   mov ax, data
   mov ds, ax
   mov SI,0
   mov DI,0
input:
   mov ah, 1
   int 21h;  AL=getchar()
   cmp al, 0Dh; // to see if is enter
   je input_next
   mov s[SI],al
   add SI,1
   cmp al, 20h
   je input; //to see if is blank
   cmp al,7Ah; //to see if is small letter
   jbe may_small
fuzhi:
   mov t[DI],al
   add DI,1
   jmp input
may_small:
   cmp al,61h
   jae is_small
   jmp fuzhi
is_small:
   sub al,20h
   mov t[DI],al
   add DI,1
   jmp input
input_next:
   mov s[SI],00h
   mov DI,-1
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
   jmp output
output:
   mov ax, data
   mov ds, ax
   add DI,1
   mov dl,t[DI]
   cmp dl,00h
   je exit
   mov ah,2
   int 21h
   jmp output
exit:
   mov ah,4ch
   int 21h
code ends
end main