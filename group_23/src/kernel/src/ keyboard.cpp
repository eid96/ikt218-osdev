

#include "keyboard.h"


// Keyboard scancode to ASCII mapping
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};



static void write_sc(unsigned char scancode)
{
    k_buffer[write_pos] = scancode; 
    write_pos = (write_pos + 1) % K_BUFFER_SIZE;
}

void kb_irq_handler(registers_t regs)
{
    unsigned char scancode = inb(KB_DATA_PORT);
    write_sc(scancode);
    unsigned char kb_data = read_scancode();
    if (kb_errors_check(kb_data) == KB_ERROR)
    {
        return;
    }
    int event = kb_event_type(kb_data);
    if (event == KEY_PRESS)
    {
        handle_key_press(kb_data);
    }
    else if(event == KEY_RELEASE)
    {
        handle_key_release(kb_data);
    }
    
}
void handle_key_press(unsigned char scancode)
{
    // If the scancode is range of array
    if (scancode < sizeof(sc_ascii)) 
    {
        // Get the corresponding ASCII value
        char ascii = sc_ascii[scancode];
        
        // Write it to the monitor
        monitor_put(ascii);
    }
}
void  kb_init(void)
{
    register_interrupt_handler(KB_INT_NO, kb_irq_handler);
}
