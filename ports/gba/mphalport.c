#include "py/mpconfig.h"
#include "tonc_tte.h"

// Receive single character, blocking until one is available.
int mp_hal_stdin_rx_chr(void) {
    static char *fixed_data = "2+2\rprint(\"link cable next for actual input???\")\r";
    static uint index = 0;

    if (fixed_data[index]) {
        int retval = fixed_data[index];
        index += 1;
        return retval;
    }

    while (1) {

    }
    return 0;
}

// Send the string of given length.
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {

    if (!len) {
        return;
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
