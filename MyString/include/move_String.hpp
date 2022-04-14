#pragma once

#include <iostream>
#include <string.h>

class MoveString {
  friend std::ostream &operator<<(std::ostream &out, const MoveString &str);

public:
  MoveString();                                   // default constructor
  MoveString(const char *cstr);                   // param constructor
  MoveString(const MoveString &other);            // deepcopy constructor
  MoveString(MoveString &&other);                 // move constructor
  MoveString &operator=(const MoveString &other); // deepcopy assignment
  MoveString &operator=(MoveString &&other);      // move assignment
  ~MoveString();                                  // destructor

private:
  void set_str_(const char *cstr);

private:
  char *m_str_;
  size_t len_; // string length without '\0'
};

void MoveString::set_str_(const char *cstr) {
  this->m_str_ = new char[this->len_ + 1];
  strcpy(this->m_str_, cstr); // '\0' also copy
}

// default constructor
MoveString::MoveString() : m_str_(nullptr), len_(0) {}

// param constructor
MoveString::MoveString(const char *cstr) : len_(strlen(cstr)) {
  this->set_str_(cstr);
}

// deepcopy constructor
MoveString::MoveString(const MoveString &other) : len_(strlen(other.m_str_)) {
  this->set_str_(other.m_str_);
}

// move constructor
MoveString::MoveString(MoveString &&other)
    : m_str_(other.m_str_), len_(other.len_) {
  other.m_str_ = nullptr; // must break the old pointer-addr link!
  other.len_ = 0;
}

// deepcopy assignment
MoveString &MoveString::operator=(const MoveString &other) {
  if (this == &other)
    return *this;
  this->len_ = strlen(other.m_str_);
  if (this->m_str_ != nullptr) {
    delete[] this->m_str_;
    this->m_str_ = nullptr;
  }
  this->set_str_(other.m_str_);
  return *this;
}

// move assignment
MoveString &MoveString::operator=(MoveString &&other) {
  if (this == &other)
    return *this;
  if (this->m_str_ != nullptr) {
    delete[] this->m_str_;
    this->m_str_ = nullptr;
  }
  this->m_str_ = other.m_str_;
  this->len_ = other.len_;
  other.m_str_ = nullptr;
  other.len_ = 0;
  return *this;
}

// destructor
MoveString::~MoveString() {
  if (this->m_str_ != nullptr) {
    delete[] this->m_str_;
    this->m_str_ = nullptr;
  }
}

std::ostream &operator<<(std::ostream &out, const MoveString &str) {
  out << str.m_str_;
  return out;
}
