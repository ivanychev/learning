.286
.model				tiny            


.code

				org 100h
Start:
				mov al, 05d
				mov ah, 05d
				mov bx, offset Msg
				call prstr_video


Exit:	
				mov ax, 4c00h
				int 21h

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; set_cursor - saves in DI the indent of requested cursor coordinates
;																	
; Entry: 	AL = X coordinate, AH = Y coordinate					
; Exit:  	DI = indent in video memory								
; Destroy:	BX														
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set_cursor			proc
				
				mov bx, ax
				xor ax, ax
				mov al, bh
				
				mov di, 160d
				mul di
				
				mov bh, 0h
				
				add ax, bx
				add ax, bx				

				xor di, di
				mov di, ax

				ret
				endp
				
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
; prstr_video - prints string starting with input coordinates
; Entry:	AL = X coordinate, AH = Y coordinate, BX -> string
; Destroy:	ES, DI
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

prstr_video		proc
				
				cmp bx, 0d
				je prstr_v_exit
				
				push 0b800h
				pop es
				push bx
				call set_cursor
				pop bx
				mov ax, 0h
				cmp es:[di], ax
				je prstr_v_exit
				
				xor cx, cx
prstr_v_char:
				mov cl, byte ptr [bx]
				mov es:[di], cl				; mov es:[di], byte ptr [bx] - doesn't work!
				
				inc bx
				inc di
				inc di
				
				mov cl, byte ptr [bx]
				inc cl
				
				loop prstr_v_char
prstr_v_exit:
				ret
				endp
				
Msg:	db 'Hello, GPU!', 0
				end 				Start
				
				