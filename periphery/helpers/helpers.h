static inline void send_byte_to_port(unsigned short port, unsigned char value) {
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

static inline void io_wait(void) {
    asm volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}

