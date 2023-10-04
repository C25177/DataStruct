//------------------------------------------------------------------------
// File Name: priorityqueue.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Wed 04 Oct 2023 08:41:25 CST
// Description:  优先级队列
//------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DefaultCompare(T) int compare_##T(const T a, const T b){\
  if(a < b) return 1;\
  if(a == b) return 0;\
  return -1;\
}
DefaultCompare(int)
DefaultCompare(char)
DefaultCompare(float)
DefaultCompare(double)
#define defaultcompare(T) compare_##T
#define PriorityQueue(T) typedef struct priority_queue_##T{\
  void *start;\
  void *end;\
  T *ptr;\
  int (*compare)(const T a, const T b);\
  void (*push)(struct priority_queue_##T *queue, const T val);\
  void (*pop)(struct priority_queue_##T *queue);\
  T (*top)(struct priority_queue_##T *queue);\
  T (*getval)(struct priority_queue_##T *queue, int index);\
  int (*find)(struct priority_queue_##T *queue, const T val);\
  int (*size)(struct priority_queue_##T *queue);\
  int (*maxsize)(struct priority_queue_##T *queue);\
  int (*isempty)(struct priority_queue_##T *queue);\
  void (*clear)(struct priority_queue_##T *queue);\
  void (*merge)(struct priority_queue_##T *dst, struct priority_queue_##T *src, int srcbegin, int srcend);\
}priority_queue_##T;
#define priorityqueue(T) priority_queue_##T
// Binary search sort insert
#define Push(T) void push_##T(priority_queue_##T *queue, const T val){\
  int size = queue->ptr - (T *) queue->start;\
  if(queue->ptr == queue->end){\
    void *newstart = malloc(sizeof(T) * size * 2);\
    memcpy(newstart, queue->start, size * sizeof(T));\
    queue->start = newstart;\
    queue->end = newstart + size * 2 * sizeof(T);\
    queue->ptr = newstart + size * sizeof(T);\
  }\
  int left = 0, right = size;\
  while(right > left){\
    int mid = (right + left) >> 1;\
    T *it = (T *) queue->start + mid;\
    if(queue->compare(*it, val) > 0) right = mid - 1;\
    else if(queue->compare(*it, val) < 0) left = mid + 1;\
    else {\
      left = mid;\
      break;\
    }\
  }\
  memmove(queue->start + (left + 1) * sizeof(T), queue->start + (left + 0) * sizeof(T), (size - left) * sizeof(T));\
  *((T *) queue->start + left + 0) = val;\
  queue->ptr += 1;\
}
#define Pop(T) void pop_##T(priority_queue_##T *queue){\
  if(queue->start == (void *) queue->ptr){\
    printf("this queue has been empty\n");\
    return;\
  }\
  memcpy(queue->start, queue->start + sizeof(T), (queue->end - queue->start - 1));\
  queue->ptr -= 1;\
}
#define Top(T) T top_##T(priority_queue_##T *queue){\
  if(queue->start == (void *) queue->ptr){\
    printf("this queue has been empty\n");\
    return (T) 0;\
  }\
  T val = *((T *) queue->start);\
  return val;\
}
#define Size(T) int size_##T(priority_queue_##T *queue){\
  return queue->ptr - (T *) queue->start;\
}
#define Maxsize(T) int maxsize_##T(priority_queue_##T *queue){\
  return (T *) queue->end - (T *) queue->start;\
}
#define Isempty(T) int isempty_##T(priority_queue_##T *queue){\
  return queue->start == (void *) queue->ptr;\
}
#define Clear(T) void clear_##T(priority_queue_##T *queue){\
  queue->ptr = queue->start;\
}
#define Find(T) int find_##T(priority_queue_##T *queue, const T val){\
  int size = queue->ptr - (T *) queue->start;\
  int left = 0, right = size - 1;\
  while(right > left){\
    int mid = (left + right) >> 1;\
    T *it = (T *) queue->start + mid;\
    if(queue->compare(*it, val) > 0) right = mid - 1;\
    else if(queue->compare(*it, val) < 0) left = mid + 1;\
    else return mid;\
  }\
  return -1;\
}
#define GetVal(T) T getval_##T(priority_queue_##T *queue, int index){\
  if(index * sizeof(T) + queue->start > (void *) queue->ptr){\
    printf("index has out of range\n");\
    return (T) 0;\
  }\
  return *((T *) queue->start + index);\
}
#define Merge(T) void merge_##T(priority_queue_##T *dst, priority_queue_##T *src, int srcbegin, int srcend){\
  int srcsize = src->ptr - (T *) src->start;\
  if(srcsize < srcbegin){\
    printf("srcbegin has out of index, stop merge\n");\
    return;\
  }\
  for(int i = srcbegin; i < srcend && i < srcsize; i++){\
    dst->push(dst, *((T *) src->start + i));\
  }\
}
#define NewPriorityQueue(T) priority_queue_##T *newpriorityqueue_##T(int (*compare)(const T a, const T b)){\
  priority_queue_##T *queue = (priority_queue_##T *) malloc(sizeof(priority_queue_##T));\
  queue->start = malloc(32 * sizeof(T));\
  queue->end = queue->start + 32 * sizeof(T);\
  queue->ptr = queue->start;\
  queue->compare = compare;\
  queue->push = push_##T;\
  queue->pop = pop_##T;\
  queue->top = top_##T;\
  queue->size = size_##T;\
  queue->maxsize = maxsize_##T;\
  queue->isempty = isempty_##T;\
  queue->clear = clear_##T;\
  queue->find = find_##T;\
  queue->getval = getval_##T;\
  queue->merge = merge_##T;\
}
#define DeletePriorityQueue(T) void deletepriorityqueue_##T(priority_queue_##T *queue){\
  free(queue->start);\
  free(queue);\
}
#define newpriorityqueue(T) newpriorityqueue_##T
#define deletepriorityqueue(T) deletepriorityqueue_##T
#define DEFINEPRIORITYQUEUE(T) PriorityQueue(T)\
  Push(T)\
  Pop(T)\
  Top(T)\
  Size(T)\
  Maxsize(T)\
  Isempty(T)\
  Clear(T)\
  Find(T)\
  GetVal(T)\
  Merge(T)\
  NewPriorityQueue(T)\
  DeletePriorityQueue(T)

DEFINEPRIORITYQUEUE(int)
DEFINEPRIORITYQUEUE(char)
DEFINEPRIORITYQUEUE(float)
DEFINEPRIORITYQUEUE(double)

int main(){
  priorityqueue(int) *queue = newpriorityqueue(int) (defaultcompare(int));
  queue->push(queue, 10);
  queue->push(queue, 11);
  queue->push(queue, 15);
  queue->push(queue, 9);
  printf("%d\n", queue->find(queue, 2));
  printf("%d\n", queue->find(queue, 10));
  printf("%d\n", queue->size(queue));
  printf("%d\n", queue->getval(queue, 1));
  for(int i = 0; i < 4; i++){
    printf("%d\n", queue->top(queue));
    queue->pop(queue);
  }
  deletepriorityqueue(int) (queue);
}

