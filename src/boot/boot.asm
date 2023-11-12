ORG 0x7c00
BITS 16


CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start 

_start:
	jmp short start
	nop

times 33 db 0

start:
	jmp 0:step2

step2:
	cli ; clear interrupts
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00
	sti ; enable interrupts
	

.load_protected:
	cli
	lgdt[gdt_descriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEG:load32
	

gdt_start:

gdt_null:
	dd 0x0
	dd 0x0

; offset 0x8
gdt_code: ; CS should point to this
	dw 0xffff ; segment limit 0-15 bit
	dw 0 ; base 0-15 bits
	db 0 ; base 16-23 bits
	db 0x9a ; Access bytes
	db 11001111b ; high 4 bits and low bit flags
	db 0 ; base 24-31

; offset 0x10
gdt_data: ; DS, SS, ES, FS, GS should point to this
	dw 0xffff ; segment limit 0-15 bit
	dw 0 ; base 0-15 bits
	db 0 ; base 16-23 bits
	db 0x92 ; Access bytes
	db 11001111b ; high 4 bits and low bit flags
	db 0 ; base 24-31

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

[BITS 32]
load32: ; load kernel code from memory
	mov eax, 1 ; which sector  to read
	mov ecx, 100 ; how much sectors we want to read into RAM
	mov edi, 0x0100000 ; memory address to loadm into RAM
	call ata_lba_read
	jmp CODE_SEG:0x0100000

ata_lba_read:
	mov ebx, eax ; backup lda
	; send highest 8 bits of the lba to hard disk controller
	shr eax, 24
	or eax, 0xE0 ; select the master drive
	mov dx, 0x1F6
	out dx, al
	; Finished sending the highest 8 to lba
	
	; Send total sectors to read
	mov eax, ecx
	mov dx, 0x1F2
	out dx, al
	; Finished send the total sectors to lba

	; Send more bits of the lba
	mov eax, ebx
	mov dx, 0x1F3
	out dx, al
	; Finished sending more bits of LBA

	; send more bits of the LBA
	mov dx, 0x1F4
	mov eax, ebx ; restore the backup LBA
	shr eax, 8
	out dx, al
	
	; Send upper 16 bits of the LBA
	mov dx, 0x1F5
	mov eax, ebx
	shr eax, 16
	out dx, al
	; Finished sending upper 16 bits of the LBA

	mov dx, 0x1F7
	mov al, 0x20
	out dx, al
	

; read all sectorsinto memory
.next_sector:
	push ecx

; check if we need to read
.try_again:
	mov dx, 0x1F7
	in al, dx
	test al, 8
	jz .try_again


; we need to read 256 words at a time
	mov ecx, 256
	mov dx, 0x1f0
	rep insw
	pop ecx
	loop .next_sector
	; end of reading words from sectors
	ret


times 510-($ - $$) db 0
dw 0xAA55

