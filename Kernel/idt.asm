GLOBAL _irq00handler
GLOBAL _sti
GLOBAL _cli
GLOBAL picMasterMask
GLOBAL picSlaveMask

EXTERN irqDispatcher
EXTERN _vWrite

%macro irqHandlerMaster 1
	pushaq

	mov rdi, %1
	push rdi
	call irqDispatcher
	pop rdi

	mov al, 20h ; Acknowledge interruption was treated
	out 20h, al ; and PIC can recieve the next one

	popaq
	iretq
%endmacro

section .text

; Disable interruptions
_cli:
	cli
	ret

; Enable interruptions
_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, si
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, si  ; ax = mascara de 16 bits
    out		0A1h, al
    pop     rbp
    retn

; Timer tick
_irq00handler:
	irqHandlerMaster 0

