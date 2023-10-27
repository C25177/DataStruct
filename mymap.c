//------------------------------------------------------------------------
// File Name: mymap.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Wed 04 Oct 2023 22:19:16 CST
// Description:
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

typedef struct map{
  void *val;
  void *key;
  void (*push)(void *key, void *val);
}map;


int main(int argc, char const *argv[])
{

  return 0;
}

