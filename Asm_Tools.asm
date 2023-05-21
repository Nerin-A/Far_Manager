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
Draw_Line_Horizontal proc
; extern "C" void Draw_Line_Horizontal (CHAR_INFO* screen_buffer, XYPos pos, CHAR_INFO symbol);
; Parameters:
; RCX = screen_buffer
; RDX = pos
; R8 = symbol
; Return RAX
	
	push rax
	push rcx
	push rdi

	; 1. Calculate the address to output a character: addres_offset = (x_y_pos.Y_Pos * x_y_pos.Screen_width + x_y_pos.X_Pos) * 4 (4 bytes for 1 symbol)
	; 1.1 Calculating x_y_pos.Y * x_y_pos.Screen_Width
	mov rax, rdx
	shr rax, 16 ; AX = x_y_pos.Y_Pos
	movzx rax, ax ; RAX = AX = x_y_pos.Y_Pos


	mov rbx, rdx
	shr rbx, 32 ; BX = x_y_pos.Screen_width
	movzx rbx, bx ; RBX = BX = x_y_pos.Screen_width

	imul rax, rbx ; RAX = RAX * RBX = x_y_pos.Y_Pos * x_y_pos.Screen_Width

	; 1.2 Add x_y_pos.X_Pos to RAX
	movzx rbx, dx ; RBX = DX = x_y_pos.X_Pos
	add rax, rbx ; RAX = x_y_pos.Y_Pos * x_y_pos.Screen_Width + x_y_pos.X_Pos = offset in symbols. 
	
	; 1.3 We still need offset in bytes. Every symbol is 4 bytes so we have to multiply by 4
	shl rax, 2 ; RAX = RAX * 4 = addres_offset

	mov rdi, rcx ; RDI = screen_buffer
	add rdi, rax ; RDI = screen_buffer + addres_offset

	; 2. Show symbols
	mov eax, r9d
	mov rcx, r8

	rep stosd

	pop rdi
	pop rcx
	pop rax

	ret

Draw_Line_Horizontal endp
;------------------------------------------------------------------------------------------------------------
end