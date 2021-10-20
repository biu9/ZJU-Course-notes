;现在是写完了文件读取功能，然后写了show_this_page函数，但
;我原计划的是先做到能显示十六进制表示下的偏移地址，所以在show_this_page函数中只写了这部分的内容
;在show_this_page函数中，写完了clear_this_page函数和strcpy函数，并且可以成功的显示出来
;目前在写long2hex函数，long2hex函数中的_lrotl函数也写完了
;char2hex函数起了个头，还在写


.386
stack1 segment stack use16
DD 100 dup (0)
stack1 ends

data segment use16
s db "00000000: xx xx xx xx|xx xx xx xx|xx xx xx xx|xx xx xx xx  ................","$"
pattern db "00000000:            |           |           |                             ","$"
t db "0123456789ABCDEF","$"
prompt_file db "Please input filename:","$"
prompt_file_1 db "open sucess","$"
open_error_1 db "Cannot open file!","$"
filename db 20
handle dw 0
file_size dw 0
new_offset dd 0
n dd 0
bytes_in_buf dw 0
buf db 256 dup(0)
data ends

code segment use16
assume cs:code, ds:data

my_strcpy:
   push bp
   mov bp,sp
   push bx
   push di
   mov bx,word ptr [bp+4];bx设为pattern
   mov di,word ptr [bp+6];di设为s
   my_strcpy_loop:
   cmp byte ptr [bx],"$"
   je my_strcpy_end
   mov al,ds:[bx]
   mov ds:[di],al
   inc bx
   inc di
   jmp my_strcpy_loop
   my_strcpy_end:
   pop di;恢复变量
   pop bx
   mov sp,bp
   pop bp
   ret

_lrotl:
   mov cl,8
   rol ax,cl
   and ax,00ffh;ax == xx  xx = offset & 0xFF;
   ret

char2hex:;把8位数转化成16进制格式
   push ax
   push cx
   mov cl,4
   shr ax,cl
   and al,0fh
   xlat;将四位翻译成ascii码
   pop ax
   pop cx
   ret

long2hex:;把32位数转化成16进制格式
   push bp
   mov bp,sp
   push bx;bx == xx
   push di;di == i
   push ax
   push dx
   mov ax,si;ax == offset
   mov di,0
   mov dx,4
long2hex_for_trans:
   inc di
   cmp di,dx
   call _lrotl;循环左移8位, 把高8位移到低8位
   call char2hex
   jb long2hex_for_trans
   jmp long2hex_for_end

long2hex_for_end:
   pop dx
   pop ax
   pop di;恢复变量
   pop bx
   mov sp,bp
   pop bp
   ret

show_this_row:
   push si
   mov si,ax
   mov bx,offset s
   push bx
   mov bx,offset pattern
   push bx
   call my_strcpy;strcpy的翻译
   call long2hex;把32位数转化成16进制格式
   pop bx
   pop bx
   pop si
   mov dx,offset s
   mov ah,09h
   int 21h
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
   ret

clear_this_page:;清屏
   mov ax, 0B800h
   mov es, ax
   mov ax,3
   int 10h;清屏
   mov SI,0Fh
   mov dl,31h
   ret

show_this_page:
   push bp
   mov bp,sp
   sub sp,6
   push bx
   push dx;保存变量
   push di
   ;bp-2:di i
   ;bp-4:dx rows
   ;bp-6:bx bytes_on_row
   call clear_this_page
   mov dx,0fh
   ;mov word ptr [bp-2],0
   ;mov ax,word ptr [bp-2]
   mov ax,0
for_trans:;for循环的翻译
   inc ax
   push ax
   push dx
   cmp ax,dx
   jae for_end_trans
   ;mov word ptr [bp-6],16
   jmp for_oneturn_end
for_oneturn_end:
   mov bx,10h
   mul bx
   push ax
   call show_this_row;画出一行
   pop ax
   pop dx
   pop ax
   jmp for_trans
for_end_trans:

drawrows_2:
   mov dx,offset s
   mov ah,09h
   int 21h

   pop di
   pop dx
   pop bx;回复变量
   mov sp,bp
   pop bp;恢复运行状态
   ret


main:
   mov ax,data
   mov ds,ax
   mov SI,0
put_sign:
   mov dx,offset prompt_file
   mov ah,09h
   int 21h
input_1:
   mov ah, 01h
   int 21h;  AL=getchar()
   cmp al, 0Dh; // to see if is enter
   je process_input
   mov filename[SI],al
   add SI,1
   jmp input_1
process_input:
   mov filename[SI],0;给文件名最后加上0
   mov SI,0
openfile:;打开文件
   mov ax,3D00h
   mov al,0
   mov dx,offset filename
   int 21h
   mov handle,ax
   jnc get_lenth
   jc open_error
get_lenth:;获取文件长度
   mov ah,42h
   mov al,2
   mov bx,handle
   mov cx,0
   mov dx,0
   mov word ptr file_size[2], dx
   mov word ptr file_size[0], ax
mov_to_head:;文件指针移到文件头
   mov ah,42h
   mov al,0
   mov bx,handle
   mov cx,0
   mov dx,0
   int 21h
   mov word ptr new_offset[0],0;将初始的偏移量设为0
   mov word ptr new_offset[2],0;
   jmp do_if_trans
sucess_quit:
   mov ah, 3Eh
   mov bx, handle
   int 21h
   mov ah,4ch
   int 21h
open_error:;如果打开文件失败则显示error
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
   mov dx,offset open_error_1
   mov ah,09h
   int 21h
   mov ah,4ch
   int 21h
do_if_trans:;do循环中的if的翻译
   mov ax,word ptr file_size[0];
   mov dx,word ptr file_size[2];
   sub ax,word ptr new_offset[0];
   sbb dx,word ptr new_offset[2];进行连减完成32位无符号整数的减法
   mov word ptr n[2],dx
   mov word ptr n[0],ax;n = filesize-offset
   cmp word ptr n[2],0
   ja above_256
   cmp word ptr n[0],0100h 
   jae above_256
   jmp blow_256
above_256:
   mov word ptr bytes_in_buf,256
   jmp next
blow_256:
   mov ax,word ptr n[0]
   mov word ptr bytes_in_buf[0],ax;将字符数设为n
next:
   call show_this_page;调用show_this_page
exit:
   mov ah,4ch
   int 21h
code ends
end main