//------------------------------------------------------------------------
// File Name: myvector.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Fri 29 Sep 2023 11:36:37 CST
// Description: 向量
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Vector(T) typedef struct vector_##T{\
  void *start;\
  void *end;\
  T *ptr;\
  int (*size)(struct vector_##T *vector);\
  int (*max_size)(struct vector_##T *vector);\
  int (*isempty)(struct vector_##T *vector);\
  void (*push_back)(struct vector_##T *vector, T val);\
  void (*pop_back)(struct vector_##T *vector);\
  void (*remove)(struct vector_##T *vec, int begin, int end);\
  int (*find)(struct vector_##T *vec, T val);\
  T (*back)(struct vector_##T *vector);\
  T (*front)(struct vector_##T *vector);\
  void (*copyfrom)(struct vector_##T *dst, struct vector_##T *src, int srcbegin, int srcend);\
  void (*merge)(struct vector_##T *dst, struct vector_##T *src, int dstbegin, int srcbegin, int srcend);\
  void (*clear)(struct vector_##T *vec);\
}vector_##T;
#define vector(T) vector_##T
#define Size(T) int size_##T(vector_##T *vector){\
  return vector->ptr - (T *)vector->start;\
}
#define Max_size(T) int max_size_##T(vector_##T *vector){\
  return (T *) vector->end - (T *) vector->start;\
}
#define Isempty(T) int isempty_##T(vector_##T *vector){\
  return (void *) vector->ptr == vector->start;\
}
#define Push_back(T) void push_back_##T(vector_##T *vector, T val){\
  if(vector->end - (void *)vector->ptr < sizeof(T)){\
    int size = vector->end - vector->start;\
    void *newstart = malloc(size * 2);\
    memcpy(newstart, vector->start, size);\
    free(vector->start);\
    vector->start = newstart;\
    vector->end = vector->start + size * 2;\
    vector->ptr = vector->start + size;\
  }\
  memcpy((void *) vector->ptr, &val, sizeof(T));\
  vector->ptr += 1;\
}
#define Pop_back(T) void pop_back_##T(vector_##T *vector){\
  if(vector->ptr != vector->start)\
    vector->ptr -= 1;\
  else \
    printf("this vector has been empty\n");\
}
#define Back(T) T back_##T(vector_##T *vector){\
  if(vector->ptr == vector->start){\
    printf("this vector is empty\n");\
    return (T)0;\
  }\
  T val;\
  memcpy(&val, (void *) vector->ptr - 1, sizeof(T));\
  return val;\
}
#define Front(T) T front_##T(vector_##T *vector){\
  if(vector->ptr == vector->start){\
    printf("this vector is empty\n");\
    return (T)0;\
  }\
  T val;\
  memcpy(&val, vector->start, sizeof(T));\
  return val;\
}
#define Remove(T) void remove_##T(vector_##T *vec, int begin, int end){\
  T *pbegin = vec->start + begin;\
  T *pend = vec->start + end;\
  memcpy((void *)pbegin, (void *)pend, ((void *) vec->ptr - (void *) pend));\
  vec->ptr = pbegin + (vec->ptr - pend);\
}
#define Find(T) int find_##T(vector_##T *vec, T val){\
  T *iterator = vec->start;\
  int index = 0;\
  while(iterator != vec->ptr){\
    if(*iterator == val)return index;\
    iterator++;\
    index++;\
  }\
  return -1;\
}
// srcbegin and srcend is index
#define Copyfrom(T) void copyfrom_##T(vector_##T *dst, vector_##T *src, int srcbegin, int srcend){\
  int srcsize = (void *) src->ptr - src->start;\
  if(srcbegin * sizeof(T) > srcsize){\
    printf("begin index has out of range");\
    return;\
  }\
  if(srcend * sizeof(T) > srcsize){\
    printf("end index has out of range");\
    return;\
  }\
  int dstmaxsize = dst->end - dst->start;\
  int copysize = sizeof(T) * (srcend - srcbegin);\
  if(dstmaxsize < copysize){\
    while(dstmaxsize < copysize)\
      dstmaxsize << 2;\
    void *newstart = malloc(dstmaxsize);\
    dst->start = newstart;\
  }\
  memcpy(dst->start, src->start + sizeof(T) * srcbegin, copysize);\
  dst->ptr = (T *) dst->start + srcend - srcbegin;\
}
#define Merge(T) void merge_##T(struct vector_##T *dst, struct vector_##T *src, int dstbegin, int srcbegin, int srcend){\
  int srcsize = src->ptr - (T *) src->start;\
  if(srcbegin >= srcsize){\
    printf("begin index has out of range");\
    return;\
  }\
  if(srcend * sizeof(T) > srcsize){\
    printf("end index has out of range");\
    return;\
  }\
  int dstmaxsize = dst->end - dst->start;\
  int dstsize = (void *) dst->ptr - dst->start;\
  while(dstmaxsize < dstsize + (srcend - srcbegin) * sizeof(T))\
    dstmaxsize << 2;\
  void *newstart = malloc(dstmaxsize);\
  memcpy(newstart, dst->start, dstbegin * sizeof(T));\
  memcpy(newstart + dstbegin * sizeof(T), src->start + srcbegin * sizeof(T), (srcend - srcbegin) * sizeof(T));\
  memcpy(newstart + dstbegin * sizeof(T) + srcsize, dst->start + dstbegin * sizeof(T), (void *) dst->ptr - dst->start - dstbegin * sizeof(T));\
  free(dst->start);\
  dst->start = newstart;\
  dst->end = newstart + dstmaxsize;\
  dst->ptr = newstart + dstsize + (srcend - srcbegin) * sizeof(T);\
}
#define Clear(T) void clear_##T(vector_##T *vec){\
  vec->ptr = vec->start;\
}
#define NewVector(T) vector_##T *newvector_##T(){\
  vector_##T *vector = malloc(sizeof(vector_##T));\
  vector->start = malloc(sizeof(T) * 32);\
  vector->end = vector->start + sizeof(T) * 32;\
  vector->ptr = vector->start;\
  vector->size = size_##T;\
  vector->max_size = max_size_##T;\
  vector->push_back = push_back_##T;\
  vector->pop_back = pop_back_##T;\
  vector->front = front_##T;\
  vector->back = back_##T;\
  vector->find = find_##T;\
  vector->remove = remove_##T;\
  vector->copyfrom = copyfrom_##T;\
  vector->merge = merge_##T;\
  vector->clear = clear_##T;\
  return vector;\
}
#define DeleteVector(T) void deletevector_##T(vector_##T *vector){\
  free(vector->start);\
  free(vector);\
}
#define newvector(T) newvector_##T
#define deletevector(T) deletevector_##T
#define DEFINEVECTOR(T) Vector(T)\
  Size(T)\
  Max_size(T)\
  Push_back(T)\
  Pop_back(T)\
  Back(T)\
  Front(T)\
  Remove(T)\
  Find(T)\
  Copyfrom(T)\
  Merge(T)\
  Clear(T)\
  NewVector(T)\
  DeleteVector(T)

DEFINEVECTOR(int)
DEFINEVECTOR(char)
DEFINEVECTOR(float)
DEFINEVECTOR(double)

int main(){
  vector(int) *v = newvector(int)();
  vector(int) *v2 =newvector(int)();
  int i = 33;
  while(i--){
    v->push_back(v, i);
  }
  i = 33;
  v2->copyfrom(v2, v, 0, 10);
  v2->merge(v2, v, 5, 1, 10);
  while(i--){
    printf("%d\n", v->back(v));
    printf("%d\n", v2->back(v2));
    v->pop_back(v);
    v2->pop_back(v2);
  }
  v->pop_back(v);
  deletevector(int)(v);
  deletevector(int)(v2);
}
