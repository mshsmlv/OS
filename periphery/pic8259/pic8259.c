#include "pic8259.h"
#include "helpers.h"

void init_pic8259() {
    send_byte_to_port(0x20, 0x11); // needs icw4; cascade mode enable; edge triggered mode
    io_wait();
    send_byte_to_port(0xa0, 0x11);
    io_wait();

    send_byte_to_port(0x21, 0x20); //offsets for interupts
    io_wait();
    send_byte_to_port(0xa1, 0x28); //offsets for interrupts
    io_wait();

    send_byte_to_port(0x21, 0x04); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_wait();
    send_byte_to_port(0xa1, 0x02); // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_wait();

    send_byte_to_port(0x21, 0x01); // ICW4: last bit - 8086 mode
    io_wait();
    send_byte_to_port(0xa1, 0x01);
    io_wait();

    send_byte_to_port(0x21, 0xff); // send mask to imr (interrupt mask register)
    io_wait();
    send_byte_to_port(0xa1, 0xff); 
    io_wait();
}





















//
// INT - пин прерывания процессора
// INTa - Если проц готов обработать прерывание, и они не замаскированы, то проц 
// отвечает через INTa последовательность сигналов.
//
// Во время второго сигнала на D0-D7 подает номер прерывания
// 6) бит ISR установлен пока не придет EOL
//   _______________________
//   |                      |
//   |  Priority resolver   |
//   |______________________|
//              |
//              | 
//    _______________________
//   |                      |
//   |  checking IMR        |
//   | (operate with IRR)   |
//   |______________________|
//              |
//              |
//   _______________________
//   |                      |
//   |  Send to data bus    |
//   |______________________|

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
