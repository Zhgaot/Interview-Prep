#pragma once
#include <iostream>
#include <string.h>
#include <string> // for test

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
  bool operator<(const MoveString &rhs) const;    // for test
  bool operator==(const MoveString &rhs) const;   // for test
  char *get() const;                              // for test

private:
  void set_str_(const char *cstr);

private:
  char *m_str_;
  size_t len_; // string length without '\0'

public:
  static size_t DCtor; // count for "default constructor"
  static size_t Ctor;  // count for "param constructor"
  static size_t CCtor; // count for "deepcopy constructor"
  static size_t DAsgn; // count for "deepcopy assignment"
  static size_t MCtor; // count for "move constructor"
  static size_t MAsgn; // count for "move assignment"
  static size_t Dtor;  // count for "destructor"
};

static size_t DCtor = 0;
static size_t Ctor = 0;
static size_t CCtor = 0;
static size_t DAsgn = 0;
static size_t MCtor = 0;
static size_t MAsgn = 0;
static size_t Dtor = 0;

void MoveString::set_str_(const char *cstr) {
  this->m_str_ = new char[this->len_ + 1];
  strcpy(this->m_str_, cstr); // '\0' also copy
}

// default constructor
MoveString::MoveString() : m_str_(nullptr), len_(0) { ++DCtor; }

// param constructor
MoveString::MoveString(const char *cstr) : len_(strlen(cstr)) {
  ++Ctor;
  this->set_str_(cstr);
}

// deepcopy constructor
MoveString::MoveString(const MoveString &other) : len_(strlen(other.m_str_)) {
  ++CCtor;
  this->set_str_(other.m_str_);
}

// move constructor
MoveString::MoveString(MoveString &&other)
    : m_str_(other.m_str_), len_(other.len_) {
  ++MCtor;
  other.m_str_ = nullptr;
  other.len_ = 0;
}

// deepcopy assignment
MoveString &MoveString::operator=(const MoveString &other) {
  ++DAsgn;
  if (this == &other)
    return *this;
  this->len_ = strlen(other.m_str_);
  if (this->m_str_ != nullptr) {
    delete[] this->m_str_;
    this->m_str_ = nullptr;
  }
  this->set_str_(other.m_str_);
}

// move assignment
MoveString &MoveString::operator=(MoveString &&other) {
  ++MAsgn;
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
  ++Dtor;
  if (this->m_str_ != nullptr) {
    delete[] this->m_str_;
    this->m_str_ = nullptr;
  }
}

// for test
bool MoveString::operator<(const MoveString &rhs) const {
  return std::string(this->m_str_) < std::string(rhs.m_str_);
}

// for test
bool MoveString::operator==(const MoveString &rhs) const {
  return std::string(this->m_str_) == std::string(rhs.m_str_);
}

// for test
char *MoveString::get() const { return this->m_str_; }

std::ostream &operator<<(std::ostream &out, const MoveString &str) {
  out << str.m_str_;
  return out;
}
