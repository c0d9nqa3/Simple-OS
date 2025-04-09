kkBITS 16
ORG 0x7c00

; Clear the screen
mov ah, 0x00
mov al, 0x03
int 0x10

; Print boot message
mov si, boot_message
call print_string

; Load kernel into memory at 0x1000:0x0000
mov ax, 0x1000        ; Kernel load segment address
mov es, ax
xor bx, bx
mov ah, 0x02          ; BIOS disk read function
mov al, 10            ; Read 10 sectors
mov ch, 0
mov cl, 2             ; Start from the second sector
mov dh, 0
int 0x13

jc load_error          ; If read fails, jump to error handler

; Print kernel loaded message
mov si, kernel_loaded_message
call print_string

; Jump to the kernel entry point
jmp 0x1000:0x0000

load_error:
mov si, error_message
call print_string
jmp $

print_string:
    mov ah, 0x0E
.next_char:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .next_char
.done:
    ret

boot_message db 'Booting Simple OS...', 0
kernel_loaded_message db 'Kernel loaded successfully!', 0
error_message db 'Kernel load failed!', 0

TIMES 510 - ($ - $$) db 0
DW 0xAA55

