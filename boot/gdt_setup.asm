; GDT setup
gdt_start:

gdt_null:   ; mandatory null descriptor - 16 bytes of zeros
    dd 0x0
    dd 0x0

gdt_code:   ; the code segment descriptor
    ; base = 0x0, limit = 0x000fffff
    ; 1st flags:  present = 1, privilage = 00, desc_type = 1 -> 0b1001
    ; type flags: code = 1, conforming = 0, readable = 1, accessed = 0 -> 0b1010
    ; 2nd flags:  granularity = 1, 32-bit default = 1, 64-bit seg = 0, AVL = 0 -> 0b1100
    dw 0xffff    ; Limit bits 0-15
    dw 0x0       ; Base bits 0-15
    db 0x0       ; Base bits 16-23
    db 10011010b ; 1st flags, type flags
    db 11001111b ; 2nd flags, Limit bits 16-19
    db 0x0       ; Base bits 24-31

gdt_data:   ; the data segment descriptor
    ; only the type flags are different 0b0010
    dw 0xffff    ; Limit bits 0-15
    dw 0x0       ; Base bits 0-15
    db 0x0       ; Base bits 16-23
    db 10010010b ; 1st flags, type flags
    db 11001111b ; 2nd flags, Limit bits 16-19
    db 0x0       ; Base bits 24-31

gdt_end: ; for calculating the size of the table

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size of the gdt
    dd gdt_start               ; address of the tabel

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

