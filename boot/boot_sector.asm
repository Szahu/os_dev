[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl ; save the boot drive

mov bp, 0x9000
mov sp, bp

mov bx, MSG_STARTUP
call print_string_bios

call load_kernel
call swtich_to_pm

jmp $

%include "print.asm"
%include "disk_load.asm"
%include "gdt_setup.asm"
%include "switch_to_pm.asm"

[BITS 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string_bios

    mov bx, KERNEL_OFFSET
    mov dh, 31
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov bx, MSG_DONE_LOADING_KERNEL
    call print_string_bios

    ret

[BITS 32]
BEGIN_PM:

    mov ebx, MSG_PROT_MODE
    call print_string

    call KERNEL_OFFSET
    jmp $

MSG_PROT_MODE: db "Kernel loaded successf! ", 0
MSG_STARTUP: db "Starting the bootloader ", 0
MSG_LOAD_KERNEL: db "Loading kernel ", 0
MSG_DONE_LOADING_KERNEL: db "Kernel loaded ", 0

BOOT_DRIVE: db 0

times 510-($-$$) db 0
dw 0xAA55
