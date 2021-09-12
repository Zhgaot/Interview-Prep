#include <stdio.h>
 
void test01()
{   
    union {
        int i;
        char x[3];
    } a;

    a.x[0] = 10;
    a.x[1] = 1;
    a.x[2] = 0;
    printf("a.i = %d\n", a.i);  // a.i = 266
}

void test02()
{
    /*定义一个联合*/
    union {
        int i;
        /*在联合中定义一个结构*/
        struct {
            char first;
            char second;
        } half;
    }number;

    /*联合成员赋值*/
    number.i = 0x4241;  // 0x42=B, 0x41=A
    printf("%c %c\n", number.half.first, number.half.second);  // A B

    /*联合中结构成员赋值*/
    number.half.first = 'a';  // 'a'=0x61
    number.half.second = 'b'; // 'b'=0x62
    printf("%x\n", number.i); // 6261
}

int main() {
    printf("--------------- test01 ---------------\n");
    test01();
    printf("\n--------------- test02 ---------------\n");
    test02();
}