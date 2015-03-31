;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; Tiny printf on MASM32. 
;
; Copyright (c) Ivanychev Sergey, MIPT, 2014
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

.586

.model flat, stdcall
option casemap:none

include 	windows.inc
include 	kernel32.inc
include 	masm32.inc
include 	msvcrt.inc
include 	shell32.inc
includelib 	masm32.lib
includelib 	kernel32.lib
includelib 	msvcrt.lib

;m_memcmp	PROTO C  : DWORD, :DWORD
printf		PROTO C	 : VARARG
iv_putchar	PROTO C  handle:  dword, chr : dword
iv_strlen	PROTO C  str_ptr: dword
iv_puts		PROTO C  handle:  dword, str_ptr: dword
getchar		PROTO C
put_buffer	PROTO C char: dword

u_bin_print	PROTO C	 num : dword
u_hex_print	PROTO C	 num : dword
u_dec_print	PROTO C  num : dword

buffer_puts PROTO C strptr: dword
tiny_printf PROTO C  args: VARARG


check_overflow PROTO


.data
				Str1			BYTE 		"0001", 0
				Str2			BYTE 		"00000000002", 0
				Out_str			BYTE 		"%x", 13d, 10d,0
				m_putchar_char	BYTE 		4 dup(0d)
				
				numbers			BYTE		"0123456789ABCDEF", 0
check_overflow_error_message 	BYTE		"Buffer overflowed. Terminating", 0

				buffer 			byte 		257 dup(0)
				buffer_seek 	dword  		0h 
				BUFFER_LEN		dword		256d
				
				num_chars_wrtn	dword 		0h
				
				IHANDLE			dword 		0
				OHANDLE			dword 		0
				
				Invalid_spec	db 			"[Invalid specificator after %. Terminating...]", 0
				
				printf_test		byte 		"%c %d %x %b", 13, 10, "is %% a %s number", "%c %d %x %b", 13, 10, "is %% a %s number", 0
				huge			byte		"huge", 0
				hugehuge		byte		"%s %s", 0
.CODE

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	m_console_alloc				macros, that allocates console
;	Return:						EAX - Input Handle, EBX - Output Handle
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

m_console_alloc	macro
	
				invoke AllocConsole
				
				invoke	GetStdHandle, STD_OUTPUT_HANDLE
				mov dword ptr OHANDLE, eax
				invoke  GetStdHandle, STD_INPUT_HANDLE
				mov dword ptr IHANDLE, eax
				
				endm
				
				
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;
; burn_rubbish	macros sets standard registers values 0
; Destroy:		eax, ebx, ecx, edx, edi, esi
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


burn_rubbish	macro
				
				xor eax, eax
				xor ebx, ebx
				xor ecx, ecx
				xor edx, edx
				xor edi, edi
				xor esi, esi
				
				endm
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	clear_buffer		macros clears the defined buffer of printf
;	
;	Destroy				nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

clear_buffer	macro
	
				push ecx
				push eax
				push edi
				
				mov  eax, 0d
				mov  ecx, dword ptr BUFFER_LEN
				mov  edi, offset buffer
				
				rep stosb
				
				mov dword ptr buffer_seek, 0d
				
				pop edi
				pop eax
				pop ecx
endm

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;>>>>>>>>>>>>>>>>>>>>>>>STARTING  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Start:
				burn_rubbish
				clear_buffer
				m_console_alloc
				xor eax, eax
				mov al, 50d
				
				;invoke u_bin_print, 50
				;invoke iv_putchar,  OHANDLE, ' '
				;invoke u_hex_print, 50
				;invoke iv_putchar, OHANDLE, ' '
				;invoke u_dec_print, 50
				;invoke buffer_puts, addr Str1
				;invoke iv_puts, dword ptr OHANDLE,  addr buffer
				
				invoke tiny_printf,					
					addr printf_test,
					50,
					50,
					50,
					50,
					addr huge,
					50,
					50,
					50,
					50,
					addr huge
				
				invoke getchar
				invoke ExitProcess, 0
				
				



				
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; 	iv_putchar				prints character in input console, which is located in the 
;							first byte on input double word
;
;	Args:					ConsoleHandle, character
;	Destroy:				Nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

