#include "conv.h"
#include "io.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tice.h>

#define LB "\xC1" /* [ is ascii code 193 on the calculator */
#define page(id) void page_##id(void)

page(home);
page(tobin);
page(todec);
page(add);

void (*pages[4])(void) = {
    page_home,
    page_tobin,
    page_todec,
    page_add
};

void main(void)
{
    page_home();
}

page(home)
{
    int8_t current = 1;

    clear();

    print_at("Binary Converter", 0, 5);
    print_at(">" LB "1] Decimal to Binary", 3, 2);
    print_at(LB "2] Binary to Decimal", 4, 3);
    print_at(LB "3] Binary Addition", 5, 3);
    print_at("Select a Mode", 7, 6);

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

page(tobin)
{
    int i;
    int8_t decimal;

    clear();
    print_box();
    print_at("Decimal to Binary", 0, 5);
    print_at("Decimal:", 4, 5);
    print_at("Binary:", 6, 6);

    setpos(4, 14);
    decimal = decimal_input();

    setpos(6, 14);
    print_binary(decimal);

    wait();
    page_home();
}

page(todec)
{
    int i;
    int8_t decimal;

    clear();
    print_box();
    print_at("Binary to Decimal", 0, 5);
    print_at("Binary:", 4, 6);
    print_at("Decimal:", 6, 5);

    setpos(4, 14);
    decimal = binary_input();

    setpos(6, 14);
    print_int(decimal);

    wait();
    page_home();
}

page(add)
{
    int i;
    int8_t decimal_1;
    int8_t decimal_2;

    clear();
    print_box();

    print_at("Binary Addition", 0, 5);
    print_at("Binary:", 3, 6);
    print_at("Binary:", 4, 6);
    print_at("Binary:", 6, 6);
    print_at("Decimal:", 7, 5);

    setpos(3, 14);
    decimal_1 = binary_input();
    setpos(4, 14);
    decimal_2 = binary_input();

    setpos(6, 14);
    print_binary(decimal_1 + decimal_2);
    setpos(7, 14);
    print_int(decimal_1 + decimal_2);

    wait();
    page_home();
}
