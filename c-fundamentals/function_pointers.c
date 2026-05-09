#include <stdio.h>
#include <stdint.h>

void say_hello(void)
{
  printf("Hello from say_hello\n");
}

void say_goodbye(void)
{
  printf("Goodbye from say_goodbye\n");
}

int add(int a, int b)
{
  return a + b;
}

int subtract(int a, int b)
{
  return a - b;
}

int multiply(int a, int b)
{
  return a * b;
}

typedef struct
{
  void (*init)(uint32_t baud_rate);
  void (*send)(uint8_t data);
  uint8_t (*receive)(void);
  void (*deinit)(void);
} UART_Driver_t;

void uartA_init(uint32_t baud_rate)
{
  printf("[UART-A] Initialized at %u baud\n", (unsigned int)baud_rate);
}

void uartA_send(uint8_t data)
{
  printf("[UART-A] Sending: 0x%02X\n", data);
}

uint8_t uartA_receive(void)
{
  printf("[UART-A] Receivng byte\n");
  return 0xAA;
}

void uartA_deinit(void)
{
  printf("[UART-A] Deinitialized\n");
}

void uartB_init(uint32_t baud_rate)
{
  printf("[UART-B] Initialized at %u baud\n", (unsigned int)baud_rate);
}

void uartB_send(uint8_t data)
{
  printf("[UART-B] Sending: 0x%02X\n", data);
}

uint8_t uartB_receive(void)
{
  printf("[UART-B] Receivng byte\n");
  return 0xAA;
}

void uartB_deinit(void)
{
  printf("[UART-B] Deinitialized\n");
}

static const UART_Driver_t UART_A_Driver = {
    .init = uartA_init,
    .send = uartA_send,
    .receive = uartA_receive,
    .deinit = uartA_deinit};

static const UART_Driver_t UART_B_Driver = {
    .init = uartB_init,
    .send = uartB_send,
    .receive = uartB_receive,
    .deinit = uartB_deinit};

void run_uart_application(const UART_Driver_t *driver, uint32_t baud_rate)
{
  driver->init(baud_rate);
  driver->send(0x55);
  uint8_t data = driver->receive();
  printf("Received: 0x%02X\n", data);
  driver->deinit();
}

typedef enum
{
  STATE_IDLE = 0,
  STATE_RUNNING,
  STATE_ERROR,
  STATE_COUNT
} SystemState_t;

void handle_idle(void)
{
  printf("Handling IDLE state\n");
}

void handle_running(void)
{
  printf("Handling RUNNING state\n");
}

void handle_error(void)
{
  printf("Handling ERROR state\n");
}

typedef void (*StateHandler_t)(void);

// Dispatch table
static const StateHandler_t state_handlers[STATE_COUNT] = {
    [STATE_IDLE] = handle_idle,
    [STATE_RUNNING] = handle_running,
    [STATE_ERROR] = handle_error};

int main(void)
{
  printf("=== Part 1: Basic Function Pointers ===\n");

  void (*greet)(void) = say_hello;
  greet();

  greet = say_goodbye;
  greet();

  int (*math_op)(int, int) = add;
  printf("add(3, 4)    = %d\n", math_op(3, 4));

  math_op = subtract;
  printf("substract(3, 4)   = %d\n", math_op(3, 4));

  math_op = multiply;
  printf("multiply(3, 4)    = %d\n", math_op(3, 4));

  printf("=== Part 2: Driver Abstraction ===\n");
  run_uart_application(&UART_A_Driver, 900);

  return 0;
}