#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../drivers/eval.h"

#include "util.h"
#include "mem.h"

#define BLACK_ON_WHITE 0x0F
#define WOB_GREEN 0x0A
#define WOB_RED 0x04
#define WOB_BLUE 0x01
#define WOB_CYAN 0x03
#define WOB_MAGENTA 0x05
#define WOB_YELLOW 0x06

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
    print_string("Installing interrupt service routines (ISRs). ");
    isr_install();
    print_string("[");
    print_string_color("OK", WOB_GREEN);
    print_string("]\n");

    print_string("Enabling external interrupts. ");
    asm volatile("sti");
    print_string("[");
    print_string_color("OK", WOB_GREEN);
    print_string("]\n");

    print_string("Initializing keyboard (IRQ 1). ");
    init_keyboard();
    print_string("[");
    print_string_color("OK", WOB_GREEN);
    print_string("]\n");

    print_string("Initializing dynamic memory. ");
    init_dynamic_mem();
    print_string("[");
    print_string_color("OK", WOB_GREEN);
    print_string("]\n");

    print_string_color("\nleafOS", WOB_RED);
    print_string(" dev ");
    print_string_color("0.10\n", WOB_CYAN);

    int *ptr1 = alloc(5);

    int *ptr2 = alloc(10);

    mem_free(ptr1);

    int *ptr3 = alloc(2);

    mem_free(ptr2);

    mem_free(ptr3);

    print_string_color("\nleafOS", WOB_RED);print_string(" >");print_string_color(" /test/", WOB_CYAN);print_string_color(" $ ", WOB_GREEN);
}

void execute_command(char *input) {
    if (compare_string(input, "DISPOSE") == 0) {
        print_string("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    if (compare_string(input, "HELP") == 0) {
        print_string("leafOS Help\n\nHELP - Shows help.\nDISPOSE - Stops the CPU.");
        print_string_color("\nleafOS", WOB_RED);print_string(" >");print_string_color(" /test/", WOB_CYAN);print_string_color(" $ ", WOB_GREEN);
        return;
    }
    if (compare_string(input, "TOUCH") == 0) {
        print_string("TOUCH: Creates a file.");
        print_string_color("\nleafOS", WOB_RED);print_string(" >");print_string_color(" /test/", WOB_CYAN);print_string_color(" $ ", WOB_GREEN);
        return;
    }
    if (compare_string(input, "MKDIR") == 0) {
        print_string("MKDIR: Makes a directory.");
        print_string_color("\nleafOS", WOB_RED);print_string(" >");print_string_color(" /test/", WOB_CYAN);print_string_color(" $ ", WOB_GREEN);
        return;
    }
    if (compare_string(input, "LS") == 0) {
        print_string("LS: Lists all directories and files.");
        print_string_color("\nleafOS", WOB_RED);print_string(" >");print_string_color(" /test/", WOB_CYAN);print_string_color(" $ ", WOB_GREEN);
        return;
    }
    if (compare_string(input, "CLEAR") == 0) {
        clear_screen();
        print_string_color("\nleafOS", WOB_RED);print_string(" >");print_string_color(" /test/", WOB_CYAN);print_string_color(" $ ", WOB_GREEN);
        return;
    }
    if (compare_string(input, "EVAL") == 0) {
        print_string_color("Running ", WOB_GREEN);
        print_string("C ");
        print_string_color("Code", WOB_CYAN);
        print_string("...\n");
        eval(input);
        print_string_color("\nleafOS", WOB_RED);print_string(" >");print_string_color(" /test/", WOB_CYAN);print_string_color(" $ ", WOB_GREEN);
        return;
    }
    print_string("Unknown command: ");
    print_string(input);
    print_string_color("\nleafOS", WOB_RED);print_string(" >");print_string_color(" /test/", WOB_CYAN);print_string_color(" $ ", WOB_GREEN);
}