#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"
#include "app_error.h"
#include "boards.h"

#ifdef SOFTDEVICE_PRESENT
    #include "softdevice_handler.h"
#endif // SOFTDEVICE_PRESENT

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfcrypt/test/test.h>
#include <wolfcrypt/benchmark/benchmark.h>


typedef struct func_args {
    int    argc;
    char** argv;
    int    return_code;
} func_args;

static func_args args = { 0 } ;


#define ENABLE_UART_ECHO_TEST

#define UART_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 1                           /**< UART RX buffer size. */

void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR) {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR) {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

void uart_init(void)
{
    uint32_t err_code;
    const app_uart_comm_params_t comm_params =
      {
          RX_PIN_NUMBER,
          TX_PIN_NUMBER,
          RTS_PIN_NUMBER,
          CTS_PIN_NUMBER,
          APP_UART_FLOW_CONTROL_ENABLED,
          false,
          UART_BAUDRATE_BAUDRATE_Baud115200
      };

    APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOW,
                         err_code);
    APP_ERROR_CHECK(err_code);
}



/**
 * @brief Function for main application entry.
 */
int main(void)
{
    //uint32_t err_code;
    int test_num = 0;

    LEDS_CONFIGURE(LEDS_MASK);
    LEDS_OFF(LEDS_MASK);

    uart_init();

#ifdef SOFTDEVICE_PRESENT
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, false);
#endif // SOFTDEVICE_PRESENT

#ifdef ENABLE_UART_ECHO_TEST
    printf("\n\rUART Echo Test (use q or Q to exit):\n\r");
    while (true) {
        uint8_t cr;

        while(app_uart_get(&cr) != NRF_SUCCESS);
        while(app_uart_put(cr) != NRF_SUCCESS);

        if (cr == 'q' || cr == 'Q') {
            printf(" \n\rExit!\n\r");
            break;
        }
    }
#endif

    do
    {
#ifndef NO_CRYPT_TEST
        printf("\nCrypt Test %d:\n", test_num);
        wolfcrypt_test(&args);
        printf("Crypt Test %d: Return code %d\n", test_num, args.return_code);
#endif

#ifndef NO_CRYPT_BENCHMARK
        printf("\nBenchmark Test %d:\n", test_num);
        benchmark_test(&args);
        printf("Benchmark Test %d: Return code %d\n", test_num, args.return_code);
#endif

        test_num++;
    } while(args.return_code == 0);    
}


/** @} */