iv_putchar		proc C	handle: dword, chr : dword
				
				push 	eax
				mov 	eax, dword ptr chr
				mov 	byte ptr m_putchar_char, al
				pop 	eax
				
				invoke WriteConsole,
					handle,
					addr m_putchar_char,
					1,
					addr num_chars_wrtn,
					NULL
						

				pop eax
				ret				
iv_putchar		endp




;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	iv_puts					prints string to the console	
;
;	Args:					ConsoleHandle, String pointer
;	Output:					EAX amount of chars written
;	Destoy:					Nothing			
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

iv_puts			proc C handle: dword, str_ptr: dword
	
				invoke iv_strlen, dword ptr str_ptr
				
				invoke WriteConsole,
					handle,
					str_ptr,				
					eax,
					addr num_chars_wrtn,
					NULL
				
				ret

iv_puts			endp


;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; iv_strlen	returns length of input string
; Input: 	string pointer in program memory segment
; Output:	EAX to save length
; Destoy:	Nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


iv_strlen		proc C str_ptr: dword
				
				push edi
				push ebx
				
				mov edi, dword ptr str_ptr
				
				cmp edi, 0d
				je strlen_stop
	
				mov ebx, edi
				xor eax, eax
				
				mov ecx, 0ffffffffh
				repne scasb
				
				sub edi, ebx
				mov eax, edi
				sub eax, 1
				
				
strlen_stop:
				pop ebx
				pop edi
				
				ret
iv_strlen		endp


;>>>>>>>>>>>>>>>>>>>>>> NUMBER OUTPUT >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	Printf uses buffer to locate there string that will pe printed						>
; 	at the end it its work. The main reason for that is that we don't 					>
;	exactly know the size of string that will be printed. So we need					>
;	to save it in buffer, use the STRLEN and print it out using PUTS					>
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	Check_overflow			A tiny verification of prepared buffer overflow. It checkes
;							whether the last character is zero or not. If negative - error
;
;	Destroy:				Nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

check_overflow	proc
				
				push ebx
				push eax
				mov  ebx, dword ptr BUFFER_LEN
				add  ebx, offset buffer
				
				mov  al,  byte  ptr [ebx]
				and  al, al
				jz check_overflow_continue
				pop  eax
				pop  ebx
				invoke iv_puts, OHANDLE, addr check_overflow_error_message
				invoke getchar
				invoke ExitProcess, 0
check_overflow_continue:
				pop  eax
				pop  ebx
				
				ret
check_overflow	endp


;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; 	u_bin_print		
; 	u_hex_print		print unsigned dword number to buffer
;
; 	Input:			number to print
; 	Destroy:		Nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
u_out			macro radix
				
				pusha
				
				mov eax, num
				if 		radix eq 2
					mov ecx, 32d
				elseif 	radix eq 16
					mov ecx, 8d
				endif
				
				if 		radix eq 2
					mov edx, 00000001h
				elseif	radix eq 16
					mov edx, 0000000fh
				endif
				mov edi, offset buffer
				add edi, dword ptr buffer_seek
@@:
				mov ebx, edx
				
				if 		radix eq 2
					rol eax, 1d
				elseif	radix eq 16
					rol eax, 4d
				endif
				
				and ebx, eax
				add ebx, offset numbers
				mov esi, ebx
				
				movsb
				
				loop @b
				
				if 		radix eq 2
					mov byte ptr [edi], 'b'
				elseif	radix eq 16
					mov byte ptr [edi], 'h'
				endif
				
				inc edi
				
				sub edi, offset buffer
				mov dword ptr buffer_seek, edi
				
				popa
				
				
endm

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

u_bin_print		proc C num : dword
				
				u_out 2
				call check_overflow
				ret
u_bin_print		endp

u_hex_print		proc C num : dword
	
				u_out 16
				call check_overflow
				ret
u_hex_print endp


;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	u_dec_print		prints unsigned word number to buffer
;
; 	Input:			number to print
; 	Destroy:			Nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

u_dec_print		proc C num: dword
				
				pusha
				mov eax, num
								
				mov ecx, 0				; digits counter
				mov ebx, 10d			; argument of DIV
				mov edi, offset buffer
				add edi, dword ptr buffer_seek
				
dec_print_new_digit:
				mov edx, 0h
				div ebx

				push edx

				inc ecx
				cmp eax, 0
				je PrintDec
				jmp dec_print_new_digit
	
PrintDec:
				pop esi
				add esi, offset numbers
				
				movsb
				
				loop PrintDec
