.286
jumps

.model tiny



.code

org 100h
Start:

jmp Begin

NewLine proc
				mov word ptr [Arg1], offset NewLineString
				call PrintLine
				ret
endp

FindDigit proc
				
										
				push bx
				push cx
				push dx
				mov  dx, word ptr [Arg1] ; char must be in dl	
				mov  cx, 0000h
				mov  bx, offset Digits
FindDigitLoop:
				cmp dl, byte ptr [bx] 
				je FindDigitFound
				cmp byte ptr [bx], '$'
				je FindDigitNo
				inc bx
				jmp FindDigitLoop

FindDigitFound:
				sub bx, offset Digits
				mov word ptr [Arg1], bx 
				
				pop dx
				pop cx
				pop bx
				ret
FindDigitNo:
				mov bh, 11h
				mov dx, word ptr [Arg1]
				
				pop dx
				pop cx
				pop bx
				ret
endp

PrintLine proc
				push ax
				push bx
				mov  bx, word ptr [Arg1]
				mov  ah, 0eh
PrintChar:
				mov al, byte ptr [bx]
				cmp al, '$'
				je BreakPrint
	
				inc bx
				int 10h
				jmp PrintChar
		
BreakPrint:
				pop bx
				pop ax
				ret
endp


Begin:
				mov word ptr [Arg1], offset InviteOne
				
				call PrintLine

				mov ah, 01h
				int 21h
				mov byte ptr InpType, al
				call NewLine
				

				mov cx, 0000h
				mov dx, 0000h
					
				cmp byte ptr InpType, 'b'
				je InputBin
				cmp byte ptr InpType, 'B'
				je InputBin

				cmp byte ptr InpType, 'd'
				je InputDec
				cmp byte ptr InpType, 'D'
				je InputDec

				cmp byte ptr InpType, 'h'
				je InputHex
				cmp byte ptr InpType, 'H'
				je InputHex

				mov bx, offset ErrorInvalidType	
				mov word ptr [Arg1], bx							
				call PrintLine
				jmp Stop
InputBin:
				mov word ptr [Arg1], offset OkWriteDown
				call PrintLine
InputBinLoop:
				;mov word ptr [Arg1], offset BinChosen
				;call PrintLine
				
				mov ah, 01h
				int 21h
				cmp al, 13d
				je ConvertNum
				
				cmp cx, BinByteDigs
				
				jae ErrorWrongSize
				inc cx
				
				mov word ptr [Arg1], ax
				call FindDigit
				mov ax, word ptr [Arg1]
				
				cmp ah, 0d
				jne PrintErrorBadChar
				cmp al, 1d
				ja  PrintErrorBadChar
				
				rol dl, 1h
				add dl, al
				jmp InputBinLoop

InputHex:
				mov word ptr [Arg1], offset OkWriteDown
				call PrintLine
InputHexLoop:
				;mov word ptr [Arg1], offset HexChosen
				;call PrintLine
				
				mov ah, 01h
				int 21h
				cmp al, 13d
				je ConvertNum
				
				cmp cx, HexByteDigs
				
				jae ErrorWrongSize
				inc cx
				
				mov word ptr [Arg1], ax
				call FindDigit
				mov ax, word ptr [Arg1]
				
				cmp ah, 0d
				jne PrintErrorBadChar
				cmp al, 15d
				ja  PrintErrorBadChar
				
				rol dl, 4h
				add dl, al
				jmp InputHexLoop
	
InputDec:
				mov word ptr [Arg1], offset OkWriteDown
				call PrintLine
InputDecLoop:
				
				mov  ah, 01h
				int  21h
				cmp  al, 13d
				je   ConvertNum
				
				cmp  cx, 4d
				je   ErrorWrongSize
				
				inc  cx
				
				push cx
				mov  word ptr [Arg1], ax
				call FindDigit
				mov  ax, word ptr [Arg1]
				pop  cx
				
				cmp  ah, 0d
				jne  PrintErrorBadChar
				cmp  al, 0fh
				ja   PrintErrorBadChar
				
				push ax
				mov  ax, dx
				mov  cx, 10d 
				mul  cx
				mov  dx, ax
				pop  ax

				add dl, al
				jmp InputDecLoop

