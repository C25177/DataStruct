//----
// @file mymap.cpp
// @author mask <beloved25177@126.com>
// @brief
// @version 1.0
// @date 2024-04-16
//
// @copyright Copyright (c) 2024
//
//----

#include <iostream>
#include <queue>

typedef unsigned short m_size_t;

template<typename FIRST, typename SECOND>
class MapNode {
private:
  m_size_t nnum;
  m_size_t maxnnum;
  m_size_t id;

public:
  MapNode **neighbour;
  FIRST first;
  SECOND second;
  MapNode(const m_size_t &id = 0, const FIRST &_f = 0, const SECOND &_s = 0) : first(_f), second(_s) {
    maxnnum = 16;
    neighbour = new MapNode[16];
    for (int i = 0; i < 16; ++i)
      neighbour[i] = nullptr;
  }
  ~MapNode() {
    delete neighbour;
  }
  std::ostream &operator<<(std::ostream &_os) {
    std::cout << "key: " << first << "\tval" << second << std::endl;
    return _os;
  }
  void insertNeighbour(const MapNode *_n) {
    if (nnum == maxnnum) {
      MapNode **newneighbour = new MapNode *[maxnnum << 1];
      memcpy(newneighbour, neighbour, sizeof(MapNode *) * nnum);
      delete neighbour;
      neighbour = newneighbour;
      maxnnum <<= 1;
    }
    neighbour[nnum++] = _n;
  }
};

template<typename KEY, typename VALUE>
class Map {
  MapNode<KEY, VALUE> **nodes;
  m_size_t nnum;
  m_size_t maxnnum;
  bool DFS_t(MapNode<KEY, VALUE> *_n, const int &_key, bool *visited) {
    if (_n == nullptr || visited[_n->id]) return false;
    MapNode<KEY, VALUE> *node = *(_n->neighbour);
    visited[node->id] = true;
    if (node->key == _key) return true;
    while (node) {
      if (DFS_t(node++, _key, visited)) return true;
    }
    return false;
  }

public:
  Map() {
    nodes = new MapNode<KEY, VALUE>[16];
    for (int i = 0; i < 16; ++i)
      nodes[i] = nullptr;
    maxnnum = 16;
  }
  ~Map() {
    delete nodes;
  }
  bool insert(const KEY &_key, const VALUE &_val) {
    if (nnum == maxnnum) {
      MapNode<KEY, VALUE> **newnodes = new MapNode<KEY, VALUE> *[maxnnum << 1];
      memcpy(newnodes, nodes, sizeof(MapNode<KEY, VALUE> *) * nnum);
      delete nodes;
      nodes = newnodes;
      maxnnum <<= 1;
    }
    nodes[nnum] = new MapNode<KEY, VALUE>(nnum, _key, _val);
    ++nnum;
    return true;
  }
  bool BFS(const int &_key) {
    bool visited[nnum] = {false};
    std::queue<MapNode<KEY, VALUE> *> q;
    for (int i = 0; i < nnum; ++i)
      q.push(nodes[i]);
    while (!q.empty()) {
      MapNode<KEY, VALUE> *node = q.front();
      q.pop();
      if (node->key == _key) return true;
      for (int i = 0; i < node->nnum; ++i)
        q.push(node.neighbour[i]);
    }
    return false;
  }
  bool DFS(const int &key) {
    bool visited[nnum] = {false};
    for (int i = 0; i < nnum; ++i) {
      if (!visited[nodes[i]->id] && DFS_t(nodes[i], key, visited)) return true;
    }
    return false;
  }
  VALUE operator[](const int &_key) {
    bool visited[nnum] = {false};
    std::queue<MapNode<KEY, VALUE> *> q;
    for (int i = 0; i < nnum; ++i)
      q.push(nodes[i]);
    while (!q.empty()) {
      MapNode<KEY, VALUE> *node = q.front();
      q.pop();
      if (node->key == _key) return node->val;
      for (int i = 0; i < node->nnum; ++i)
        q.push(node.neighbour[i]);
    }
    return nullptr;
  }
};

int main(int argc, char *argv[]) {
}