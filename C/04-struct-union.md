## struct-union

#### struct

1. 空结构体类型是多大呢？我们分别用gcc, g++来编译测试下面这段代码：

```cpp
#include <stdio.h>

typedef struct _test
{
} test;

int main(int argc, char** argv)
{
	test t1;
	test t2;
	printf("%d\n", sizeof(test));
	printf("%d\t%p\n", sizeof(t1), &t1);
	printf("%d\t%p\n", sizeof(t2), &t2);

	return 0;
}
```

结果:
```shell
[root@localhost C]# gcc sizeof.c 
[root@localhost C]# ./a.out 
0
0       0xbf81a050
0       0xbf81a050
[root@localhost C]# g++ sizeof.c 
[root@localhost C]# ./a.out 
1
1       0xbfdd8d2f
1       0xbfdd8d2e
```

从结果可以看出，g++给出的结果 **更合理** ，其实在C语言规范里。并没有明确定义空结构体类型的大小，所以各个编译器都有其各自的定义。

2. 
