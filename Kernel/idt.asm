global _lidt
global _irq00handler
extern irqDispatcher

%macro irqHandlerMaster 1
	pushaq

	mov rax, %1
	push rax
	call irqDispatcher
	pop rax

	mov al, 20h
	out 20h, al

	popaq
	iret
%endmacro

section .text

_lidt:
	push rbp
	mov rbp, rsp

	push rbx
	rol rbx, 16

	pop rbx
	pop rbp

	retn

_irq00handler:
	irqHandlerMaster 0




