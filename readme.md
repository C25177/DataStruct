毕竟不是计算机专业的，**本人很菜，勿喷😁**
文件可读性较差，而且会有bug(体谅一下哈，毕竟调试宏定义不能查看代码内部运行情况，只能根据结果和经验来解决问题😭)
亲测指针类型的好像会出问题(在binarytree的时候测试的😭，痛苦，有解决办法：可以利用typedef，把指针类型重命名为ptr，如 `typedef int* intptr`，已经写好的数据结构就不想再改了，之后有机会再改)
如果看不懂可以试试 gcc -E xx.c -o yy.c 查看生成的预编译文件，预编译会把所有宏定义展开，所以还是比较人性化的

代码中实际上使用了c语言库中的函数，毕竟很好用，特别是memcpy和memmove，但是需要注意memcpy和memmove功能上和效率上的区别
还有就是代码中涉及很多指针操作（因为我觉得对于动态规划的话，申请一块内存来进行操作是很不错的，所以一定会需要指针来管理内存），比较危险，所以**一定记得要释放掉指针，尽量避免危险操作**