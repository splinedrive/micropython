#include <unistd.h>
#include "py/mpconfig.h"

/*
 * Core UART functions to implement for a port
 */

#define UART_BASE       0x30000000
#define UART_TX            ( volatile uint32_t  *) (UART_BASE + 0x0000)
#define UART_READY         ( volatile uint32_t  *) (UART_BASE + 0x0000)
#define UART_RX            ( volatile uint32_t  *) (UART_BASE + 0x003C)

int mp_hal_stdin_rx_chr(void) {
    int32_t c = -1;
#if MICROPY_MIN_USE_STDOUT
    int r = read(0, &c, 1);
    (void)r;
#else
     while (c == -1) {
       c = *((volatile uint32_t*) UART_RX);
     }
#endif
    return (char) ((c == 10 ? 13 : c));
}

void kianv_putchar(char c) {
  while (!*((volatile uint32_t*) UART_READY))
    ;
  *((volatile uint32_t*) UART_TX) = c;
}

void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
#if MICROPY_MIN_USE_STDOUT
    int r = write(1, str, len);
    (void)r;
#else
    while (len--) {
	    kianv_putchar(*str++);
    }
#endif
}
