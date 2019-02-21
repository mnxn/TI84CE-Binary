#ifndef IO_H
#define IO_H

#include "conv.h"
#include <tice.h>

#define clear() os_ClrHome()
#define setpos(row, col) os_SetCursorPos(row, col)
#define print(text) os_PutStrLine(text)
#define print_at(text, row, col) \
    os_SetCursorPos(row, col);   \
    os_PutStrLine(text)
#define wait() while (!os_GetCSC())

void update_select(int8_t* selection, int8_t after)
{
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

void print_box()
{
    int i;
    print_at("-----------------------", 2, 2);
    for (i = 3; i < 8; i++) {
        print_at("|                     |", i, 2);
    }
    print_at("-----------------------", 8, 2);
}

uint8_t binary_input()
{
    unsigned int startRow, startCol;
    uint8_t current = 0;
    uint8_t out = 0;

    sk_key_t key;

    os_GetCursorPos(&startRow, &startCol);
    os_EnableCursor();

    while (true) {
        key = os_GetCSC();

        if (key == sk_Enter) {
            os_DisableCursor();
            setpos(startRow, startCol);
            print_binary(out);
            return out;
        } else if (key == sk_Clear) {
            out = 0;
            current = 0;
            print_at("        ", startRow, startCol);
            setpos(startRow, startCol);
        } else if (current < 8 && (key == sk_0 || key == sk_1)) {
            print_numkey(key);
            out <<= 1;
            out += key_to_int(key);
            current++;
        }
    }
}

int8_t decimal_input()
{
    unsigned int startRow, startCol;
    uint8_t current = 0;
    int8_t out = 0;
    bool isNeg = false;
    sk_key_t key;

    os_GetCursorPos(&startRow, &startCol);
    os_EnableCursor();

    while (true) {
        key = os_GetCSC();

        if (key == sk_Enter) {
            os_DisableCursor();
            if (isNeg) {
                return -out;
            }
            return out;
        } else if (key == sk_Clear) {
            out = 0;
            current = 0;
            isNeg = false;
            print_at("    ", startRow, startCol);
            setpos(startRow, startCol);
        } else if (key == sk_Sub || key == sk_Chs) {
            if (current == 0) { /* only allow negatives at beginning of number */
                isNeg = true;
                print("-");
            }
        } else if (key == sk_0
            || key == sk_1
            || key == sk_2
            || key == sk_3
            || key == sk_4
            || key == sk_5
            || key == sk_6
            || key == sk_7
            || key == sk_8
            || key == sk_9) {

            if (current < 3) {
                print_numkey(key);
                out *= 10;
                out += key_to_int(key);
                current++;
            }
        }
    }
}

#endif /* IO_H */