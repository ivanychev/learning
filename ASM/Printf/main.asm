;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; This file contain string, numeric and memory functions and testing code in 
; the main part.													
;
; Video output might be found in the another commit on code.google.com
; 
; TODO: -- Find out about stack levelling back (now stack isn't cleaned after
;		   pushing arguments TOFIX) 
;		-- Source code dividing (not done for simplicity of checking)
;
; - memcmp
; - memset
; - strlen
; - strcmp
; - dos_puts
; - u_bin_print
; - u_hex_print
; - u_dec_print
;
; Developed by Ivanychev Sergey. DCAM MIPT, group 376
; sergeyivanychev@gmail.com
;
; Update 1: - added support for stosb, lodsb
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

.286
.model			tiny

.code

jumps

				org 100h
Start:

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; burn_rubbish	macros sets standard registers values 0
; Destroy:		ax, bx, cx, dx
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

burn_rubbish	macro
				
				xor ax, ax
				xor bx, bx
				xor cx, cx
				xor dx, dx
				xor di, di
				xor si, si
				
				endm
				
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; new_line		prints \n using DOS interruption
; Destroy:		nothing
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

new_line		macro
				push ax
				push dx
				mov ah, 02h
				mov dl, 0ah
				int 21h
				mov dl, 0dh
				int 21h
				pop dx
				pop ax
				endm	

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;=============================================================================
				
				burn_rubbish
				
				jmp main_test_printf
;				
;				mov ax, 7
;				mov bx, 6
;				cmp ax, bx
;				
;				push offset Msg
;				call strlen
;				pop cx
;				;xor cx, cx
;				
;				push ax							; testing numbers printing and strlen
;				call u_bin_print
;				call u_hex_print
;				call u_dec_print
;				pop cx
;				;xor cx, cx
;				
;				push offset Destination			; testing strcpy
;				push offset Copied
;				call strcpy
;				pop cx
;				pop cx
;				xor cx, cx
;				push offset Destination
;				new_line
;				call dos_puts
;				pop cx
;				;xor cx, cx
;				
;				new_line
;
;
;				push 5d							; testing memset
;				push 48d
;				push offset Memset_field
;				
;				call memset
;				pop cx
;				pop cx
;				pop cx
;				;xor cx, cx
;				
;				push offset Memset_field
;				call dos_puts
;				pop cx
;				;xor cx, cx
;				
;				
;				push 3d
;				push offset Comp2
;				push offset Comp1
;				call memcmp
;				pop cx
;				pop cx
;				pop cx
;				;xor cx, cx
;				
;				push ax
;				call u_bin_print
;				pop cx
;				;xor cx, cx
;				
;				push 4d
;				push offset Comp2
;				push offset Comp1
;				call memcmp
;				pop cx
;				pop cx
;				pop cx
;				;xor cx, cx
;				
;				push ax
;				call u_bin_print
;				pop cx

main_test_printf:
				
				;'%d is %b and %x in other radiX. %d %%%c %s'
				
				mov ax, offset Destination
				push ax
				push '!';
				push 100d
				mov ax, 48d
				push ax
				push ax
				push ax
				
				mov ax, offset Printf_1
				push ax
				call tiny_printf
				
				add sp, 4d
				
				mov ax, 4c00h
				int 21h
;=============================================================================
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; memcmp		Compares first ARG3 bytes of ARG1, ARG2 blocks of memory
; Input:		First block pointer, second block pointer, quantity of bytes
; Output:		AX = 0 if equal, 0001h if above, 0ffffh if below
; Destroy		AX, DI, SI
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

memcmp			proc

				push bp
				mov bp, sp

				mov si, [bp+4]
				mov di, [bp+6]
				mov cx, [bp+8]
				
				repe cmpsb
;memcmp_process:
;				inc di
;				inc si
;				mov al, byte ptr [di]
;				cmp al, byte ptr [si]
;				
;				loopz memcmp_process
								
				jz memcmp_zero
				ja memcmp_above
				jmp memcmp_below
memcmp_zero:
				mov ax, 0h
				jmp memcmp_stop
