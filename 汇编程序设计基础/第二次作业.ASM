data segment
d db 100 dup(0)
data ends
code segment
assume cs:code, ds:data
main:
   mov ax, 0B800h
   mov es, ax
   mov ax,3
   int 10h;清屏
   mov di,0
   mov dx, 00h
   mov si,0
   mov ah, 00h
   mov d[si], ah
   mov d[si+1], ah
again:
   mov al, dx; 输出asc码
   mov ah, 0Ch; 红色
   mov word ptr es:[di], ax; 输出asc码
print_number1:；输出十位数
   add di,2
   add d[si], 30h
   mov al, d[si]
   mov ah, 02h
   mov word ptr es:[di],ax
   sub di, 2
   sub d[si], 30h
print_number2:；输出个位数
   add di,4
   add d[si+1], 30h
   mov al, d[si+1]
   mov ah, 02h
   mov word ptr es:[di],ax
   sub di, 4
   sub d[si+1], 30h
   cmp d[si+1], 09h
   je jingwei
   cmp d[si+1], 16h
   jae jianwei
   add d[si+1], 1
   jmp next
jianwei:；进位，到F时
   sub d[si+1], 16h
   add d[si], 01h
   cmp d[si], 0Ah
   je jingwei2
   jmp next
jingwei2:；进位，从9到A
   add d[si], 07h
   jmp next
jingwei:
   add d[si+1], 8
   jmp next
next:
   add dx, 1
   add di, 160
   cmp di,4000
   jae next_row
   cmp dx, 0FFh
   ja exit
   jmp again
next_row:；换列
   sub di,4000
   add di, 14
   jmp again
exit:
   mov dl, 0Dh
   int 21h; 输出回车
   mov dl, 0Ah
   int 21h; 输出换行
   mov ah,1