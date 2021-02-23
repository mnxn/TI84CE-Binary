#ifndef IO_H
#define IO_H

#include <tice.h>

#include "conv.h"

void wait() {
    while (!os_GetCSC()) {
        // do nothing
    }
    return;
}

void print_at(const char* text, uint8_t row, uint8_t col) {
    os_SetCursorPos(row, col);
    os_PutStrLine(text);
}

void print_at_reset(const char* text, uint8_t row, uint8_t col) {
    os_SetCursorPos(row, col);
    os_PutStrLine(text);
    os_SetCursorPos(row, col);
}

void print_box() {
    print_at("-----------------------", 2, 2);
    for (int i = 3; i < 8; i++) {
        print_at("|                     |", i, 2);
    }
    print_at("-----------------------", 8, 2);
}

uint8_t binary_input() {
    unsigned int startRow, startCol;
    os_GetCursorPos(&startRow, &startCol);
    os_EnableCursor();

    uint8_t current = 0;
    uint8_t out = 0;

    while (true) {
        sk_key_t key = os_GetCSC();

        if (key == sk_Enter) {
            os_DisableCursor();
            os_SetCursorPos(startRow, startCol);
            print_binary(out);
            return out;
        } else if (key == sk_Clear) {
            out = 0;
            current = 0;
            print_at_reset("        ", startRow, startCol);
        } else if (current < 8 && (key == sk_0 || key == sk_1)) {
            print_numkey(key);
            out <<= 1;
            out += key_to_int(key);
            current++;
        }
    }
}

int8_t decimal_input() {
    unsigned int startRow, startCol;
    os_GetCursorPos(&startRow, &startCol);
    os_EnableCursor();

    bool isNegative = false;
    uint8_t current = 0;
    int8_t out = 0;

    while (true) {
        sk_key_t key = os_GetCSC();

        if (key == sk_Enter) {
            os_DisableCursor();
            if (isNegative) {
                return -out;
            }
            return out;
        } else if (key == sk_Clear) {
            out = 0;
            current = 0;
            isNegative = false;
            print_at_reset("    ", startRow, startCol);
        } else if (key == sk_Sub || key == sk_Chs) {
            if (current == 0) {  // only allow negatives at beginning of number
                isNegative = true;
                os_PutStrLine("-");
            }
        } else if (
            key == sk_0 || key == sk_1 || key == sk_2 || key == sk_3 ||
            key == sk_4 || key == sk_5 || key == sk_6 || key == sk_7 ||
            key == sk_8 || key == sk_9) {
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
