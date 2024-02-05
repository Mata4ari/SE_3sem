.586
.model flat, stdcall
includelib kernel32.lib

ExitProcess PROTO :DWORD
MessageBoxA proto :dword,:dword,:dword,:dword

.stack 4096

.const
a dword 3
b dword 4

.data
MB_OK EQU 0
str1 DB "Моя первая программа", 0
str2 db "Результат сложения = ", 0
str3 db 25 dup(?)
result db 0
HW DD ?

.code

sum proc 
	
	mov eax,ecx
	add eax,edx
	ret
sum endp

main proc
	
	mov ecx,a
	mov edx,b
	call sum
	mov result,al
	add result,48
	
	lea si, str2
    lea di, str3
	copy_string:
    mov al, [esi]
    mov [edi], al
    inc si
    inc di
    cmp al, 0  
    jnz copy_string

    
    mov al, result
    mov [edi-1], al


	INVOKE MessageBoxA, HW, offset str3, offset str1, MB_OK

	
	push -1
	call ExitProcess
main endp

end main