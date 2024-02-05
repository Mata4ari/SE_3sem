.586
.model flat, stdcall
includelib kernel32.lib

ExitProcess PROTO :DWORD
MessageBoxA proto :dword,:dword,:dword,:dword

.stack 4096

.const


.data
myBytes byte 10h, 20h, 30h, 40h
myWords word 8Ah, 3Bh, 44h, 5Fh, 99h
myDoubles dword 1, 2, 3, 4, 5, 6
myPointer dword myDoubles
arr dword 12, 3, 5, 32, 0, 1, 10
len byte $-arr
leng dword ($-arr)/4
HW DD ?
MB_OK EQU 0

.code

sum proc

xor ebx,ebx
xor eax,eax

mov al,len
mov bl,4
div bl
mov ecx,eax

xor ebx,ebx
lea ebx, arr

xor eax, eax	 
cikl: 	add ax, [ebx]	
add bx,4	
loop cikl
ret

sum endp

nullCheck proc

 mov ecx, 0 
 lea ebx, arr

LoopStart:
    cmp ecx, leng
    jge NotFound 

    mov eax, [ebx + ecx * 4] 
    cmp eax, 0 
    jz FoundZero 

    inc ecx 
    jmp LoopStart 

FoundZero:
    mov ebx,0
    ret

NotFound:
    mov ebx,1
    ret

nullCheck endp

main proc

call sum
call nullCheck

mov ebx, myPointer
mov eax, [ebx+4]
mov edx, [ebx]



	
	push -1
	call ExitProcess
main endp

end main