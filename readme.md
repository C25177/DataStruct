there are some c source files

**首先本人很菜，勿喷😁**
文件可读性较差，而且会有bug(体谅一下哈，毕竟调试宏定义不能查看代码内部运行情况，只能根据结果和经验来解决问题😭)
亲测指针类型的好像会出问题(在binarytree的时候测试的😭，痛苦，有解决办法：可以利用typedef，把指针类型重命名为ptr，如 `typedef int* intptr`)
如果看不懂可以试试 gcc -E xx.c -o yy.c 查看生成的预编译文件，预编译会把所有宏定义展开，所以还是比较人性化的
