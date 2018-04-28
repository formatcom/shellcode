BITS 64
;se limpian los registros rbx, rax
xor rbx, rbx
xor rax, rax
;referencia a las llamadas al sistema (syscall)
;para 64 bits -> /usr/include/asm/unistd_64.h
mov al, 0x01; 0x01 es para indicar al syscall el exit
;man -L es 2 exit -> para mas informacion
mov bl, 0x05; le pasamos al exit 0x05 como arg
int 0x80; se llama a la interrupcion
