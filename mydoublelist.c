//------------------------------------------------------------------------
// File Name: mydoublelist.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Thu 28 Sep 2023 14:34:59 CST
// Description: 双向链表
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define ListNode(T)             \
  typedef struct ListNode_##T { \
    struct ListNode_##T *pre;   \
    struct ListNode_##T *next;  \
    T val;                      \
  } ListNode_##T;
#define listnode(T) ListNode_##T
#define NewListNode(T)                                                  \
  ListNode_##T *newListNode_##T(T val) {                                \
    ListNode_##T *node = (ListNode_##T *) malloc(sizeof(ListNode_##T)); \
    node->next = NULL;                                                  \
    node->pre = NULL;                                                   \
    node->val = val;                                                    \
    return node;                                                        \
  }
#define DeleteListNode(T)                       \
  void deleteListNode_##T(ListNode_##T *node) { \
    free(node);                                 \
  }
#define newListNode(T) newListNode_##T
#define deleteListNode(T) deleteListNode_##T
#define DoubleList(T)                                                                                               \
  typedef struct doublelist_##T {                                                                                   \
    ListNode_##T *head;                                                                                             \
    ListNode_##T *tail;                                                                                             \
    int length;                                                                                                     \
    void (*insert)(struct doublelist_##T * doublelist, int index, ListNode_##T *node);                              \
    void (*remove)(struct doublelist_##T * doublelist, int index);                                                  \
    void (*merge)(struct doublelist_##T * dst, struct doublelist_##T *src, int dstbegin, int srcbegin, int srcend); \
    void (*clear)(struct doublelist_##T * list);                                                                    \
    void (*isempty)(struct doublelist_##T * list);                                                                  \
  } doublelist_##T;
#define doublelist(T) doublelist_##T
#define Insert(T)                                                              \
  void insert_##T(doublelist_##T *doublelist, int index, ListNode_##T *node) { \
    ListNode_##T *iterator = doublelist->head;                                 \
    while (iterator != doublelist->tail && index--) {                          \
      iterator = iterator->next;                                               \
    }                                                                          \
    if (!index)                                                                \
      printf("index has out of range and will insert front of tail\n");        \
    node->next = iterator->next;                                               \
    node->pre = iterator;                                                      \
    iterator->next->pre = node;                                                \
    iterator->next = node;                                                     \
    doublelist->length++;                                                      \
  }
#define Remove(T)                                                \
  void remove_##T(doublelist_##T *doublelist, int index) {       \
    ListNode_##T *iterator = doublelist->head;                   \
    while (iterator != doublelist->tail && index--) {            \
      iterator = iterator->next;                                 \
    }                                                            \
    if (index >= 0) {                                            \
      printf("index has out of range, can't remove any node\n"); \
      return;                                                    \
    }                                                            \
    iterator->pre->next = iterator->next;                        \
    iterator->next->pre = iterator->pre;                         \
    iterator->pre = NULL;                                        \
    iterator->next = NULL;                                       \
    free(iterator);                                              \
  }
#define Merge(T)                                                                                                   \
  void merge_##T(struct doublelist_##T *dst, struct doublelist_##T *src, int dstbegin, int srcbegin, int srcend) { \
    ListNode_##T *dstit = dst->head;                                                                               \
    ListNode_##T *srcit = src->head;                                                                               \
    while (dstit->next != dst->tail && dstbegin-- > 0) dstit = dstit->next;                                        \
    if (dstbegin > 0) printf("dstbegin has out of range, so merge begin at the tail\n");                           \
    ListNode_##T *copybegin;                                                                                       \
    ListNode_##T *copyend;                                                                                         \
    int copylength = 0;                                                                                            \
    while (srcit->next != src->tail) {                                                                             \
      srcit = srcit->next;                                                                                         \
      srcbegin--;                                                                                                  \
      srcend--;                                                                                                    \
      if (srcend <= 0) break;                                                                                      \
      if (srcbegin == 0) {                                                                                         \
        copybegin = newListNode(T)(srcit->val);                                                                    \
        copyend = copybegin;                                                                                       \
        copylength++;                                                                                              \
      } else if (srcbegin < 0) {                                                                                   \
        ListNode_##T *node = newListNode(T)(srcit->val);                                                           \
        copyend->next = node;                                                                                      \
        node->pre = copyend;                                                                                       \
        copyend = copyend->next;                                                                                   \
        copylength++;                                                                                              \
      }                                                                                                            \
    }                                                                                                              \
    if (srcbegin > 0) {                                                                                            \
      printf("srcbegin has out of range, so stop merge\n");                                                        \
      return;                                                                                                      \
    }                                                                                                              \
    dstit->next->pre = copyend;                                                                                    \
    copyend->next = dstit->next;                                                                                   \
    copybegin->pre = dstit;                                                                                        \
    dstit->next = copybegin;                                                                                       \
    dst->length += copylength;                                                                                     \
  }
#define Clear(T)                                   \
  void clear_##T(doublelist_##T *list) {           \
    while (list->head->next != list->tail) {       \
      ListNode_##T *deletenode = list->head->next; \
      list->head->next = list->head->next->next;   \
      free(deletenode);                            \
    }                                              \
    list->tail->pre = list->head;                  \
  }
