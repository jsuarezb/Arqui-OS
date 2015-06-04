;	sysCallHandler -> int 80
;	Hacer sys call (primer parm rax)
;		rdi - rsi - rdx - rbx
;	Func 
;		rax - rbx - rcx - rbx
; WRITE ( file desc, buffer, cant)
; READ ( file desc, buffer, cant)

GLOBAL execSysCall

execSysCall:
	push rbp
	mov rbp, rsp

	mov rax, rdi
	mov rdi, rsi 
	mov rsi, rdx
	mov rdx, rcx

	int 80h

	mov rsp, rbp
	pop rbp
	ret 
