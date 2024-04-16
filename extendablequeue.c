//------------------------------------------------------------------------
// File Name: myqueue.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Wed 27 Sep 2023 09:06:03 CST
// Description:
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Queue(T)                                   \
  typedef struct queue_##T {                       \
    void *start;                                   \
    void *end;                                     \
    T *ptr;                                        \
    int size;                                      \
    void (*push)(struct queue_##T * queue, T val); \
    void (*pop)(struct queue_##T * queue);         \
    T(*top)                                        \
    (struct queue_##T * queue);                    \
  } queue_##T;
#define queue(T) queue_##T
#define Push(T)                                    \
  void push_##T(queue_##T *queue, T val) {         \
    if (queue->ptr == queue->end) {                \
      T *newstart = (T *) malloc(2 * queue->size); \
      memcpy(newstart, queue->start, queue->size); \
      free(queue->start);                          \
      queue->start = newstart;                     \
      queue->end = queue->start + queue->size * 2; \
      queue->ptr = queue->start + queue->size;     \
      queue->size = 2 * queue->size;               \
    }                                              \
    memmove(queue->ptr, &val, sizeof(T));          \
    queue->ptr += 1;                               \
  }
#define Pop(T)                                                                              \
  void pop_##T(queue_##T *queue) {                                                          \
    if ((void *) queue->ptr == queue->start) return;                                        \
    memmove(queue->start, queue->start + sizeof(T), queue->end - queue->start - sizeof(T)); \
    queue->ptr -= 1;                                                                        \
  }
#define Top(T)                                                    \
  T top_##T(queue_##T *queue) {                                   \
    T data;                                                       \
    if ((void *) queue->ptr - queue->start < sizeof(T)) return 0; \
    memmove(&data, queue->start, sizeof(T));                      \
    return data;                                                  \
  }
#define NewQueue(T)                                             \
  queue_##T *newqueue_##T() {                                   \
    queue_##T *queue = (queue_##T *) malloc(sizeof(queue_##T)); \
    queue->start = malloc(sizeof(T) * 32);                      \
    queue->size = 32 * sizeof(T);                               \
    queue->end = queue->start + queue->size;                    \
    queue->ptr = queue->start;                                  \
    queue->push = push_##T;                                     \
    queue->pop = pop_##T;                                       \
    queue->top = top_##T;                                       \
    return queue;                                               \
  }
#define newqueue(T) newqueue_##T
#define DeleteQueue(T)                     \
  void deletequeue_##T(queue_##T *queue) { \
    free(queue->start);                    \
    free(queue);                           \
  }
#define deletequeue(T) deletequeue_##T
#define DEFINEQUEUE(T) Queue(T) \
  Push(T)                       \
    Pop(T)                      \
      Top(T)                    \
        NewQueue(T)             \
          DeleteQueue(T)

DEFINEQUEUE(int)
DEFINEQUEUE(char)
DEFINEQUEUE(float)
DEFINEQUEUE(double)

int main() {
  queue(int) *queue = newqueue(int)();
  int i = 33;
  while (i--)
    queue->push(queue, i);
  i = 33;
  while (i--) {
    printf("%d\n", queue->top(queue));
    queue->pop(queue);
  }
  deletequeue(int)(queue);
}
