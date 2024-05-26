#include <stdio.h>

int main() {
    const char *msg = "Hello, World!\n";

    asm volatile (
        "movl $4, %%eax\n"        // syscall number for sys_write
        "movl $1, %%ebx\n"        // file descriptor STDOUT
        "movl %0, %%ecx\n"        // address of the message
        "movl $13, %%edx\n"       // length of the message
        "int $0x80\n"             // invoke syscall
        :
        : "r" (msg)
        : "%eax", "%ebx", "%ecx", "%edx"
    );

    return 0;
}
