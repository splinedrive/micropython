#include <unistd.h>
#include "py/mpconfig.h"

#include <generated/csr.h>

#define UART_EV_TX 0x1
#define UART_EV_RX 0x2



/*
 * Core UART functions to implement for a port
 */

// Receive single character
int mp_hal_stdin_rx_chr(void) {
    unsigned char c = 0;
#if MICROPY_MIN_USE_STDOUT
    int r = read(0, &c, 1);
    (void)r;
#else
    while (uart_rxempty_read())
            __asm__("nop");
    uart_ev_pending_write(UART_EV_RX);
    c = uart_rxtx_read();
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
    	while (uart_txfull_read())
        	__asm__("nop");
        uart_rxtx_write(*str++);
    }
#endif
}
