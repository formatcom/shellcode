#include <string.h>
#include <sys/mman.h>

#define SHX_SIZE 0xC // 0xA + 0x2 = 0xC

/*
	nasm asm/shellcode.asm
	ndisasm -b 64 asm/shellcode
*/

// SHELLCODE syscall exit 5
char SHX[] = {
	/* 00000000 */  "\x48\x31\xDB" /* xor rbx, rbx */
	/* 00000003 */  "\x48\x31\xC0" /* xor rax, rax */
	/* 00000006 */  "\xB0\x01"     /* mov  al, 0x1 */
	/* 00000008 */  "\xB3\x05"     /* mov  bl, 0x5 */
	/* 0000000A */  "\xCD\x80"     /* int 0x80     */
};

void xcode(char *s, int len){
	void *bin;

	// asigna espacio de memoria con permiso RWX
	// con los flags de anonimo y privada
	bin = mmap(0, len,
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_ANON | MAP_PRIVATE, -1, 0);

	// copia al espacio de memoria el shellcode
	memcpy(bin, s, len);

	// ejecutamos el shellcode como puntero a una funcion
	((void(*)())bin)();

	// liberamos la memoria mapeada
	munmap(bin, len);
}

int main (int argc, char *argv[]){
	xcode(SHX, SHX_SIZE);
	return 0;
}
