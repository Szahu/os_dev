[BITS 16]
print_string_bios:
    pusha               ; Preserve bx

.loop:
    mov al, [bx]         ; Load the byte at [BX] into AL
    cmp al, 0            ; Check if the byte is null (end of string)
    je .done             ; If null, exit the loop
    mov ah, 0x0E         ; BIOS teletype output function
    int 0x10             ; Print the character
    inc bx               ; Increment BX to point to the next character
    jmp .loop            ; Repeat the loop

.done:
    popa            ; Restore bx
    ret                  


[BITS 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
print_string:
    pusha
    mov edx, VIDEO_MEMORY

  print_string_loop:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK

    cmp al, 0
    je print_string_done

    mov [edx], ax
    add ebx, 1
    add edx, 2

    jmp print_string_loop

  print_string_done:
    popa
    ret

hex_digit_to_ascii:
    cmp al, 9
    jg is_letter
    add al, '0'
    jmp done
  is_letter:
    add al, 'A' - 10

  done:
    ret

print_hex:
    pusha
    
    mov ax, dx
    and ax, 0x000f
    call hex_digit_to_ascii
    mov bx, HEX_OUT
    add bx, 5
    mov byte [bx], al

    mov ax, dx
    and ax, 0x00f0
    shr ax, 4
    call hex_digit_to_ascii
    mov bx, HEX_OUT
    add bx, 4
    mov byte [bx], al

    mov ax, dx
    and ax, 0x0f00
    shr ax, 8
    call hex_digit_to_ascii
    mov bx, HEX_OUT
    add bx, 3
    mov byte [bx], al

    mov ax, dx
    and ax, 0xf000
    shr ax, 12
    call hex_digit_to_ascii
    mov bx, HEX_OUT
    add bx, 2
    mov byte [bx], al

    mov bx, HEX_OUT
    call print_string
    popa
    ret

HEX_OUT: db '0x0000', 0
