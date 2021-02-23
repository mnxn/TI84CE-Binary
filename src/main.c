#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tice.h>

#include "conv.h"
#include "io.h"

#define LB "\xC1"  // [ is ascii code 193 on the calculator

#define page(id) void page_##id(void)

page(home);
page(tobin);
page(todec);
page(add);

void (*pages[4])(void) = {page_home, page_tobin, page_todec, page_add};

int main(void) {
    page_home();
    return 0;
}

void update_select(int8_t* selection, int8_t after) {
    print_at(" ", 2 + *selection, 2);

    if (after > 3) {
        *selection = 1;
    } else if (after < 1) {
        *selection = 3;
    } else {
        *selection = after;
    }

    print_at(">", 2 + *selection, 2);
}

page(home) {
    os_ClrHome();

    print_at("Binary Converter", 0, 5);
    print_at(">" LB "1] Decimal to Binary", 3, 2);
    print_at(LB "2] Binary to Decimal", 4, 3);
    print_at(LB "3] Binary Addition", 5, 3);
    print_at("Select a Mode", 7, 6);

    int8_t current = 1;
    while (true) {
        switch (os_GetCSC()) {
            case sk_Del:
            case sk_Clear:
                return;

            case sk_2nd:
            case sk_Enter:
                (*pages[current])();
                return;

            case sk_1:
                update_select(&current, 1);
                break;
            case sk_2:
                update_select(&current, 2);
                break;
            case sk_3:
                update_select(&current, 3);
                break;

            case sk_Up:
                update_select(&current, current - 1);
                break;
            case sk_Down:
                update_select(&current, current + 1);
                break;
        }
    }
}

page(tobin) {
    os_ClrHome();
    print_box();
    print_at("Decimal to Binary", 0, 5);
    print_at("Decimal:", 4, 5);
    print_at("Binary:", 6, 6);

    os_SetCursorPos(4, 14);
    int8_t decimal = decimal_input();

    os_SetCursorPos(6, 14);
    print_binary(decimal);

    wait();
    page_home();
}

page(todec) {
    os_ClrHome();
    print_box();
    print_at("Binary to Decimal", 0, 5);
    print_at("Binary:", 4, 6);
    print_at("Decimal:", 6, 5);

    os_SetCursorPos(4, 14);
    int8_t decimal = binary_input();

    os_SetCursorPos(6, 14);
    print_int(decimal);

    wait();
    page_home();
}

page(add) {
    os_ClrHome();
    print_box();

    print_at("Binary Addition", 0, 5);
    print_at("Binary:", 3, 6);
    print_at("Binary:", 4, 6);
    print_at("Binary:", 6, 6);
    print_at("Decimal:", 7, 5);

    os_SetCursorPos(3, 14);
    int8_t decimal_1 = binary_input();
    os_SetCursorPos(4, 14);
    int8_t decimal_2 = binary_input();

    os_SetCursorPos(6, 14);
    print_binary(decimal_1 + decimal_2);
    os_SetCursorPos(7, 14);
    print_int(decimal_1 + decimal_2);

    wait();
    page_home();
}
