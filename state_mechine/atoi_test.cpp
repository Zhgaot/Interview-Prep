#include <iostream>
#include "atoi.h"

using namespace std;
using namespace myatoi;

int main() {

    cout << "string: '-50'           " \
    << "Atoi: " << Atoi("-50") << endl;

    char c_str[] = " 0100";
    cout << "char[]: ' 0100'         " \
    << "Atoi: " << Atoi(c_str, static_cast<int>(sizeof(c_str) / sizeof(char))) << endl;

    string str("-91283472332");
    cout << "string: '-91283472332'  " \
    << "Atoi: " << Atoi(str) << endl;
}
