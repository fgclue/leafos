#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"

#include "util.h"
#include "mem.h"

void* alloc(int n) {
    int *ptr = (int *) mem_alloc(n * sizeof(int));
    if (ptr == NULL_POINTER) {
        print_string("Memory not allocated.\n");
    } else {
        // Get the elements of the array
        for (int i = 0; i < n; ++i) {
//            ptr[i] = i + 1; // shorthand for *(ptr + i)
        }

        for (int i = 0; i < n; ++i) {
//            char str[256];
//            int_to_string(ptr[i], str);
//            print_string(str);
        }
//        print_nl();
    }
    return ptr;
}

void start_kernel() {
    clear_screen();
    print_string("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print_string("Enabling external interrupts.\n");
    asm volatile("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

    print_string("Initializing dynamic memory.\n");
    init_dynamic_mem();

    print_string("dddddOS dev\n");

    int *ptr1 = alloc(5);

    int *ptr2 = alloc(10);

    mem_free(ptr1);

    int *ptr3 = alloc(2);

    mem_free(ptr2);

    mem_free(ptr3);

    print_string("dddddISO > /test/ $ ");
}

void execute_command(char *input) {
    if (compare_string(input, "DISPOSE") == 0) {
        print_string("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    if (compare_string(input, "HELP") == 0) {
        print_string("dddddOS Help\n\nHELP - Shows help.\nDISPOSE - Stops the CPU.");
        print_string("\ndddddISO > /test/ $ ");
        return 0;
    }
    if (compare_string(input, "TOUCH") == 0) {
        print_string("TOUCH: Creates a file.");
        print_string("\ndddddISO > /test/ $ ");
        return 0;
    }
    if (compare_string(input, "MKDIR") == 0) {
        print_string("MKDIR: Makes a directory.");
        print_string("\ndddddISO > /test/ $ ");
        return 0;
    }
    if (compare_string(input, "LS") == 0) {
        print_string("LS: Lists all directories and files.");
        print_string("\ndddddISO > /test/ $ ");
        return 0;
    }
    print_string("Unknown command: ");
    print_string(input);
    print_string("\n > /test/ ! ");
}
