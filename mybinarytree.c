//------------------------------------------------------------------------
// File Name: mybinarytree.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Mon 02 Oct 2023 10:57:36 CST
// Description:
//------------------------------------------------------------------------

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
#define newtreenode newtreenode_##T
#define DeleteTreeNode(T) void deletetreenode_##T(treenode_##T *node){\
  free(node);\
}
#define Tree(T) typedef struct tree_##T{\
  treenode_##T *root;\
  int size;\
  int (*compare)(const T a, const T b);\
  int (*isempty)(struct tree_##T *this);\
  treenode_##T *(*getroot)(struct tree_##T *tree);\
  void (*insert)(struct tree_##T *this, T val);\
  void (*updateheight)(struct tree_##T *this);\
  int (*balance)(struct tree_##T *this);\
}tree_##T;
#define tree(T) tree_##T
#define Isempty(T) int isempty_##T(tree_##T *this){\
  return this->size == 0;\
}
#define Getroot(T) treenode_##T *getroot_##T(tree_##T *this){\
  return this->root;\
}
#define Updateheight(T) void updateheight_##T(tree_##T *this){\
}
#define Insert(T) void insert_##T(tree_##T *this, T val){\
  treenode_##T *node = (treenode_##T *) malloc(sizeof(treenode_##T));\
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
}
