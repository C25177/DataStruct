//------------------------------------------------------------------------
// File Name: mybinarytree.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Mon 02 Oct 2023 10:57:36 CST
// Description: （平衡）二叉树
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define max(x, y) (x) > (y)? (x) : (y)

#define treenode(T) struct treenode_##T

#define Queue(T) typedef struct queuetreenode_##T{\
  void *start;\
  void *end;\
  struct treenode_##T **ptr;\
  int size;\
  void (*push)(struct queuetreenode_##T *queue, treenode_##T *val);\
  void (*pop)(struct queuetreenode_##T *queue);\
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
#define NewQueue(T) queuetreenode_##T *newqueuetreenode_##T(int size){\
  queuetreenode_##T *queue = (queuetreenode_##T *) malloc(sizeof(queuetreenode_##T));\
  queue->start = malloc(sizeof(treenode_##T *) * size);\
  queue->end = queue->start + sizeof(treenode_##T *) * size;\
  queue->ptr = queue->start;\
  queue->push = pushtreenode_##T;\
  queue->pop = poptreenode_##T;\
  queue->top = toptreenode_##T;\
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

// 这里的 size 函数是深度优点算法
// 广度优先算法需要借助其他数据结构了
#define TreeNode(T) typedef struct treenode_##T{\
  T val;\
  struct treenode_##T *parent;\
  struct treenode_##T *left;\
  struct treenode_##T *right;\
  int height;\
  int (*sizeDFS)(struct treenode_##T *this);\
  int (*sizeBFS)(struct treenode_##T *this);\
  void (*insertl)(struct treenode_##T *this, struct treenode_##T *node);\
  void (*insertr)(struct treenode_##T *this, struct treenode_##T *node);\
  int (*isleaf)(struct treenode_##T *this);\
  int (*isroot)(struct treenode_##T *this);\
}treenode_##T;
#define SizeDFS(T) int sizeDFS_##T(treenode_##T *this){\
  if(!this)return 0;\
  return 1 + sizeDFS_##T(this->left) + sizeDFS_##T(this->right);\
}
#define SizeBFS(T) int sizeBFS_##T(treenode_##T *this){\
  int num = 0;\
  queue(T) *nodequeue = newqueue(T)(32);\
  nodequeue->push(nodequeue, this);\
  while(nodequeue->size){\
    treenode_##T *node = nodequeue->top(nodequeue);\
    nodequeue->pop(nodequeue);\
    if(!node)continue;\
    nodequeue->push(nodequeue, node->left);\
    nodequeue->push(nodequeue, node->right);\
    num++;\
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
#define Isroot(T) int isroot_##T(treenode_##T *this){\
  return !this->parent;\
}
#define NewTreeNode(T) treenode_##T *newtreenode_##T(T val){\
  treenode_##T *node = (treenode_##T *) malloc(sizeof(treenode_##T));\
  node->val = val;\
  node->left = NULL;\
  node->right = NULL;\
  node->parent = NULL;\
  node->height = 0;\
  node->sizeDFS = sizeDFS_##T;\
  node->sizeBFS = sizeBFS_##T;\
  node->insertl = insertl_##T;\
  node->insertr = insertr_##T;\
  node->isleaf = isleaf_##T;\
  node->isroot = isroot_##T;\
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
  void (*balanceBFS)(queue(T) *queue, treenode_##T *node);\
  void (*linkBFS)(queue(T) *queue, treenode_##T *node, int left, int right, int mid);\
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
  if(node == NULL) return 0;\
  int heightleft = heightBFS_##T(node->left);\
  int heightright = heightBFS_##T(node->right);\
  node->height = max(heightleft, heightright) + 1;\
  return node->height;\
}
#define Updateheight(T) void updateheight_##T(tree_##T *this){\
  this->heightBFS(this->root);\
}
#define Insert(T) void insert_##T(tree_##T *this, T val){\
  treenode_##T *node = newtreenode_##T(val);\
  if(!this->root){\
    this->root = node;\
    this->size++;\
    return;\
  }\
  treenode_##T *iterator = this->root;\
  while(iterator){\
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
  this->updateheight(this);\
  this->size++;\
}
#define BalanceBFS(T) void balanceBFS_##T(queue(T) *queue, treenode_##T *node){\
  if(!node)return;\
  balanceBFS_##T(queue, node->left);\
  queue->push(queue, node);\
  balanceBFS_##T(queue, node->right);\
  node->parent = NULL;\
  node->left = NULL;\
  node->right = NULL;\
}
#define LinkBFS(T) void linkBFS_##T(queue(T) *queue, treenode_##T *node, int left, int right, int mid){\
  if(left >= right) return;\
  if(left == mid - 1){\
    node->left = *((treenode_##T **) queue->start + left);\
    node->left->parent = node;\
  }\
  else if(left < mid - 1){\
    int leftmid = (left + mid) >> 1;\
    node->left = *((treenode_##T **) queue->start + leftmid);\
    node->left->parent = node;\
    linkBFS_##T(queue, node->left, left, mid - 1, leftmid);\
  }\
  if(right == mid + 1){\
    node->right = *((treenode_##T **) queue->start + right);\
    node->right->parent = node;\
  }\
  else if(right > mid + 1){\
    int rightmid = (right + mid) >> 1;\
    node->right = *((treenode_##T **) queue->start + rightmid);\
    node->right->parent = node;\
    linkBFS_##T(queue, node->right, mid + 1, right, rightmid);\
  }\
}
#define Balance(T) void balance_##T(tree_##T *this){\
  queue(T) *queue = newqueue(T)(this->root->height * 2);\
  this->balanceBFS(queue, this->root);\
  int size = queue->size - 1;\
  int mid = size >> 1;\
  this->root = *((treenode_##T **) queue->start + mid);\
  this->linkBFS(queue, this->root, 0, size, mid);\
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
#define DEFINETREE(T)  TreeNode(T)\
  DEFINEQUEUE(T)\
  SizeDFS(T)\
  SizeBFS(T)\
  InsertL(T)\
  InsertR(T)\
  Isleaf(T)\
  Isroot(T)\
  NewTreeNode(T)\
  DeleteTreeNode(T)\
  Tree(T)\
  Isempty(T)\
  Getroot(T)\
  HeightBFS(T)\
  Updateheight(T)\
  Insert(T)\
  BalanceBFS(T)\
  LinkBFS(T)\
  Balance(T)\
  NewTree(T)\
  DeleteTree(T)

DEFINETREE(int)
DEFINETREE(char)
DEFINETREE(float)
DEFINETREE(double)

int main(){
  tree(int) *tree = newtree(int)();
  tree->insert(tree, 1);
  tree->insert(tree, 1);
  tree->insert(tree, 2);
  tree->insert(tree, 3);
  tree->insert(tree, -1);
  tree->insert(tree, -2);
  tree->root->sizeDFS(tree->root);
  tree->root->sizeBFS(tree->root);
  deletetree(int)(tree);
}
