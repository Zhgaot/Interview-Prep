#include "String.hpp"
#include "move_String.hpp"
#include <iostream>
using namespace std;

void test_String() {
  String str1("Hello World!");
  cout << "str1: " << str1 << endl;
  String str2(str1);
  cout << "str2: " << str2 << endl;
  String str3;
  str3 = str2;
  str2 = str3;
  cout << "str3: " << str3 << endl;
  String str4("Aloha!");
  str2 = str4;
  cout << "str2 = str4 = " << str2 << endl;
}

void test_MoveString() {
  MoveString str1("Hello World!");
  cout << "str1: " << str1 << endl;
  MoveString str2(str1);
  cout << "str2: " << str2 << endl;
  MoveString str3;
  str3 = str2;
  str2 = str3;
  cout << "str3: " << str3 << endl;
  MoveString str4("Aloha!");
  str2 = str4;
  cout << "str2 = str4 = " << str2 << endl;
}

int main() {
  test_MoveString();
  return 0;
}
