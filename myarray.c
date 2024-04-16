//------------------------------------------------------------------------
// File Name: myarray.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Wed 27 Sep 2023 08:23:46 CST
// Description:
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define Array(T)             \
  typedef struct array_##T { \
    T *val;                  \
  } array_##T;
#define array(T) array_##T
#define NewArray(T)                                            \
  array_##T *newArray_##T(int size) {                          \
    array(T) *array = (array_##T *) malloc(sizeof(array_##T)); \
    array->val = (T *) malloc(sizeof(T) * size);               \
    return array;                                              \
  }
#define newArray(T) newArray_##T
#define DeleteArray(T)                     \
  void deleteArray_##T(array_##T *array) { \
    free(array->val);                      \
    free(array);                           \
  }
#define deleteArray(T) deleteArray_##T
#define DEFINEARRAY(T) Array(T) \
  NewArray(T)                   \
    DeleteArray(T)

DEFINEARRAY(int)
DEFINEARRAY(char)
DEFINEARRAY(float)
DEFINEARRAY(double)

int main() {
  array(int) *a = newArray(int)(10);
  *(a->val) = 1;
  *(a->val + 1) = 2;
  *(a->val + 2) = 3;
  *(a->val + 3) = 4;
  a->val[4] = 5;

  printf("%d\n", *(a->val));
  printf("%d\n", *(a->val + 1));
  printf("%d\n", *(a->val + 2));
  printf("%d\n", *(a->val + 3));
  printf("%d\n", a->val[4]);

  deleteArray(int)(a);
}
