//------------------------------------------------------------------------
// File Name: k-arytree.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Thu 05 Oct 2023 11:35:22 CST
// Description: 有根树
//------------------------------------------------------------------------

#include <stdio.h>

#define TreeNode(T) typedef struct treenode_##T{\
  treenode_##T *parent;\
  treenode_##T *children;\
  int childrennums;\
}treenode_##T;
#define treenode(T) treenode_##T
#define Tree(T) typedef struct tree_##T{\
  treenode_##T *root;\
  int size;\
}
