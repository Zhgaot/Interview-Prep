#pragma once

#include <iostream>
#include <string.h>

class String {
  // friend std::ostream &operator<<(std::ostream &out, const String &str);

public:
  String(const char *cstr = nullptr);
  String(const String &other);
  String &operator=(const String &other);
  ~String();
  char *get_c_str() const;

private:
  char *m_str_;
};

String::String(const char *cstr) {
  if (cstr != nullptr) {
    this->m_str_ = new char[strlen(cstr) + 1];
    strcpy(this->m_str_, cstr); // '\0' also copy
  } else {
    this->m_str_ = new char[1];
    *this->m_str_ = '\0';
  }
}

// Deepcopy
String::String(const String &other) {
  this->m_str_ = new char[strlen(other.m_str_) + 1];
  strcpy(this->m_str_, other.m_str_); // '\0' also copy
}

// Deepcopy
String &String::operator=(const String &other) {
  if (this == &other) { // avoid self-copy
    return *this;
  }
  if (this->m_str_ != nullptr) {
    delete[] this->m_str_;
    this->m_str_ = nullptr;
  }
  this->m_str_ = new char[strlen(other.m_str_) + 1];
  strcpy(this->m_str_, other.m_str_); // '\0' also copy
  return *this;
}

String::~String() {
  if (this->m_str_ != nullptr) {
    delete[] this->m_str_;
    this->m_str_ = nullptr;
  }
}

char *String::get_c_str() const { return this->m_str_; }

std::ostream &operator<<(std::ostream &out, const String &str) {
  out << str.get_c_str();
  return out;
}
