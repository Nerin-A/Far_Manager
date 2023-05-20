.code
;------------------------------------------------------------------------------------------------------------
Make_Sum proc
; extern "C" int Make_Sum(int value_1, int value_2)
; Parameters:
; RCX = value_1
; RDX = value_2
; Return RAX

	mov eax, ecx
	add eax, edx

	ret

Make_Sum endp
;------------------------------------------------------------------------------------------------------------
Draw_Line proc
; extern "C" void Draw_Line(CHAR_INFO* screen_buffer, XYPos pos, int length, CHAR_INFO symbol);
; Parameters:
; RCX = screen_buffer
; RDX = pos
; R8 = length
; R9 = symbol
; Return RAX
	
	push rax
	push rcx
	push rdi

	; Showing symbols
	mov rdi, rcx
	mov eax, r9d
	mov rcx, r8

	rep stosd

	pop rdi
	pop rcx
	pop rax

	ret

Draw_Line endp
;------------------------------------------------------------------------------------------------------------
end