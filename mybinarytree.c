//------------------------------------------------------------------------
// File Name: mybinarytree.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Mon 02 Oct 2023 10:57:36 CST
// Description:
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define Queue(T) typedef struct queue_##T{\
  void* start;\
  void* end;\
  T* ptr;\
  int size;\
  void (*push)(struct queue_##T *queue, T val);\
  void (*pop)(struct queue_##T *queue);\
  T (*top)(struct queue_##T* queue);\
}queue_##T;
#define queue(T) queue_##T
#define Push(T) void push_##T(queue_##T *queue, T val){\
  if(queue->ptr == queue->end){\
    T *newstart = (T *) malloc(2 *  queue->size);\
    memcpy(newstart, queue->start, queue->size);\
    free(queue->start);\
    queue->start = newstart;\
    queue->end = queue->start + queue->size * 2;\
    queue->ptr = queue->start + queue->size;\
    queue->size = 2 * queue->size;\
  }\
  memmove(queue->ptr, &val, sizeof(T));\
  queue->ptr += 1;\
}
#define Pop(T) void pop_##T(queue_##T *queue){\
  if((void *)queue->ptr == queue->start)return;\
  memmove(queue->start, queue->start + sizeof(T), queue->end - queue ->start -  sizeof(T));\
  queue->ptr -=1;\
}
#define Top(T) T top_##T(queue_##T *queue){\
  T data;\
  if((void *)queue->ptr - queue->start < sizeof(T))return 0;\
  memmove(&data, queue->start, sizeof(T));\
  return data;\
}
#define NewQueue(T) queue_##T *newqueue_##T(){\
  queue_##T *queue = (queue_##T *) malloc(sizeof(queue_##T));\
  queue->start = malloc(sizeof(T) * 32);\
  queue->size = 32 * sizeof(T);\
  queue->end = queue->start + queue->size;\
  queue->ptr = queue->start;\
  queue->push = push_##T;\
  queue->pop = pop_##T;\
  queue->top = top_##T;\
  return queue;\
}
#define newqueue(T) newqueue_##T
#define DeleteQueue(T) void deletequeue_##T(queue_##T* queue){\
  free(queue->start);\
  free(queue);\
}
#define deletequeue(T) deletequeue_##T
#define DEFINEQUEUE(T) Queue(T)\
  Push(T)\
  Pop(T)\
  Top(T)\
  NewQueue(T)\
  DeleteQueue(T)

