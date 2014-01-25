## struct-union

#### struct

* 空结构体类型是多大呢？我们分别用gcc, g++来编译测试下面这段代码：

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


#### 用struct定义“柔性数组”
* 什么是“柔性数组”？通常我们在声明一个数组时，必须指定数组大小，否则编译不通过，“柔性数组”其实就是 **变长数组** ，长度在运行时从堆上动态分配的。

* 我们可以这样定义一个“柔性数组”
```cpp
#include <stdio.h>

typedef struct _soft_array
{
	int len;
	int array[];
} soft_array;

int main(int argc, char** argv)
{
	printf("soft_array size = %d\n", sizeof(soft_array));
	return 0;
}
```

这里，我顺便打印出了soft_array的大小，结果
`soft_array size = 4`
这是因为array[]这个 **域** 在这里充当 **占位符** ，编译器无法确定其大小，不为其分配内存空间。所以array[]大小为0

