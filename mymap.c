//------------------------------------------------------------------------
// File Name: mymap.c
// Author: Dragon
// mail: [beloved25177@126.com](mailto:beloved25177@126.com)
// Created Time: Wed 04 Oct 2023 22:19:16 CST
// Description:
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define MapNode(TKEY, TVAL) typedef struct mapnode_##TKEY_##TVAL{\
  TKEY key;\
  TVAL val;\
}mapnode_##TKEY_##TVAL;
#define mapnode(TKEY, TVAL) mapnode_##TKEY_##TVAL
#define NewMapNode(TKEY, TVAL) mapnode_##TKEY_##TVAL *newmapnode_##TKEY_##TVAL(const TKEY key, const TVAL val){\
  mapnode_##TKEY_##TVAL *node = (mapnode_##TKEY_##TVAL *) malloc(sizeof(mapnode_##TKEY_##TVAL));\
  node->key = key;\
  node->val = val;\
  return node;\
}
#define DeleteMapNode(TKEY, TVAL) void deletemapnode_##TKEY_##TVAL(mapnode_##TKEY_##TVAL *node){\
  free(node);\
}
MapNode(int, int)
NewMapNode(int, int)
DeleteMapNode(int, int)

#define Map(TKEY, TVAL) typedef struct map_##TKEY_##TVAL{\
}map_##TKEY_##TVAL;
  
int main(){

}