extern "C"{
    #include "system.h"
    #include "../include/descriptor_tables.h"
    #include "../include/common.h"
    #include "../include/monitor.h"
    //#include "../include/isr.h"
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

Keyboard::hook_keyboard([](uint8_t scancode, void* context){
        //auto* os = (OperatingSystem*)context;
        monitor_write("Print stuff"); 
        //monitor_put(scancode); 
        //monitor_write(")");
        //monitor_write("/n");
    }, NULL);

    //clear_screen();
    //write_string("Hello, World!");
    
	 
}