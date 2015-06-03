; get and set the current time and date
GLOBAL get_time
GLOBAL get_date
GLOBAL set_time
GLOBAL set_date

start:

get_date:
	push rbp      ; Armado de stack frame
    mov rbp, rsp  ;

	cli  				
    mov al, rdi		; first argument
    out 0x70, al 	; get the date data
    in al, 0x71		; get the date data
    sti 	
    mov rax , al	; return the date data

    mov rsp, rbp  ; Desarmado de stack frame
    pop rbp
    ret

set_date:
	push rbp      ; Armado de stack frame
    mov rbp, rsp  ;

	cli             
	mov al , rdi 	; first argument
	out 0x70,al     ; set the date data
	mov al, rsi		; second argument
	out 0x71,al 
	sti 

    mov rsp, rbp  ; Desarmado de stack frame
    pop rbp
    ret