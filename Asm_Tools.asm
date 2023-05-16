.code

Make_Sum proc
; extern "C" int Make_Sum(int value_1, int value_2)
; RCX = value_1
; RDX = value_2
; Return RAX

	mov eax, ecx
	add eax, edx

	ret

Make_Sum endp

end