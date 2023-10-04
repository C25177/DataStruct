//------------------------------------------------------------------------
// File Name: mybinarytree.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Mon 02 Oct 2023 10:57:36 CST
// Description:
//------------------------------------------------------------------------

#define TreeNode(T) typedef struct treenode_##T{\
  T val;\
  int degree;\
  struct treenode_##T *left;\
  struct treenode_##T *right;\
}treenode_##T;
TreeNode(int)
TreeNode(char)
TreeNode(float)
TreeNode(double)
#define treenode(T) treenode_##T

#define NewTreeNode(T) treenode_##T *newtreenode_##T(T val){\
  treenode_##T *node = (treenode_##T *) malloc(sizeof(treenode_##T));\
  node->val = val;\
  node->degree = 0;\
  node->left = NULL;\
  node->right = NULL;\
  return node;\
}
NewTreeNode(int)
NewTreeNode(char)
NewTreeNode(float)
NewTreeNode(double)
#define newtreenode newtreenode_##T

#define Tree(T) typedef struct tree_##T{\
  treenode_##T *root;\
  void (*push)(struct tree_##T *tree, treenode_##T *node);\
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


