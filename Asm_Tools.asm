.code

Make_Sum proc
; extern "C" int Make_Sum(int value_1, int value_2)

	mov eax, value_1
	add eax, value_2

	ret

Make_Sum endp

end