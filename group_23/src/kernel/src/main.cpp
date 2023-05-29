extern "C"{
    #include "system.h"
    #include "../include/descriptor_tables.h"
    #include "../include/common.h"
    #include "../include/monitor.h"
    
    #include "../include/keyboard.h"

}


// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    monitor_clear();
    
    init_descriptor_tables();
    monitor_write("Hello, World!\n");
    monitor_clear(); 
 
   
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
    asm volatile("sti");
    kb_init();
   if (read_pos != write_pos) {
            unsigned char kb_data = read_scancode();
            int event = kb_event_type(kb_data);

            if (event == KEY_PRESS) {
                handle_key_press(kb_data);
            } else if (event == KEY_RELEASE) {
                handle_key_release(kb_data);
            }
        }
    
   




    //clear_screen();
    //write_string("Hello, World!");
    
	 
}