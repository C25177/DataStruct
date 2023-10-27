//------------------------------------------------------------------------
// File Name: k-arytree.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Thu 05 Oct 2023 11:35:22 CST
// Description: 有根树
//------------------------------------------------------------------------

#include <stdio.h>
#define treenode(T) struct treenode_##T
#define Queue(T) typedef struct queuetreenode_##T{\
  void *start;\
  void *end;\
  struct treenode_##T **ptr;\
  int size;\
  void (*push)(struct queuetreenode_##T *queue, treenode_##T *val);\
  void (*pop)(struct queuetreenode_##T *queue);\
  void (*merge)(struct queuetreenode_##T *dst, struct queuetreenode_##T *src, int dstbegin, int srcbegin, int srcend);\
  treenode_##T *(*top)(struct queuetreenode_##T *queue);\
}queuetreenode_##T;
#define queue(T) queuetreenode_##T
#define Push(T) void pushtreenode_##T(queuetreenode_##T *queue, struct treenode_##T *val){\
  if((void *) queue->ptr == queue->end){\
    int size = queue->end - queue->start;\
    void *newstart = malloc(2 * size);\
    memcpy(newstart, queue->start, size);\
    free(queue->start);\
    queue->start = newstart;\
    queue->end = queue->start + 2 * size;\
    queue->ptr = queue->start + size;\
  }\
  memcpy(queue->ptr, &val, sizeof(struct treenode_##T *));\
  queue->ptr += 1;\
  queue->size++;\
}
#define Pop(T) void poptreenode_##T(queuetreenode_##T *queue){\
  if((void *) queue->ptr == queue->start) return;\
  memmove(queue->start, queue->start + sizeof(treenode_##T *), queue->end - queue->start - sizeof(treenode_##T *));\
  queue->ptr -= 1;\
  queue->size--;\
}
#define Top(T) treenode_##T *toptreenode_##T(queuetreenode_##T *queue){\
  treenode_##T *treenode = *((treenode_##T **) queue->start);\
  return treenode;\
}
#define Merge(T) void merge_##T(queuetreenode_##T *dst, queuetreenode_##T *src, int dstbegin, int srcbegin, int srcen){\
  int srcsize = src->ptr - (treenode_##T * *) src->start;\
  if(srcbegin >= srcsize){\
    printf("begin index has out of range");\
    return;\
  }\
  if(srcend * sizeof(treenode_##T *) > srcsize){\
    printf("end index has out of range");\
    return;\
  }\
  int dstmaxsize = dst->end - dst->start;\
  int dstsize = (void *) dst->ptr - dst->start;\
  while(dstmaxsize < dstsize + (srcend - srcbegin) * sizeof(treenode_##T *))\
    dstmaxsize << 2;\
  void *newstart = malloc(dstmaxsize);\
  memcpy(newstart, dst->start, dstbegin * sizeof(treenode_##T *));\
  memcpy(newstart + dstbegin * sizeof(treenode_##T *), src->start + srcbegin * sizeof(treenode_##T *), (srcend - srcbegin) * sizeof(treenode_##T *));\
  memcpy(newstart + dstbegin * sizeof(treenode_##T *) + srcsize, dst->start + dstbegin * sizeof(treenode_##T *), (void *) dst->ptr - dst->start - dstbegin * sizeof(treenode_##T *));\
  free(dst->start);\
  dst->start = newstart;\
  dst->end = newstart + dstmaxsize;\
  dst->ptr = newstart + dstsize + (srcend - srcbegin) * sizeof(treenode_##T *);\
}
#define NewQueue(T) queuetreenode_##T *newqueuetreenode_##T(int size){\
  queuetreenode_##T *queue = (queuetreenode_##T *) malloc(sizeof(queuetreenode_##T));\
  queue->start = malloc(sizeof(treenode_##T *) * size);\
  queue->end = queue->start + sizeof(treenode_##T *) * size;\
  queue->ptr = queue->start;\
  queue->push = pushtreenode_##T;\
  queue->pop = poptreenode_##T;\
  queue->top = toptreenode_##T;\
  queue->merge = merge_##T;\
}
#define newqueue(T) newqueuetreenode_##T
#define DeleteQueue(T) void deletequeuetreenode_##T(queuetreenode_##T *queue){\
  free(queue->start);\
  free(queue);\
}
#define deletequeue(T) deletequeuetreenode_##T
#define DEFINEQUEUE(T) Queue(T)\
  Push(T)\
  Pop(T)\
  Top(T)\
  NewQueue(T)\
  DeleteQueue(T)
#define TreeNode(T) typedef struct treenode_##T{\
  treenode_##T *parent;\
  queuetreenode_##T *children;\
  void (*insert)(treenode_##T *this, treenode_##T *node);\
  void (*dfs)(treenode_##T *this, void (*func)(treenode_##T *node));\
  void (*bfs)(treenode_##T *this, void (*func)(treenode_##T *node));\
  int (*isleaf)(struct treenode_##T *this);\
  int (*isroot)(struct treenode_##T *this);\
}treenode_##T;
#define nodeInsert(T) void nodeinsert_##T(treenode_##T *this, void (*func)(treenode_##T *node)){\
  children->push(node);\
}
#define NodeDFS(T) void nodedfs_##T(treenode_##T *this, void (*func)(T val)){\
  if(!this)return;\
  func(this);\
  nodedfs_##T(this->left, func);\
  nodedfs_##T(this->right, func);\
}
#define NodeBFS(T) void nodebfs_##T(treenode_##T *this, void (*func)(treenode_##T *node)){\
  queue(T) *nodequeue = newqueue(T)(32);\
  nodequeue->push(this);\
  while(nodequeue->size){\
    treenode_##T *node = nodequeue->top(nodequeue);\
    nodequeue->pop(nodequeue);\
    if(!node)continue;\
    func(node);\
    nodequeue->merge(nodequeue, this->children, nodequeue->ptr - (treenode_##T **) node->start, 0, this->children->ptr - (treenode_##T **) this->children->start);\
  }\
}
#define Isleaf(T) int isleaf_##T(treenode_##T *this){\
  return this->children->ptr == this->children->start;\
}
#define Isroot(T) int isroot_##T(treenode_##T *this){\
  return !this->parent;\
}
#define Tree(T) typedef struct tree_##T{\
  treenode_##T *root;\
  int size;\
}tree_##T;
#define tree(T) tree_##T
#define NewTree(T) tree_##T *newtree_##T(){\
  tree_##T *tree = (tree_##T *) malloc(sizeof(tree_##T));\
  tree->root = NULL;\
  tree->size = 0;\
  return tree;\
}