ConvertNum:

				mov  ah, 0eh
				mov  bx, offset InviteTwo
				mov word ptr [Arg1], bx

				call PrintLine

				mov ah, 01h
				int 21h
				mov byte ptr InpType, al
					
				cmp byte ptr InpType, 'b'
				je BinOutput
				cmp byte ptr InpType, 'B'
				je BinOutput

				cmp byte ptr InpType, 'd'
				je DecOutput
				cmp byte ptr InpType, 'D'
				je DecOutput

				cmp byte ptr InpType, 'h'
				je HexOutput
				cmp byte ptr InpType, 'H'
				je HexOutput

				mov bx, offset ErrorInvalidType	
				mov word ptr [Arg1], bx							
				call PrintLine
				jmp Stop


BinOutput:
				mov cl, byte ptr BinByteDigs
				mov ah ,0eh
				call NewLine
BinOut:
				mov bl, byte ptr BinDigit
				mov bh, 00h

				rol dl, 1						; byte ptr BinBitsDigit
				and bl, dl
				add bx, offset Digits
				mov al, [bx]
				int 10h
				dec cl;
				cmp cl, 00h
				je BinBreak
				
				jmp BinOut
BinBreak:
				mov al, 'b'
				int 10h
				mov al, 0dh				; space
				int 10h
				mov al, 0ah
				int 10h
				jmp Stop


HexOutput:
				mov cl, byte ptr HexByteDigs
				mov ah ,0eh
				call NewLine
HexOut:
				mov bl, byte ptr HexDigit
				mov bh, 00h
				
				rol dl, 4				; HexBitsDigit
				and bl, dl
				add bx, offset Digits
				mov al, [bx]
				int 10h
				dec cl
				cmp cl, 00h
				je HexBreak
				jmp HexOut
HexBreak:
				mov al, 'h'
				int 10h
				mov al, 0dh				; space
				int 10h
				mov al, 0ah
				int 10h
				jmp Stop
				
										; generating decimal numbers in stack

DecOutput:
				mov al, dl				
				mov ah, 00h
				mov cl, 0				; digits counter
				mov bh, 10d				; argument of DIV
				call NewLine
NextDigit:
				div bh
				mov dx, ax

				and dx, 0ff00h
				mov dl, dh
				mov dh, 00h
				push dx
				
				and ax, 00ffh

				inc  cl
				cmp al, 0
				je PrintDec
				jmp NextDigit
	
PrintDec:
				dec cl
				pop bx
				add bx, offset Digits
				mov al, [bx]
				mov ah, 0eh
				int 10h
				cmp cl, 0
				je Stop
				jmp PrintDec

ErrorBadChar:

				mov bx, offset ErrorInvalidChar			; Printing error message
				mov ah, 0eh

PrintErrorBadChar:
				mov al, byte ptr [bx]
				cmp al, '$'
				je Stop
				
				inc bx
				int 10h
				jmp PrintErrorBadChar

ErrorWrongSize:
				mov bx, offset ErrorInvalidSize			; Printing error message
				mov ah, 0eh

PrintErrorBadSize:
				mov al, byte ptr [bx]
				cmp al, '$'
				je Stop
				
				inc bx
				int 10h
				jmp PrintErrorBadSize


				jmp Stop

Stop:	
				mov ax, 4c00h
				int 21h
				
InviteOne: 			db 'Please, type B, D or H to input a number', 0dh, 0ah, '$'
InviteTwo: 			db 'OK, Please type B, D or H of destination format', 0dh, 0ah, '$'
OkWriteDown:		db 'OK, Write number down', 0dh, 0ah, '$'
ErrorInvalidType: 	db 0dh, 0ah, 'ERROR: Invalid input type', 0dh, 0ah, '$'
ErrorInvalidChar: 	db 0dh, 0ah, 'ERROR: Invalid character found.', 0dh, 0ah, '$'
ErrorInvalidSize: 	db 0dh, 0ah, 'ERROR: Size is too long.', 0dh, 0ah, '$'
BinChosen:			db 'Binary chosen', 0dh, 0ah, '$'
DecChosen:			db 'Decimal chosen', 0dh, 0ah, '$'
HexChosen:			db 'Hex chosen', 0dh, 0ah, '$'
InpType: 			db '0'
OutType: 			db '0'
Digits: 			db '0123456789abcdef$'
NewLineString:		db 0dh, 0ah, '$'

Arg1:				dw 0000h

BinByteDigs			= 08h				; quantity of digits in binary number
HexByteDigs 		= 02h				; in hex number

BinBitsDigit		= 01h				; bits of information per digit
HexBitsDigit		= 04h				;

BinDigit			= 00000001b		; mask for digit separation 
HexDigit			= 00001111b


				
end		Start

