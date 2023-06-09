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
Get_Pos_Address proc
; Parameters:
; RCX = screen_buffer
; RDX = x_y_pos
; Return RDI

	; 1. Calculate the address to output a character: address_offset = (x_y_pos.Y_Pos * x_y_pos.Screen_width + x_y_pos.X_Pos) * 4 (4 bytes for 1 symbol)
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
	shl rax, 2 ; RAX = RAX * 4 = address_offset

	mov rdi, rcx ; RDI = screen_buffer
	add rdi, rax ; RDI = screen_buffer + address_offset

	ret

Get_Pos_Address endp
;------------------------------------------------------------------------------------------------------------
Draw_Start_Symbol proc
;Output the start symbol
; Parameters:
; RDI = current address in screen_buffer
; R8 = symbol
; Return NONE

	push rax
	push rbx

	mov eax, r8d
	mov rbx, r8
	shr rbx, 32	; RBX = EBX = (symbol.Start_Symbol, symbol.End_Symbol)
	mov ax, bx ; EAX = (symbol.Attributes, symbol.Start_Symbol)

	stosd

	pop rbx
	pop rax

	ret

Draw_Start_Symbol endp
;------------------------------------------------------------------------------------------------------------
Draw_End_Symbol proc
;Output the last symbol
; Parameters:
; EAX = symbol.Attributes, symbol.Main_Symbol
; RDI = current address in screen_buffer
; R8 = symbol
; Return NONE

	mov rbx, r8
	shr rbx, 48	; RBX = BX = symbol.End_Symbol
	mov ax, bx ; EAX = (symbol.Attributes, symbol.End_Symbol)

	stosd

	ret

Draw_End_Symbol endp
;------------------------------------------------------------------------------------------------------------
Draw_Line_Horizontal proc
; extern "C" void Draw_Line_Horizontal (CHAR_INFO* screen_buffer, X_Y_Pos x_y_pos, ASymbol symbol);
; Parameters:
; RCX = screen_buffer
; RDX = x_y_pos
; R8 = symbol
; Return NONE
	
	push rax
	push rbx
	push rcx
	push rdi

	; 1. Calculate the address to output a character
	call Get_Pos_Address ; RDI = position of a symbol in buffer screen_buffer in x_y_pos

	; 2. Output the start symbol
	call Draw_Start_Symbol

	; 3. Show symbol.Main_Symbol
	mov eax, r8d
	mov rcx, rdx
	shr rcx, 48 ; RCX = CX = x_y_pos.Length
	
	rep stosd

	; 4. Output the last symbol 
	call Draw_End_Symbol

	pop rdi
	pop rcx
	pop rbx
	pop rax

	ret

Draw_Line_Horizontal endp
;------------------------------------------------------------------------------------------------------------
Draw_Line_Vertical proc
;extern "C" void Draw_Line_Vertical(CHAR_INFO * screen_buffer, X_Y_Pos x_y_pos, ASymbol symbol);
; Parameters:
; RCX = screen_buffer
; RDX = x_y_pos
; R8 = symbol
; Return NONE

	push rax
	push rcx
	push rdi
	push r11

	; 1. Calculate the address to output a character
	call Get_Pos_Address ; RDI = position of a symbol in buffer screen_buffer in x_y_pos

	; 2. Output position correction calculation
	mov r11, rdx
	shr r11, 32 ; R11 = x_y_pos
	movzx r11, r11w ; R11 = R11w = x_y_pos.Screen_Width
	dec r11
	shl r11, 2 ; R11 = x_y_pos.Screen_Width * 4 = Screen Width in bytes

	; 3. Output the first symbol
	call Draw_Start_Symbol

	add rdi, r11

	; 4. Prepare the cycle counter
	mov rcx, rdx
	shr rcx, 48 ; RCX = CX = x_y_pos.Length

	mov eax, r8d ; EAX = symbol

_1:
	stosd ; Displaying a symbol
	add rdi, r11

	loop _1

	; 5. Output the last symbol
	call Draw_End_Symbol

	pop r11
	pop rdi
	pop rcx
	pop rax

	ret

Draw_Line_Vertical endp
;------------------------------------------------------------------------------------------------------------
Show_Colors proc
; extern "C" void Show_Colors(CHAR_INFO * screen_buffer, X_Y_Pos x_y_pos, CHAR_INFO symbol);
; Parameters:
; RCX = screen_buffer
; RDX = x_y_pos
; R8 = symbol
; Return NONE

	push rax
	push rbx
	push rcx
	push rdi
	push r10
	push r11

	; 1. Calculate the address to output a character
	call Get_Pos_Address ; RDI = position of a symbol in buffer screen_buffer in x_y_pos

	mov r10, rdi

	; 2. Output position correction calculation
	mov r11, rdx
	shr r11, 32 ; R11 = x_y_pos
	movzx r11, r11w ; R11 = R11w = x_y_pos.Screen_Width
	shl r11, 2 ; R11 = x_y_pos.Screen_Width * 4 = Screen Width in bytes

	; 3. Preparing cycles
	mov rax, r8 ; RAX = EAX = symbol

	; 3.1 Logical AND result
	; 0 & 0 = 0
	; 0 & 1 = 0
	; 1 & 0 = 0
	; 1 & 1 = 1

	and rax, 0ffffh ; set first 2 bytes of RAX to 1111 1111 and rest is zeroed
	mov rbx, 16

	xor rcx, rcx ; RCX = 0

	; 3.1 XOR result
	; 0 XOR 0 = 0
	; 0 XOR 1 = 1
	; 1 XOR 0 = 1
	; 1 XOR 1 = 0

