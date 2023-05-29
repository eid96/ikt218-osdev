#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "isr.h"
#include "monitor.h"

// Define the keyboard data port
#define KB_DATA_PORT 0x60

// Define the keyboard interrupt number
#define KB_INT_NO 33

// Define a constant for a keyboard error
#define KB_ERROR -1

// Define constants for keyboard events
#define KEY_PRESS 1
#define KEY_RELEASE 0

// Size of keyboard buffer
#define K_BUFFER_SIZE 256

// Keyboard buffer
static unsigned char k_buffer[K_BUFFER_SIZE];


// Position of the next scancode be read from the buffer
static int read_pos = 0;

// Position of next scancode to be written to buffer
static int write_pos = 0;

static unsigned char read_scancode(void)
{
    unsigned char scancode = k_buffer[read_pos];
    read_pos = (read_pos + 1) % K_BUFFER_SIZE;
    return scancode; 
}
// Initializes the keyboard
void kb_init(void);

// Handles keyboard interrupts
void kb_irq_handler(registers_t regs);

// Checks for errors in keyboard data
int kb_errors_check(unsigned char data);

// Gets keyboard events
int kb_event_type(unsigned char data);

// Handle  key press events
void handle_key_press(unsigned char data);

//handles key release events
void handle_key_release(unsigned char scancode);

#endif // KEYBOARD_H