// 这里的 size 函数是深度优点算法
// 广度优先算法需要借助其他数据结构了
#define TreeNode(T) typedef struct treenode_##T{\
  T val;\
  struct treenode_##T *parent;\
  struct treenode_##T *left;\
  struct treenode_##T *right;\
  int height;\
  int (*sizeDFS)(struct treenode_##T *this);\
  int (*sizeBFS)(struct treenode_##T *list, int num);\
  void (*insertl)(struct treenode_##T *this, struct treenode_##T *node);\
  void (*insertr)(struct treenode_##T *this, struct treenode_##T *node);\
  int (*isleaf)(struct treenode_##T *this);\
  int (*isroot)(struct treenode_##T *this);\
}treenode_##T;
#define treenode(T) treenode_##T
#define SizeDFS(T) int sizeDFS_##T(treenode_##T *this){\
  if(!this)return 0;\
  return 1 + sizeDFS_##T(this->left) + sizeDFS_##T(this->right);\
}
#define SizeBFS(T) int sizeDFS_##T(queue(treenode_##T) *nodequeue, int num){\
  int num = 0;\
  while(nodequeue->size){\
    treenode_##T node = nodequeue->top(nodequeue);\
    if(!node)continue;\
    nodequeue->pop(nodequeue);\
    nodequeue->push(node.left);\
    nodequeue->push(node.right);\
    n++;\
  }\
  return num;\
}
#define InsertL(T) void insertl_##T(treenode_##T *this, treenode_##T *node){\
  this->left = node;\
  this->height = (1 + node->height > this->height? 1 + node->height : this->height);\
  node->parent = this;\
}
#define InsertR(T) void insertr_##T(treenode_##T *this, treenode_##T *node){\
  this->right = node;\
  this->height = (1 + node->height > this->height? 1 + node->height : this->height);\
  node->parent = this;\
}
#define Isleaf(T) int isleaf_##T(treenode_##T *this){\
  return !this->right && !this->left;\
}
#define Isroot(T) int isroot_##T(treenode_##t *this){\
  return !this->parent;\
}
#define NewTreeNode(T) treenode_##T *newtreenode_##T(T val){\
  treenode_##T *node = (treenode_##T *) malloc(sizeof(treenode_##T));\
  node->val = val;\
  node->left = NULL;\
  node->right = NULL;\
  node->parent = NULL;\
  node=>leftdegree = 0;\
  node=>rightdegree = 0;\
  return node;\
}
#define DeleteTreeNode(T) void deletetreenode_##T(treenode_##T *node){\
  if(!node)return;\
  deletetreenode_##T(node->left);\
  deletetreenode_##T(node->right);\
  free(node);\
}
#define newtreenode newtreenode_##T
#define deletetreenode(T) deletetreenode_##T
#define Tree(T) typedef struct tree_##T{\
  treenode_##T *root;\
  int size;\
  int (*compare)(const T a, const T b);\
  int (*isempty)(struct tree_##T *this);\
  treenode_##T *(*getroot)(struct tree_##T *tree);\
  void (*insert)(struct tree_##T *this, T val);\
  int (*heightBFS)(treenode_##T *node);\
  void (*updateheight)(struct tree_##T *this);\
  void (*balanceBFS)(queue(treenode_##T *) *queue, treenode_##T *node);\
  void (*linkBFS)(queue(treenode_##T *) *queue, treenode_##T *node, int left, int right);\
  void (*balance)(struct tree_##T *this);\
}tree_##T;
#define tree(T) tree_##T
#define Isempty(T) int isempty_##T(tree_##T *this){\
  return this->size == 0;\
}
#define Getroot(T) treenode_##T *getroot_##T(tree_##T *this){\
  return this->root;\
}
#define HeightBFS(T) int heightBFS_##T(treenode_##T *node){\
  if(!node)return 0;\
  node->height = max(heightBFS_##T(node->left), heightBFS_##T(node->right)) + 1;\
  return node->height;\
}
#define Updateheight(T) void updateheight_##T(tree_##T *this){\
  this->heightBFS(this->node);\
}
#define Insert(T) void insert_##T(tree_##T *this, T val){\
  treenode_##T *node = (treenode_##T *) malloc(sizeof(treenode_##T));\
  if(!this->root){\
    root = node;\
    return;\
  }\
  treenode_##T *iterator = this->root;\
  while(iterator->left || iterator->right){\
    if(iterator->val == val){\
      printf("this tree has a same val, so can't insert\n");\
      return;\
    }\
    if(val < iterator->val){\
      if(!iterator->left){\
        iterator->left = node;\
        break;\
      }\
      iterator = iterator->left;\
    }\
    if(val > iterator->val){\
      if(!iterator->right){\
        iterator->right = node;\
        break;\
      }\
      iterator = iterator->right;\
    }\
  }\
  this->balance(this);\
}
#define BalanceBFS(T) void balanceBFS_##T(queue(treenode_##T *) *queue, treenode_##T *node){\
  if(!node)return;\
  balanceBFS_##T(queue, node->left);\
  queue->push(node);\
  balanceBFS_##T(queue, node->right);\
}
#define LinkBFS(T) void linkBFS_##T(queue(treenode_##T *) *queue, treenode_##T *node, int left, int right, int mid){\
  if(left == right) return;\
  int leftmid = (left + mid) >> 2;\
  int rightmid = (right + mid) >> 2;\
  if(left < mid){\
    node->left = *((treenode_##T **) queue->start + leftmid);\
    LinkBFS_##T(queue, node->left, left, mid - 1, leftmid);\
  }\
  if(right > mid){\
    node->right = *((treenode_##T **) queue->start + rightmid);\
    LinkBFS_##T(queue, node->right, mid + 1, right, rightmid);\
  }\
}
#define Balance(T) void balance_##T(tree_##T *this){\
  queue(treenode_##T *) *queue = newqueue(treenode_##T *)(this->root->height * 2);\
  this->balanceBFS(queue, this->root);\
  int size = queue->size - 1;\
  int mid = size >> 1;\
  this->root = *((treenode_##T **) queue->start + mid);\
  linkBFS_##T(queue, this->root, 0, size, mid);\
}
#define NewTree(T) tree_##T *newtree_##T(){\
  tree_##T *tree = (tree_##T *) malloc(sizeof(tree_##T));\
  tree->root = NULL;\
  tree->size = 0;\
  tree->isempty = isempty_##T;\
  tree->getroot = getroot_##T;\
  tree->insert = insert_##T;\
  tree->heightBFS = heightBFS_##T;\
  tree->updateheight = updateheight_##T;\
  tree->balanceBFS = balanceBFS_##T;\
  tree->linkBFS = linkBFS_##T;\
  tree->balance = balance_##T;\
  return tree;\
}
#define DeleteTree(T) void deletetree_##T(tree_##T *tree){\
  deletetreenode_##T(tree->root);\
  free(tree);\
}
#define newtree(T) newtree_##T
#define deletetree(T) deletetree_##T
#define DEFINETREE(T) Tree(T)\
  Isempty(T)\
  Getroot(T)\
  HeightBFS(T)\
  Updateheight(T)\
  Insert(T)\
  BalanceBFS(T)\
  LinkBFS(T)\
  Balance(T)\
  NewTree(T)\
  Deletetree(T)