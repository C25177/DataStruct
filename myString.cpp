//----
// @file myString.cpp
// @author mask <beloved25177@126.com>
// @brief
// @version 1.0
// @date 2024-04-16
//
// @copyright Copyright (c) 2024
//
//----

#include <iostream>

typedef unsigned short s_size_t;

class String {
  s_size_t len;
  s_size_t max_len;
  char *p;

public:
  String(const s_size_t &_n = 16) {
    p = new char[_n];
    len = _n;
  }
  void operator=(char *_s) {
    char *i = _s;
    s_size_t sz = 0;
    while (*i)
      ++sz;
    if (sz > max_len) {
      delete[] p;
      max_len = sz << 1;
      p = new char[max_len];
    }
    memcpy(p, _s, sz);
    len = sz;
  }
  void operator=(const String &_s) {
    char *i = _s.p;
    if (_s.len > max_len) {
      delete[] p;
      max_len = _s.len << 1;
      p = new char[max_len];
    }
    memcpy(p, _s.p, _s.len);
  }
  char charat(const s_size_t &_n) {
    return p[_n];
  }
  String substr(const s_size_t &_b, const s_size_t &_n) {
    s_size_t sz = _n;
    if (_b + _n > len)
      sz = len - _b;
    String s = String(sz << 1);
    memcpy(s.p, (p + _b), sz);
    return s;
  }
  void concat(const String &_s) {
    if (_s.len + len > max_len) {
      max_len = (_s.len + len) << 1;
      char *newp = new char[max_len];
      memcpy(newp, p, len);
      delete[] p;
      p = newp;
    }
    len += _s.len;
    memcpy((p + len), _s.p, _s.len);
  }
  bool operator==(const String &_s) {
    if (len != _s.len) return false;
    for (int i = 0; i < len; ++i)
      if (p[i] != _s.p[i]) return false;
    return true;
  }
  s_size_t length() {
    return len;
  }
  void append(const char &_c) {
    if (len + 1 > max_len) {
      max_len <<= 1;
      char *newp = new char[max_len];
      memcpy(newp, p, len);
      delete[] p;
      p = newp;
    }
    p[len++] = _c;
  }
  char pop_back() {
    if (len == 0) return 0;
    return p[--len];
  }
};

int main(int argc, char const *argv[]) {
  return 0;
}
