//------------------------------------------------------------------------
// File Name: template.h
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Mon 25 Sep 2023 20:37:55 CST
// Description: C语言实现模板
//------------------------------------------------------------------------

#include <stdio.h>

#define MAX(T) T max_##T (T x, T y){\
  return ((x > y) ? (x) : (y));}

MAX(int)
MAX(char)
MAX(float)

#define STR(T) typedef struct STR##T{T val;}STR##T;

STR(int)
STR(char)
STR(float)

#define Max(T) max_##T
#define Str(T) STR##T
void main(){
  printf("%c\n", Max(char)('a', 'b'));
  printf("%d\n", Max(int)(3, 10));
  printf("%f\n", Max(float)(1.4, 12.3));
  Str(int) a;
  a.val = 199;
  printf("%d\n", a.val);
}

