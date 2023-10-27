//------------------------------------------------------------------------
// File Name: mylist.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Mon 25 Sep 2023 20:34:40 CST
// Description: 单向链表 insert remove new delete
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define ListNode(T) typedef struct listnode_##T{\
  struct listnode_##T* next;\
  T val;\
}listnode_##T;
#define listnode(T) listnode_##T
#define NewListNode(T) listnode_##T* newListNode_##T(T val){\
  listnode_##T *node = (listnode_##T *) malloc(sizeof(listnode_##T));\
  node->next = NULL;\
  node->val = val;\
  return node;\
}
#define newListNode(T) newListNode_##T
#define DeleteListNode(T) void deleteListNode_##T(listnode_##T *node){\
  free(node);\
}
#define deleteListNode(T) deleteListNode_##T
#define LinkedList(T) typedef struct linkedlist_##T{\
  struct listnode_##T *head;\
  struct listnode_##T *tail;\
  int length;\
  T val;\
  void (*insert)(struct linkedlist_##T *list, int index, listnode_##T* node);\
  void (*remove)(struct linkedlist_##T *list, int index);\
  void (*merge)(struct linkedlist_##T *dst, struct linkedlist_##T *src, int dstbegin, int srcbegin, int srcend);\
  void (*clear)(struct linkedlist_##T *list);\
  int (*isempty)(struct linkedlist_##T *list);\
}linkedlist_##T;
#define linkedlist(T) linkedlist_##T
// insert at the front of index node
#define Insert(T) void insert_##T(linkedlist_##T* list, int index, listnode_##T* node){\
  listnode_##T *iterator = list->head;\
  while(iterator->next != list->tail && index--){\
    iterator = iterator->next;\
  }\
  if(index > 0)printf("index has out of range, but will insert tail\n");\
  node->next = iterator->next;\
  list->length++;\
  iterator->next = node;\
}
// remove the next of iterator
#define Remove(T) void remove_##T(linkedlist_##T* list, int index){\
  listnode_##T *iterator = list->head;\
  if(!list->length){\
    printf("this list is empty, can't remove node\n");\
    return;\
  }\
  index--;\
  while(iterator->next != list->tail && index-- > 0){\
    iterator = iterator->next;\
  }\
  if(index != 0){\
    printf("index has out of range, can't remove node\n");\
    return;\
  }\
  listnode_##T *node = iterator->next;\
  iterator->next = iterator->next->next;\
  free(node);\
  list->length--;\
}
// 都是以节点之后开始的
// [srcbegin, srcend) 节点id从1开始
#define Merge(T) void merge_##T(linkedlist_##T *dst, struct linkedlist_##T *src, int dstbegin, int srcbegin, int srcend){\
  listnode_##T *dstit = dst->head;\
  listnode_##T *srcit = src->head;\
  while(dstit->next != dst->tail && dstbegin-- > 0) dstit = dstit->next;\
  if(dstbegin > 0) printf("dstbegin has out of range, so merge begin at the tail\n");\
  listnode_##T *copybegin;\
  listnode_##T *copyend;\
  int copylength = 0;\
  while(srcit->next != src->tail){\
    srcit = srcit->next;\
    srcbegin--;\
    srcend--;\
    if(srcend <= 0)break;\
    if(srcbegin == 0){\
      copybegin = newListNode(T)(srcit->val);\
      copyend = copybegin;\
      copylength++;\
    }\
    else if(srcbegin < 0){\
      listnode_##T *node = newListNode(T)(srcit->val);\
      copyend->next = node;\
      copyend = copyend->next;\
      copylength++;\
    }\
  }\
  if(srcbegin > 0){\
    printf("srcbegin has out of range, so stop merge\n");\
    return;\
  }\
  copyend->next = dstit->next;\
  dstit->next = copybegin;\
  dst->length += copylength;\
}
#define Clear(T) void clear_##T(linkedlist_##T *list){\
  listnode_##T *it = list->head;\
  while(it->next != list->tail){\
    listnode_##T *deletenode = it->next;\
    it->next = it->next->next;\
    free(deletenode);\
  }\
  list->length = 0;\
}
#define Isempty(T) int isempty_##T(linkedlist_##T *list){\
  return list->head->next == list->tail;\
}
#define NewLinkedList(T) linkedlist_##T *newLinkedList_##T(){\
  linkedlist_##T *list = (linkedlist_##T *)malloc(sizeof(linkedlist_##T));\
  list->head = (listnode_##T *)malloc(sizeof(listnode_##T));\
  list->head->val = 0;\
  list->tail = (listnode_##T *)malloc(sizeof(listnode_##T));\
  list->tail->val = 0;\
  list->length = 0;\
  list->head->next = list->tail;\
  list->tail->next = NULL;\
  list->insert = insert_##T;\
  list->remove = remove_##T;\
  list->merge = merge_##T;\
  list->clear = clear_##T;\
  list->isempty = isempty_##T;\
  return list;\
}
#define newLinkedList(T) newLinkedList_##T()
#define DeleteLinkedList(T) void deleteLinkList_##T(linkedlist_##T *list){\
  listnode_##T *iterator = list->head;\
  while(iterator){\
    listnode_##T *deletenode = iterator;\
    iterator = iterator->next;\
    free(deletenode);\
  }\
  free(list);\
}
#define deleteLinkedList(T) deleteLinkList_##T
#define DEFINELIST(T) ListNode(T)\
  NewListNode(T)\
  DeleteListNode(T)\
  LinkedList(T)\
  Insert(T)\
  Remove(T)\
  Merge(T)\
  Clear(T)\
  Isempty(T)\
  NewLinkedList(T)\
  DeleteLinkedList(T)

DEFINELIST(int)
DEFINELIST(char)
DEFINELIST(float)
DEFINELIST(double)

int main(){
  linkedlist(int) *list = newLinkedList(int);
  linkedlist(int) *list1 = newLinkedList(int);
  listnode(int) *node = newListNode(int)(1);
  listnode(int) *node1 = newListNode(int)(2);
  list->insert(list, 0, node);
  list->insert(list, 1, node1);
  listnode(int) *node2 = newListNode(int)(3);
  listnode(int) *node3 = newListNode(int)(4);
  list1->insert(list1, 0, node2);
  list1->insert(list1, 1, node3);
  // while(iterator != list1->tail){
  //   printf("%d\n", iterator->val);
  //   iterator = iterator->next;
  // }
  list->merge(list, list1, 1, 1, 3);
  listnode(int) *iterator = list->head->next;
  while(iterator != list->tail){
    printf("%d\n", iterator->val);
    iterator = iterator->next;
  }
  list->remove(list, 0);
  iterator = list->head->next;
  while(iterator != list->tail){
    printf("%d\n", iterator->val);
    iterator = iterator->next;
  }
  deleteLinkedList(int)(list);
}
