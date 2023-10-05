//------------------------------------------------------------------------
// File Name: mybinarytree.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Mon 02 Oct 2023 10:57:36 CST
// Description:
//------------------------------------------------------------------------

#define TreeNode(T) typedef struct treenode_##T{\
  T val;\
  struct treenode_##T *parent;\
  struct treenode_##T *left;\
  struct treenode_##T *right;\
  int leftdegree;\
  int rightdegree;\
}treenode_##T;
#define treenode(T) treenode_##T
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
#define Tree(T) typedef struct tree_##T{\
  treenode_##T *root;\
  void (*push)(struct tree_##T *tree, treenode_##T *node);\
  void (*pop)(struct tree_##T *tree);\
  void (*bfs)(struct treenode_##T *node, T target);\
  void (*dfs)(struct treenode_##T *node, T target);\
  int (*maxdepth)(struct tree_##T *tree);\
}tree_##T;
Tree(int)
Tree(char)
Tree(float)
Tree(double)
#define tree(T) tree_##T
#define Push(T) void push(tree_##T *tree, T val){\
  treenode_##T *node = newtreenode_##T(val);\
  treenode_##T *iterator = tree->root;\
  if(iterator->val == node->val)return;\
  while((node->val > iterator->val && iterator->right) || (node->val < iterator->val && iterator->right)){\
  


