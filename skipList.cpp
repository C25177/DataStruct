#include <iostream>

#define MAXLEVEL 16

class Node {
public:
  int key;
  Node **next;
  int deep;
  Node(const int &_d, const int &_k = 0) : key(_k), deep(_d) {
    next = (Node **) malloc(_d * sizeof(Node *));
    for (int i = 0; i < _d; ++i)
      next[i] = nullptr;
  }
  ~Node() { free(next); };
};


class SkipList {
  // 最大层数
  unsigned short maxlevel;
  Node *head;

  int random() {
    return rand() & 0x1;
  }

public:
  SkipList() : head(new Node(MAXLEVEL)), maxlevel(MAXLEVEL){};
  ~SkipList() {
    delete head;
  }
  Node *search(int _k) {
    Node *p = head;
    Node *q = nullptr;
    for (int i = maxlevel - 1; i >= 0; --i) {
      while (p->next[i] && (q = p->next[i]) && q->key < _k) {
        p = q;
      }
      if (q && q->key == _k) return q;
    }
    return nullptr;
  }
  void insert(int _k) {
    Node *p = head;
    Node *q = nullptr;
    int new_deep = 1;
    Node *n = new Node(new_deep, _k);
    while (random() && new_deep <= maxlevel)
      new_deep++;
    for (int i = maxlevel - 1; i >= 0; --i) {
      while (p->next[i] && (q = p->next[i]) && q->key < _k) {
        p = q;
      }
      if (q && q->key == _k) {
        delete n;
        return;
      }
      if (i < new_deep) {
        n->next[i] = p->next[i];
        p->next[i] = n;
      }
    }
  }
  void remove(int _k) {
    Node *p = head;
    Node *q = nullptr;
    for (int i = maxlevel - 1; i >= 0; --i) {
      while (p->next[i] && (q = p->next[i]) && q->key < _k) {
        p = q;
      }
      if (q && q->key == _k) {
        p->next[i] = q->next[i];
      }
    }
    delete q;
  }
  void show() {
    Node *q = head->next[0];
    std::cout << "show: ";
    while (q) {
      std::cout << q->key;
      q = q->next[0];
    }
    std::cout << std::endl;
  }
};

int main(int argc, char const *argv[]) {
  SkipList *sl = new SkipList();
  sl->insert(0);
  sl->insert(1);
  sl->show();
  std::cout << sl->search(0)->key << std::endl;
  sl->remove(0);
  sl->show();
  delete sl;
  return 0;
}