dec_print_stop:
				sub edi, offset buffer
				mov dword ptr buffer_seek, edi
				
				popa
				ret
u_dec_print		endp

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	buffer_puts		prints argumented string to buffer
;
;	Input			string pointer
;	Destroy			Nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


buffer_puts		proc C strptr: dword
				
				push ecx
				push esi
				push edi
				
				mov ecx, 0ffffffffh
				
				mov esi, dword ptr strptr
				
				mov edi, offset buffer
				add edi, dword ptr buffer_seek
				
buffer_puts_copy:
				mov al, byte ptr [esi]
				and al, al
				jz buffer_puts_break_copy
				movsb
				
				jmp buffer_puts_copy
				
buffer_puts_break_copy:
				
				sub edi, offset buffer
				mov dword ptr buffer_seek, edi
				
				invoke check_overflow
				
				pop edi
				pop esi
				pop ecx
				
				ret

buffer_puts endp				

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	put_buffer		puts character to buffer
;
;	Input			dword with ascii number of character in the last byte
;	Destroy			Nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

put_buffer		proc C char: dword
				push eax
				push edi
				
				mov edi, offset buffer
				add edi, dword ptr buffer_seek
				mov eax, dword ptr char
				
				stosb
				
				sub edi, offset buffer
				mov dword ptr buffer_seek, edi
				
				pop edi
				pop eax
				
				ret
put_buffer		endp

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	tiny_printf		That function is quite different from the same in DOS. We don't know
;					exactly, how many symbols will be in the output string, so we need
;					to figure out, how to count it. If we counted, we wouldn't call 
;					ConsoleOutput every time we want to print character. Creating buffer
;					is in my oppinion the best way to deal with printf
;
;	Input			formatted string pointer and other variables
;	Destroy			Nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


tiny_printf		proc C args: vararg
				
				pusha
				cld
				mov esi, [ebp+8]
				mov ebx, ebp
				add ebx, 12d
				mov ecx, 0d
				
				cmp esi, 0h
				je printf_exit
				
printf_outchar:
				mov dl, byte ptr [esi]
				inc esi
				
				cmp dl, '%'
				jne printf_skip_spec
				
				mov dl, byte ptr [esi]
				inc esi
				
				cmp dl, 'b'
				je printf_printf_binary
				cmp dl, 'd'
				je printf_printf_decimal
				cmp dl, 'x'
				je printf_printf_hex
				cmp dl, '%'
				je printf_printf_percent
				cmp dl, 'c'
				je printf_printf_char
				cmp dl, 's'
				je printf_printf_string
				
				jmp printf_inval_spec

printf_printf_binary:
				
				mov eax, dword ptr [ebx]
				push ebx
				
				invoke u_bin_print, eax
				
				pop ebx
				
				add ebx, 4
				
				jmp printf_outchar
				
printf_printf_decimal:
				
				mov eax, dword ptr [ebx]
				push ebx
				
				invoke u_dec_print, eax
				
				pop ebx
				
				add ebx, 4
				
				jmp printf_outchar
printf_printf_hex:
				
				mov eax, dword ptr [ebx]
				push ebx
				
				invoke u_hex_print, eax
				
				pop ebx
				
				add ebx, 4
				
				jmp printf_outchar
printf_printf_char:
				mov eax, dword ptr [ebx]
				add ebx, 4
				push ebx
				
				invoke put_buffer, eax
				
				pop ebx
				jmp printf_outchar
printf_printf_percent:
				push ebx
				invoke put_buffer, '%'
				pop ebx
				
				jmp printf_outchar
printf_printf_string:
				mov eax, dword ptr [ebx]
				add ebx, 4
				push ebx
				
				invoke buffer_puts, eax
				pop ebx
				
				jmp printf_outchar
printf_inval_spec:
				invoke iv_puts, dword ptr OHANDLE,  addr Invalid_spec
				jmp printf_exit
printf_skip_spec:
				
				push ebx
				push edx
				invoke put_buffer, edx
				pop edx
				pop ebx
				
				cmp dl, 0
				je  printf_exit
				
				jmp printf_outchar
printf_exit:
				mov ecx, dword ptr buffer_seek
				
				invoke iv_puts, OHANDLE, addr buffer
				clear_buffer
				
				popa
				ret
				
tiny_printf 	endp


end				Start

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><