memcmp_above:
				mov ax, 0001h
				jmp memcmp_stop
memcmp_below:
				mov ax, 0ffffh
				jmp memcmp_stop
memcmp_stop:
				pop bp
				ret
				endp
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; memset 		Sets first ARG1 elements of memory starting with ARG2 pointer
;				with ARG3 value, which is to be converted in unsigned char
; Input:		Pointer of beginning, value, quantity of bytes,
; Destroy:		CX, DX, DI
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

memset			proc
				
				push bp
				mov bp, sp
				
				mov di, [bp+4]					; pointer
				mov ax, [bp+6]					; value
				and ax, 00ffh
				mov cx, [bp+8]
				
				rep stosb
;memset_process:
;				mov byte ptr [di], dl
;				inc di
;				loop memset_process
				
				pop bp
				ret
				endp

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; strcpy		copies import string 
; Input:		copied string pointer, destination pointer
; Destroy:		AX, BX, CX, DI, SI
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
strcpy			proc

				push bp
				mov bp, sp
				
				mov ax, [bp+4]				; copied string
				mov bx, [bp+6]				; destination	
				
				mov di, bx
				mov si, ax
				
				mov al, 0d
				
				mov cx, 00h
strcopy_charcopy:
				mov cl, ds:[si]
				inc cl
				movsb
				loop strcopy_charcopy
				
				pop bp
				ret
				endp
				
				
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; strlen	returns length of input string
; Input: 	string pointer in program memory segment
; Output:	BX to save length
; Destoy:	bx, di, ax
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
strlen			proc
				
				push bp
				mov bp, sp
				
				mov di, [bp+4] ;mov bx, [bp+4]
				
				cmp bx, 0d
				je strlen_stop
				
				;mov di, bx
				;sar bx, 4d
				
				;mov ax, ds
				;add bx, ax
				
				;mov es, bx
				;sal di, 12d
				;ror di, 12d
				
				mov bx, di
				mov ah, 0h
				mov al, 0h
				
				mov cx, 0ffffh
				repne scasb
				
				sub di, bx
				mov ax, di
				sub ax, 1
				
				
strlen_stop:
				pop bp
				ret
				endp

				
				
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; u_bin_print		prints unsigned word number 
; Input:			number to print
; Destroy:			ax, bx, cx, dx	
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
u_bin_print		proc

				push bp
				mov bp, sp
				
				mov dx, [bp+4]
				mov cl, 16d
				mov ch, 00h
				
				mov ah ,02h
bin_print_out:
				mov bx, 0001h

				rol dx, 1						
				and bx, dx
				add bx, offset Digits
				
				push dx
				mov dl, [bx]
				int 21h
				pop dx
				
			
				loop bin_print_out
bin_print_break:
				mov dl, 'b'
				int 21h

				pop bp
				ret
				endp

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; u_hex_print		prints unsigned word number 
; Input:				number to print
; Destroy:			ax, bx, cx, dx	
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

u_hex_print		proc

				push bp
				mov bp, sp
				
				mov dx, [bp+4]
				mov cl, 4d
				mov ch, 00h
				
				mov ah ,02h
hex_print_out:
				mov bx, 0fh

				rol dx, 4						
				and bx, dx
				add bx, offset Digits
				
				push dx
				mov dl, [bx]
				int 21h
				pop dx
				

				loop hex_print_out
hex_print_break:
				mov dl, 'h'
				int 21h

				pop bp
				ret
				endp
				
										; generating decimal numbers in stack

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; u_dec_print		prints unsigned word number 
; Input:				number to print
; Destroy:			ax, bx, cx, dx	
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

u_dec_print		proc
				
				xor dx, dx
				push bp
				mov bp, sp
				
				mov ax, [bp+4]
								
				mov cx, 0				; digits counter
				mov bx, 10d				; argument of DIV
dec_print_new_digit:
				mov dx, 00h
				div bx
				
				push dx

				inc cx
				cmp ax, 0
				je PrintDec
				jmp dec_print_new_digit
	
