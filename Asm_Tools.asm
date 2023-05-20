.code
;------------------------------------------------------------------------------------------------------------
Make_Sum proc
; extern "C" int Make_Sum(int value_1, int value_2)
; RCX = value_1
; RDX = value_2
; Return RAX

	mov eax, ecx
	add eax, edx

	ret

Make_Sum endp
;------------------------------------------------------------------------------------------------------------
Draw_Line proc
;extern "C" void Draw_Line(int* screen_buffer, int x_pos, int y_pos, int length, wchar_t symbol, short attribute);

	ret

Draw_Line endp
;------------------------------------------------------------------------------------------------------------
end