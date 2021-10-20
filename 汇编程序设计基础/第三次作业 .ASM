.386
data segment use16
s db 100 dup(0)
t db 100 dup(0)
num db 100 dup(0)
firstnum dw 0
secondnum dw 0
result dd 0
h db "0123456789ABCDEF"
data ends
code segment use16
assume cs:code,ds:data
main:
   mov ax, data
   mov ds, ax
   mov SI,0
   mov DI,0
input_1:；读取第一个数字
   mov ah, 01h
   int 21h;  AL=getchar()
   cmp al, 0Dh; // to see if is enter
   je input_next_1_flag
   mov s[SI],al
   add SI,1
   jmp input_1
input_next_1_flag:
   mov s[SI],30h
   mov SI,0
   mov eax,0
   jmp input_trans_1
input_trans_1:；把第一个数字从字符变成数字
   sub s[SI],48
   cmp s[SI],00h
   je input_next_1
   mul firstnum
   ;sub s[SI],48
   mov firstnum,ax
   mov dl,s[SI]
   add firstnum,dx
   mov eax,10
   ;cmp s[SI],00h
   ;je input_next_1
   add s[SI],48
   add SI,1
   jmp input_trans_1
input_next_1:；换行
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
   mov SI,-1
   jmp input_2
input_2:；同1
   mov ah, 01h
   int 21h;  AL=getchar()
   cmp al, 0Dh; // to see if is enter
   je input_next_2_flag
   mov t[DI],al
   add DI,1
   jmp input_2
input_next_2_flag:
   mov t[DI],30h
   mov DI,0
   mov eax,0
   jmp input_trans_2
input_trans_2:
   sub t[DI],48
   cmp t[DI],00h
   je input_next_2
   mul secondnum
   ;sub t[DI],48
   mov secondnum,ax
   mov dl,t[DI]
   add secondnum,dx
   mov eax,10
   ;cmp t[DI],00h
   ;je input_next_2
   add t[DI],48
   add DI,1
   jmp input_trans_2
input_next_2:
   ;mov t[DI],00h
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
   mov DI,-1
   mov SI,-1
   jmp output_1
output_1:；输出第一个数字
   mov ax, data
   mov ds, ax
   add SI,1
   mov dl,s[SI]
   cmp dl,00h
   je output_next_1
   mov ah,2
   int 21h
   jmp output_1
output_next_1:；输出“*”
   mov dl,2Ah;
   mov ah,2
   int 21h
output_2:；输出第二个数字
   mov ax, data
   mov ds, ax
   add DI,1
   mov dl,t[DI]
   cmp dl,00h
   je output_next_2
   mov ah,2
   int 21h
   jmp output_2
output_next_2:；输出“=”
   mov dl,3Dh
   mov ah,2
   int 21h
   ;jmp huanhang_1
huanhang_1:；换行
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
multiple:；相乘
   mov ax,firstnum
   mul secondnum
   shl edx,16
   add eax,edx
   mov result,eax
   mov ebx,10
   xor ecx,ecx
   mov eax,result
output_d_push:；输出十进制，把数字压入堆栈
   xor edx,edx
   div ebx
   add edx,48
   push edx
   inc ecx
   or eax,eax
   jnz output_d_push
output_d_pop:；弹出
   xor edx,edx
   pop edx
   mov ah,2
   int 21h
   loop output_d_pop
huanhuang_2:；换行
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
   mov ebx,16
   mov eax,result
output_h_push:；输出十六进制，把数字压入堆栈
   xor edx,edx
   div ebx
   push ebx
   push eax
   mov bx,offset h
   mov al,dl
   xlat
   mov dl,al
   pop eax
   pop ebx
   push edx
   inc ecx
   or eax,eax
   jnz output_h_push
   cmp ecx,8
   jnb output_h_pop
bigger_8:；如果没到八位
   mov edx,48
   push edx
   inc ecx
   cmp ecx,8
   jb bigger_8
output_h_pop:；弹出
   xor edx,edx
   pop edx
   mov ah,02h
   int 21h
   loop output_h_pop
print_h:；输出h
   mov dl,48h
   mov ah,02h
   int 21h
huanhang_3:；换行
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
   mov ebx,2
   mov eax,result
output_b_push:；输出二进制数，把数字压入堆栈
   xor edx,edx
   div ebx
   add edx,48
   push edx
   inc ecx
   or eax,eax
   jnz output_b_push
   mov ebx,ecx
   add ebx,48
judge_4:；判断是否是4的倍数
   sub ebx,4
   cmp ebx,48
   je output_b_pop
   cmp ebx,48
   jb add_0
   jmp judge_4
add_0:；补零
   mov eax,48
   push eax
   inc ebx
   inc ecx
   cmp ebx,48
   je output_b_pop_pre
   jmp add_0
output_b_pop_pre:
   mov ebx,48
output_b_pop:；弹出
   xor edx,edx
   pop edx
   mov ah,02h
   int 21h
   add ebx,1
   cmp ebx,52
   je output_blank_judge
next:
   loop output_b_pop
print_b:
   mov dl,42h
   mov ah,02h
   int 21h
   jmp exit
output_blank_judge:
   cmp ecx,1
   je print_b
   jmp output_blank
output_blank:
   mov dl,20h
   mov ah,02h
   int 21h
   mov ebx,48
   jmp next
exit:
   mov ah,4ch
   int 21h
code ends
end main