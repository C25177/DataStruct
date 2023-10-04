//------------------------------------------------------------------------
// File Name: mystack.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Fri 29 Sep 2023 14:05:50 CST
// Description: 栈
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Stack(T) typedef struct stack_##T{\
  void *start;\
  void *end;\
  T *ptr;\
  void (*push)(struct stack_##T *stack, T val);\
  void (*pop)(struct stack_##T *stack);\
  T (*top)(struct stack_##T *stack);\
  int (*isfull)(struct stack_##T *stack);\
  int (*isempty)(struct stack_##T *stack);\
  int (*size)(struct stack_##T *stack);\
  int (*maxsize)(struct stack_##T *stack);\
}stack_##T;
#define stack(T) stack_##T

#define Push(T) void push_##T(stack_##T *stack, T val){\
  if(stack->end - (void *)stack->ptr < sizeof(T)){\
    printf("this stack has been full\n");\
    return;\
  }\
  memcpy((void *)(stack->ptr), &val, sizeof(T));\
  stack->ptr += 1;\
}
#define Pop(T) void pop_##T(stack_##T *stack){\
  if((void *)stack->ptr - stack->start < sizeof(T)){\
    printf("this stack has been empty\n");\
    return;\
  }\
  stack->ptr -= 1;\
}
#define Top(T) T top_##T(stack_##T *stack){\
  if(stack->start == (void *)stack->ptr)return (T)0;\
  T data;\
  memcpy(&data, stack->ptr - 1, sizeof(T));\
  return data;\
}
#define Isfull(T) int isfull_##T(stack_##T *stack){\
  return (void *)stack->ptr == stack->end;\
}
#define Isempty(T) int isempty_##T(stack_##T *stack){\
  return (void *)stack->ptr == stack->start;\
}
#define Size(T) int size_##T(stack_##T *stack){\
  return stack->ptr - (T *) stack->start;\
}
#define Maxsize(T) int maxsize_##T(stack_##T *stack){\
  return (T *) stack->end - (T *) stack->start;\
}
#define NewStack(T) stack_##T *newStack_##T(int size){\
  stack_##T *stack = (stack_##T *) malloc(sizeof(stack_##T));\
  stack->start = malloc(sizeof(T) * size);\
  stack->end = stack->start + sizeof(T) * size;\
  stack->ptr = stack->start;\
  stack->push = push_##T;\
  stack->pop = pop_##T;\
  stack->top = top_##T;\
  stack->isfull = isfull_##T;\
  stack->isempty = isempty_##T;\
  stack->size = size_##T;\
  stack->maxsize = maxsize_##T;\
  return stack;\
}
#define newStack(T) newStack_##T

#define DeleteStack(T) void deleteStack_##T(stack_##T *stack){\
  stack->ptr = NULL;\
  stack->end = NULL;\
  free(stack->start);\
  free(stack);\
}
#define deleteStack(T) deleteStack_##T

// 对外接口
#define DEFINESTACK(T) Stack(T)\
  Push(T)\
  Pop(T)\
  Top(T)\
  Isfull(T)\
  Isempty(T)\
  Size(T);\
  Maxsize(T)\
  NewStack(T)\
  DeleteStack(T)

DEFINESTACK(int)
DEFINESTACK(char)
DEFINESTACK(float)
DEFINESTACK(double)

int main(){
  stack(int) *stack = newStack(int)(10);
  int i = 13;
  while(i--){
    stack->push(stack, i);
  }
  i = 13;
  while(i--){
    int a = (stack->top(stack));
    printf("%d\n", a);
    stack->pop(stack);
  }
}


