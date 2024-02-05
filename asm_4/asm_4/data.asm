.586
.model flat, stdcall
includelib kernel32.lib

.data
ExitProcess PROTO :DWORD

l0 dword 4294967295
l1 byte 6, 104, 101, 108, 108, 111, 0
l2 dword 0
l3 byte 6, 119, 111, 114, 108, 100, 0
l4 byte 1, 0

.code


main proc

push - 1
call ExitProcess
main endp

end main