_0:
	mov cl, 16

_1:
	stosd
	add rax, 010000h ; A binary unit shifted 16 bits to the left.

	loop _1

	add r10, r11
	mov rdi, r10

	dec rbx
	jnz _0

	pop r11
	pop r10
	pop rdi
	pop rcx
	pop rbx
	pop rax

	ret

Show_Colors endp
;------------------------------------------------------------------------------------------------------------
Clear_Area proc
; extern "C" void Clear_Area(CHAR_INFO* screen_buffer, SArea_Pos area_pos, ASymbol symbol);
; Parameters:
; RCX = screen_buffer
; RDX = area_pos
; R8 = symbol
; Return NONE

	push rax
	push rbx
	push rcx
	push rdi
	push r10
	push r11

	; 1. Calculate the address to output a character
	call Get_Pos_Address ; RDI = position of a symbol in buffer screen_buffer in x_y_pos

	mov r10, rdi

	; 2. Output position correction calculation
	mov r11, rdx
	shr r11, 32 ; R11 = x_y_pos
	movzx r11, r11w ; R11 = R11w = x_y_pos.Screen_Width
	shl r11, 2 ; R11 = x_y_pos.Screen_Width * 4 = Screen Width in bytes

	; 3. Preparing cycles
	mov rax, r8 ; RAX = EAX = symbol


	mov rbx, rdx
	shr rbx, 48 ; BH = area_pos.Height, BL = area_pos.Width

	xor rcx, rcx ; RCX = 0

_0:
	mov cl, bl
	rep stosd

	add r10, r11
	mov rdi, r10

	dec bh
	jnz _0

	pop r11
	pop r10
	pop rdi
	pop rcx
	pop rbx
	pop rax

	ret

Clear_Area endp
;------------------------------------------------------------------------------------------------------------
Draw_Text proc
; extern "C" unsigned char Draw_Text(CHAR_INFO* screen_buffer, X_Y_Text_Pos position, const wchar_t* string);
; Parameters:
; RCX = screen_buffer
; RDX = position
; R8 = string
; Return: RAX = string length

	push rbx
	push rdi
	push r8

	; 1. Calculate the address to output a character
	call Get_Pos_Address ; RDI = position of a symbol in buffer screen_buffer in x_y_pos

	mov rax, rdx
	shr rax, 32 ; EAX = position.Attributes

	xor rbx, rbx ; RBX = 0

_1:
	mov ax, [r8] ; AL = next symbol of the string

	cmp ax, 0
	je _exit

	add r8, 2 ; incrementing the pointer to the enxt symbol in the string

	stosd
	inc rbx
	jmp _1

_exit:
	mov rax, rbx

	pop r8
	pop rdi
	pop rbx

	ret

Draw_Text endp
;------------------------------------------------------------------------------------------------------------
Draw_Limited_Text proc
; extern "C" void Draw_Limited_Text(CHAR_INFO * screen_buffer, X_Y_Text_Pos position, const wchar_t* string, unsigned short limit);
; Parameters:
; RCX = screen_buffer
; RDX = position
; R8 = string
; R9 = limit
; Return: RAX = string length

	push rax
	push rcx
	push rdi
	push r8
	push r9

	; 1. Calculate the address to output a character
	call Get_Pos_Address ; RDI = position of a symbol in buffer screen_buffer in x_y_pos

	mov rax, rdx
	shr rax, 32 ; EAX = position.Attributes

_1:
	mov ax, [r8] ; AL = next symbol of the string

	cmp ax, 0
	je _fill_the_string_with_spaces

	add r8, 2 ; incrementing the pointer to the enxt symbol in the string

	stosd
	
	dec r9
	cmp r9, 0
	je _exit ; Stop output when end of line is reached

	jmp _1

_fill_the_string_with_spaces:
	mov ax, 020h ; code for " " symbol
	mov rcx, r9 ; spaces to fill

	rep stosd

_exit:
	pop r9
	pop r8
	pop rdi
	pop rcx
	pop rax

	ret

Draw_Limited_Text endp
;------------------------------------------------------------------------------------------------------------
Test_Command proc

	ret

Test_Command endp
;------------------------------------------------------------------------------------------------------------
end