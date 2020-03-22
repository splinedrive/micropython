#include <unistd.h>
#include "py/mpconfig.h"

/*
 * Core UART functions to implement for a port
 */

struct wb_uart {
        uint32_t data;
        uint32_t clkdiv;
} __attribute__((packed,aligned(4)));

#define UART_BASE       0x81000000

static volatile struct wb_uart * const uart_regs = (void*)(UART_BASE);

// Receive single character
int mp_hal_stdin_rx_chr(void) {
    unsigned char c = 0;
#if MICROPY_MIN_USE_STDOUT
    int r = read(0, &c, 1);
    (void)r;
#else
    int32_t cl;
    do {
	    cl = uart_regs->data;
    } while (cl & 0x80000000);
    c = cl & 0xff;
#endif
    return c;
}

// Send string of given length
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
#if MICROPY_MIN_USE_STDOUT
    int r = write(1, str, len);
    (void)r;
#else
    while (len--) {
	    uart_regs->data = *str++;
    }
#endif
}
