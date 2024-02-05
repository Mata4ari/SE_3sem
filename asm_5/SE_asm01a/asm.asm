.586
.model flat, stdcall



.code

findmin proc uses ebx ecx, parm1:dword, parm2:dword 


mov ebx,parm2
mov ecx,parm1


mov eax, [ebx] 
add ebx,4 
dec ecx 
jz endloop 

    loopstart:
        cmp eax, [ebx] 
        jle notless 

        mov eax, [ebx] 

        notless:
            add ebx,4 
            dec ecx 
            jnz loopstart 

    endloop:



ret 8
findmin endp


findmax proc uses ecx ebx, parm1:dword, parm2:dword


mov ecx,parm1
mov ebx,parm2


mov eax, [ebx] 
add ebx,4 
dec ecx 
jz endloop 

    loopstart:
        cmp eax, [ebx] 
        jae notless 

        mov eax, [ebx] 

        notless:
            add ebx,4 
            dec ecx 
            jnz loopstart 

    endloop:

ret 8

findmax endp


end 