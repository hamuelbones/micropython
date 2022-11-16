#include "py/mpconfig.h"
#include "py/stream.h"
#include <tonc.h>

// UART settings
#define SIO_USE_UART      0x3000

// Baud Rate
#define SIO_BAUD_9600     0x0000
#define SIO_BAUD_38400    0x0001
#define SIO_BAUD_57600    0x0002
#define SIO_BAUD_115200   0x0003

#define SIO_CTS           0x0004
#define SIO_PARITY_ODD    0x0008
#define SIO_SEND_DATA     0x0010
#define SIO_RECV_DATA     0x0020
#define SIO_ERROR         0x0040
#define SIO_LENGTH_8      0x0080
#define SIO_USE_FIFO      0x0100
#define SIO_USE_PARITY    0x0200
#define SIO_SEND_ENABLE   0x0400
#define SIO_RECV_ENABLE   0x0800
#define SIO_REQUEST_IRQ   0x4000

#define UART_RCV_BUFFER_SIZE 256
char g_rcv_buffer[UART_RCV_BUFFER_SIZE];

void init_uart(u16 uart) {
    REG_RCNT = 0;

    REG_SIOCNT = uart | SIO_MODE_UART | SIO_LENGTH_8 | SIO_SEND_ENABLE | SIO_RECV_ENABLE;
    REG_SIOCNT |= SIO_USE_FIFO;
}

void setup_uart(void) {
    init_uart(SIO_BAUD_115200);
}

// Receive single character, blocking until one is available.
int mp_hal_stdin_rx_chr(void) {
    while(REG_SIOCNT & SIO_RECV_DATA);
    //while (1);
    int c = REG_SIODATA8;

    if (c == '\n') {
        return '\r';
    }

    return c;
}

// Send the string of given length.
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {

    if (!len) {
        return;
    }

    for(s32 i = 0; i < len; i++) {
        // Wait until the send queue is empty
        while(REG_SIOCNT & SIO_SEND_DATA);

        // Bung our byte into the data register
        REG_SIODATA8 = str[i];
    }

    while (len--) {
        char c = *str++;
        switch(c) {
            case '\n':
                tte_write("\n");
                break;
            default:
                tte_putc(c);
                break;
        }
    }
}

uintptr_t mp_hal_stdio_poll(uintptr_t poll_flags) {
    uintptr_t ret = 0;
    if ((poll_flags & MP_STREAM_POLL_RD) &&
        !(REG_SIOCNT & SIO_RECV_DATA)) {
        ret |= MP_STREAM_POLL_RD;
    }
    return ret;
}
