#include <stdio.h>

void byteorder() {
    union {
        short value;  // 2(bit) * 1 = 2 bit
        char bytes[sizeof(short)];  // 1(bit) * 2 = 2 bit
    }test;

    test.value = 0x0102;

    if ((test.bytes[0] == 2) && (test.bytes[1] == 1))
        printf("little endian\n");
    else if ((test.bytes[0] == 1) && (test.bytes[1] = 2))
        printf("big endian\n");
    else
        printf("unknown...\n");
}

int main() {
    byteorder();
}
