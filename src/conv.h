#ifndef CONV_H
#define CONV_H

#include <tice.h>

void print_int(int8_t x)
{
    char str[5];
    real_t real;

    real = os_Int24ToReal(x);
    os_RealToStr(str, &real, -1, 0, -1);
    os_PutStrLine(str);
}

void print_binary(int8_t x)
{
    int i;
    char str[9];

    for (i = 7; i >= 0; i--) {
        str[i] = (x & 1) + '0';
        x >>= 1;
    }
    str[8] = '\0';

    os_PutStrLine(str);
}

void print_numkey(sk_key_t key)
{
    switch (key) {
    case sk_0:
        os_PutStrLine("0");
        break;
    case sk_1:
        os_PutStrLine("1");
        break;
    case sk_2:
        os_PutStrLine("2");
        break;
    case sk_3:
        os_PutStrLine("3");
        break;
    case sk_4:
        os_PutStrLine("4");
        break;
    case sk_5:
        os_PutStrLine("5");
        break;
    case sk_6:
        os_PutStrLine("6");
        break;
    case sk_7:
        os_PutStrLine("7");
        break;
    case sk_8:
        os_PutStrLine("8");
        break;
    case sk_9:
        os_PutStrLine("9");
        break;
    }
}

int key_to_int(sk_key_t key)
{
    switch (key) {
    case sk_0:
        return 0;
    case sk_1:
        return 1;
    case sk_2:
        return 2;
    case sk_3:
        return 3;
    case sk_4:
        return 4;
    case sk_5:
        return 5;
    case sk_6:
        return 6;
    case sk_7:
        return 7;
    case sk_8:
        return 8;
    case sk_9:
        return 9;
    default:
        return 0;
    }
}

#endif /* CONV_H */