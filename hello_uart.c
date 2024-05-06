#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

// UART0 TX/RX pins
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define UART_ID uart0
#define DATA_LENGTH 10  // Length of data to read before the checksum
#define BUFFER_SIZE 256  // Define the buffer size

static uint8_t rx_buffer[BUFFER_SIZE];
static uint16_t head = 0;
static uint16_t tail = 0;

// Function to add a byte to the buffer
static inline void buffer_put(uint8_t c) {
    uint16_t next = (head + 1) % BUFFER_SIZE;
    if (next != tail) {  // Check buffer overflow
        rx_buffer[head] = c;
        head = next;
    } else {
        // Handle buffer overflow, e.g., discard old data or stop receiving new data
    }
}

// Function to get a byte from the buffer
static inline bool buffer_get(uint8_t *c) {
    if (tail == head) {
        return false;  // Buffer empty
    }
    *c = rx_buffer[tail];
    tail = (tail + 1) % BUFFER_SIZE;
    return true;
}

// Check if buffer is empty
static inline bool buffer_empty() {
    return (head == tail);
}
// UART interrupt handler
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
        buffer_put(ch);  // Put received character into buffer

        // Optionally, check for a complete message
        // For example, newline indicates end of a command
        if (ch == '\n') {
            process_command();  // Process the command if newline received
        }
    }
}
// Function to process commands - called when a complete command is received
void process_command() {
    uint8_t data;
    while (!buffer_empty()) {
        buffer_get(&data);
        // Process each byte in the command
        // For example, parse the command or store it for further processing
    }
    // Reset the buffer indices if needed or handle command execution
}

// Function to calculate checksum
uint8_t calculate_checksum(const uint8_t *data, size_t len) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < len; i++) {
        checksum += data[i];
    }
    return checksum;
}

// Function to read data and validate checksum
bool read_data_with_checksum(uint8_t *buf, size_t len) {
    size_t received = 0;
    while (received < len) {
        if (uart_is_readable(UART_ID)) {
            buf[received++] = uart_getc(UART_ID);
        }
    }
    // The last byte is the checksum
    uint8_t checksum = buf[len - 1];
    // Calculate checksum of the data bytes
    uint8_t calculated = calculate_checksum(buf, len - 1);
    return (checksum == calculated);
}

// Function to send ACK
void send_ack() {
    const char *ack = "ACK\n";
    uart_puts(UART_ID, ack);
}

int main() {
    stdio_init_all();
    uart_init(UART_ID, 115200);

    // Set the TX and RX pins by using the function select on the GPIO
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Set up UART to use the desired baud rate
    uart_set_baudrate(UART_ID, 115200);

    // Enable the UART interrupt
    uart_set_irq_enables(UART_ID, true, false);
    irq_set_exclusive_handler(UART0_IRQ, on_uart_rx);
    irq_set_enabled(UART0_IRQ, true);

    uint8_t buffer[DATA_LENGTH + 1];  // +1 for the checksum byte

    while (1) {
        bool valid = read_data_with_checksum(buffer, sizeof(buffer));
        if (valid) {
            // Data received with valid checksum
            send_ack();
        } else {
            // Data received with invalid checksum
            // Handle error, perhaps send a NACK
        }
    }

    return 0;
}