#define NewDoubleList(T)                                                            \
  doublelist_##T *newDoubleList_##T() {                                             \
    doublelist_##T *doublelist = (doublelist_##T *) malloc(sizeof(doublelist_##T)); \
    doublelist->head = (ListNode_##T *) malloc(sizeof(ListNode_##T));               \
    doublelist->tail = (ListNode_##T *) malloc(sizeof(ListNode_##T));               \
    doublelist->head->next = doublelist->tail;                                      \
    doublelist->head->pre = doublelist->tail;                                       \
    doublelist->tail->next = doublelist->head;                                      \
    doublelist->tail->pre = doublelist->head;                                       \
    doublelist->length = 0;                                                         \
    doublelist->insert = insert_##T;                                                \
    doublelist->remove = remove_##T;                                                \
    doublelist->clear = clear_##T;                                                  \
    doublelist->merge = merge_##T;                                                  \
    return doublelist;                                                              \
  }
#define DeleteDoubleList(T)                               \
  void deleteDoubleList_##T(doublelist_##T *doublelist) { \
    ListNode_##T *iterator = doublelist->head;            \
    while (iterator) {                                    \
      ListNode_##T *deleteNode = iterator;                \
      iterator = iterator->next;                          \
      free(deleteNode);                                   \
    }                                                     \
    free(doublelist);                                     \
  }
#define newDoubleList(T) newDoubleList_##T
#define deleteDoubleList(T) deleteDoubleList_##T
#define DEFINEDOUBLELIST(T) ListNode(T) \
  NewListNode(T)                        \
    DeleteListNode(T)                   \
      DoubleList(T)                     \
        Insert(T)                       \
          Remove(T)                     \
            Clear(T)                    \
              Merge(T)                  \
                NewDoubleList(T)        \
                  DeleteDoubleList(T)

DEFINEDOUBLELIST(int)
DEFINEDOUBLELIST(char)
DEFINEDOUBLELIST(float)
DEFINEDOUBLELIST(double)

int main() {
  doublelist(int) *list = newDoubleList(int)();
  doublelist(int) *list1 = newDoubleList(int)();
  listnode(int) *node = newListNode(int)(10);
  listnode(int) *node1 = newListNode(int)(1);
  list->insert(list, 0, node);
  list->insert(list, 1, node1);
  listnode(int) *node2 = newListNode(int)(3);
  listnode(int) *node3 = newListNode(int)(4);
  list1->insert(list1, 0, node2);
  list1->insert(list1, 1, node3);
  list->merge(list, list1, 1, 1, 3);
  listnode(int) *iterator = list->head;
  while (iterator->next != list->tail) {
    iterator = iterator->next;
    printf("%d\n", iterator->val);
  }
  list->remove(list, 1);
  iterator = list->head;
  while (iterator->next != list->tail) {
    iterator = iterator->next;
    printf("%d\n", iterator->val);
  }

  free(list);
}
