//----
// @file directionary.cpp
// @author mask <beloved25177@126.com>
// @brief
// @version 1.0
// @date 2024-04-16
//
// @copyright Copyright (c) 2024
//
//----


typedef unsigned short d_size_t;

template<typename _KEY, typename _VAL>
struct DirectionaryNode {
  _KEY key;
  _VAL val;
  DirectionaryNode(const _KEY &_k, const _VAL &_v) {
    key = _k;
    val = _v;
  }
};

template<typename _KEY, typename _VAL>
class Directionary {
  d_size_t sz;
  d_size_t max_sz;
  DirectionaryNode<_KEY, _VAL> *d;

public:
  Directionary() {
    d = new DirectionaryNode<_KEY, _VAL>[16];
  }
  void put(const _KEY &_key, const _VAL &_val) {
    DirectionaryNode<_KEY, _VAL> node = get(_key);
    if (node == nullptr)
      d[sz++] = DirectionaryNode<_KEY, _VAL>(_key, _val);
    else
      d[sz++] = _val;
  }
  DirectionaryNode<_KEY, _VAL> get(const _KEY &key) {
    for (int i = 0; i < sz; ++i) {
      if (d[i].key == key)
        return d[i];
    }
    return nullptr;
  }
  _VAL operator[](const _KEY &key) {
    for (int i = 0; i < sz; ++i) {
      if (d[i].key == key)
        return d[i].val;
    }
    return nullptr;
  }
};

int main(int argc, char const *argv[]) {
  return 0;
}