PrintDec:
				pop bx
				add bx, offset Digits
				mov dl, [bx]
				mov ah, 02h
				int 21h
				cmp cx, 0
				loop PrintDec
dec_print_stop:
				pop bp
				ret
				endp
				
				
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; dos_puts	prints string to console
; Input: 		string pointer
; Destroy:		AX, BX
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

dos_puts  		proc

				push bp
				mov bp, sp
				
				mov bx, [bp+4]
				
				cmp bx, 0d
				je dos_printstr_stop
		
				mov  ah, 02h
				
dos_printstr_print_char:

				mov dl, byte ptr [bx]
				cmp dl, 0d
				je dos_printstr_stop
	
				inc bx
				int 21h
				jmp dos_printstr_print_char
		
dos_printstr_stop:
				pop bp
				ret
endp

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; putchar		prints input char
; Input			byte number
; Destroy		AX, DX
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

putchar			proc

				push bp
				mov bp, sp
				
				mov dx, [bp+4]
				mov ah, 02h
				
				int 21h
				
				pop bp
				ret
				
				endp

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; new_line		prints \n in the output
; Destroy:		AX
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

tiny_printf		proc

				push bp
				mov bp, sp
				
				xor cx, cx
				
				mov si, [bp+4]
				mov bx, bp
				add bx, 6d												; first additional argument, if exist
				
				cmp si, 0h
				je printf_exit

printf_outchar:
				mov cl, byte ptr [si]									; no lodsb, because the 0 value of CX used to exit the loop
				inc si
				
				cmp cl, '%'
				jne printf_skip_spec
				
				mov cl, byte ptr [si]									; no lodsb, because the 0 value of CX used to exit the loop
				inc si
				
				cmp cl, 'b'
				je printf_printf_binary
				cmp cl, 'd'
				je printf_printf_decimal
				cmp cl, 'x'
				je printf_printf_hex
				cmp cl, '%'
				je printf_printf_percent
				cmp cl, 'c'
				je printf_printf_char
				cmp cl, 's'
				je printf_printf_string
				
				jmp printf_inval_spec
				
printf_printf_binary:
				mov ax, [bx]
				push bx
				
				push ax
				call u_bin_print
				add sp, 2d
				
				pop bx
				
				add bx, 2
				
				jmp printf_outchar
printf_printf_decimal:
				
				mov ax, [bx]
				push bx
				
				push ax
				call u_dec_print
				add sp, 2d
				
				pop bx
				add bx, 2
				
				jmp printf_outchar
printf_printf_hex:
				mov ax, [bx]
				push bx
				
				push ax
				call u_hex_print
				add sp, 2d
				
				pop bx
				add bx, 2
				
				jmp printf_outchar
				
printf_printf_char:	
				mov ax, [bx]
				add bx, 2
				push ax
				
				call putchar
				add sp, 2d
				
				jmp printf_outchar
				
printf_printf_percent:
				push '%'
				
				call putchar
				add sp, 2d
				
				
				jmp printf_outchar
				
printf_printf_string:
				mov ax, [bx]
				add bx, 2
				
				push bx
				push ax
				call dos_puts
				add sp, 2d
				
				pop bx
				
				jmp printf_outchar
				
printf_inval_spec:
				
				mov ax, offset Invalid_spec
				call dos_puts
				add sp, 2d
				
				jmp printf_exit
				
				
printf_skip_spec:	
				push bx
				push cx
				call putchar
				add sp, 2d
				pop bx
				
				
				inc cx
				loop printf_outchar
				
printf_exit:
				pop bp
				ret
				
				endp
				



Printf_1		db '%d is %b and %x in other radiX. %d %%%c %s', 0;'%d is %b and %h in other radiX', 0
Msg:			db '123456789abcdef', 0
Copied:			db 'Hey, Jude', 0
Destination:	db 'Hell yeah', 0
Digits:			db '0123456789abcdef$'
Invalid_spec	db '[Invalid specificator after %. Terminating...]'
Memset_field	db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
Comp1			db 0,1,2,3
Comp2			db 0,1,2,4

end 			Start