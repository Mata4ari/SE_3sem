.586
.model flat, stdcall
includelib kernel32.lib
includelib SE_asm01a.lib
includelib ucrt.lib

system proto C:dword
SetConsoleTitleA proto :dword
GetStdHandle proto :dword
WriteConsoleA proto :dword, :dword, :dword, :dword, :dword
ExitProcess PROTO :DWORD
findmin proto:dword, :dword
findmax proto:dword, :dword

.const
endl equ 0ah
str_endl byte endl,0

.data

arr dword 177,888,154,154,155,4587,22,369,1111,99999
arrlength =($-arr)/4
result1 dword ?
result2 dword ?
result3 dword ?
consoleHandle dword 0h
str1 byte 'Hello world!!',0
str2 byte 'Console',0
str_pause byte 'pause',0
num1 byte 12 dup(0)
num2 byte 12 dup(0)
num3 byte 12 dup(0)
plus_str byte ' + ',0
equal_str byte ' = ',0

.code
;-----------------------------
printconsole proc uses eax ebx ecx edi esi,
					   pstr:dword, ptitle: dword

push ptitle
call SetConsoleTitleA
push -11
call GetStdHandle
mov esi,pstr
mov edi,-1
count:
inc edi
cmp byte ptr[esi+edi],0
jne count

push 0
push 0
push edi
push pstr
push eax
call WriteConsoleA

ret
printconsole endp
;--------------------------
int_to_char proc uses eax ebx ecx edi esi,
pstr:dword,
intfield:dword

mov edi,pstr
mov esi,0
mov eax,intfield
cdq
mov ebx, 10
idiv ebx
test eax,80000000h
jz plus
neg eax
neg edx
mov cl,'-'
mov [edi],cl
inc edi
plus:
	push dx
	inc esi
	test eax,eax
	jz fin
	cdq
	idiv ebx
	jmp plus
fin:
	mov ecx,esi
write:
	pop bx
	add bl,'0'
	mov [edi],bl
	inc edi
	loop write

	ret
int_to_char endp
;---------------------------
main proc

push offset arr
push arrlength
call findmin ; findmin-->eax
mov result1,eax
mov result3,eax
push offset arr
push arrlength
call findmax; findmax-->eax
mov result2,eax
add result3,eax


push result1
push offset num1
call int_to_char

push offset str2
push offset num1
call printconsole

push offset str2
push offset plus_str
call printconsole

push result2
push offset num2
call int_to_char

push offset str2
push offset num2
call printconsole

push offset str2
push offset equal_str
call printconsole

push result3
push offset num3
call int_to_char

push offset str2
push offset num3
call printconsole

push offset str2
push offset str_endl
call printconsole

push offset str_pause
call system


	push -1
	call ExitProcess
main endp

end main

