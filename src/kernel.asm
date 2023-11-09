[BITS 32]


; this causes to run C kernel.c code sequantially from the beginning
; section .asm

global _start

extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov ebp, 0x00200000
	mov esp, ebp
	
	; enable A20
	in al, 0x92
	or al, 2
	out 0x92, al


	; Remap the master PIC
	mov al, 00010001b
	out 0x20, al ; Tell master PIC

	mov al, 0x20 ; Where the master ISR should start
	out 0x21, al

	mov al, 00000001b
	out 0x21, al
	; End remap the master
	 
	; It isn't the right way to enable interrupts before
	; we initialize interrupt descriptor table
	; sti

	call kernel_main

	jmp $


times 512-($ - $$) db 0

