## struct

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

* 如何给“柔性数组”分配空间？

```cpp
#include <stdio.h>
#include <stdlib.h>

typedef struct _soft_array
{
	int len;
	int array[];
} soft_array;

int main(int argc, char** argv)
{
	soft_array* sa;
	int i;

	// sa = (soft_array*) malloc(sizeof(soft_array) + sizeof(int) * 10);
	sa = (soft_array*) malloc(sizeof(soft_array) + sizeof(sa->array[0]) * 10);
	sa->len = 10;

	for (i = 0; i < sa->len; i++) {
		sa->array[i] = i + 1;
	}

	for (i = 0; i < sa->len; i++) {
		printf("array[%d] = %d\n", i, array[i]);
	}

	free(sa);
	return 0;
}
```

上面的代码还是很好理解的，这边用了一个小技巧，就是用`sa->array[0]`代替`int`，即用 **数组第一个元素的大小来代替数组元素类型的大小** 。

#### 实例：使用“柔性数组”来存储斐波拉契数列（Fibonacci）
实现这样一个实例，主要的思路：
1. 定义一个“柔性数组”
2. 为1定义的数组分配空间
3. 创建Fibonacci数列
4. 释放内存

实现代码：

```cpp
/**********************************
 * http://www.typeof.me
 * Author: huanzh
 * Date: 25 Jan 2014 Sat
 *
 **********************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct _soft_array
{
	int len;
	int array[];
} soft_array;

soft_array* create_soft_array(int size)
{
	soft_array* ret = NULL;
	
	if (size > 0) {
		ret = (soft_array*) malloc(sizeof(ret) + sizeof(ret->array[0]) * size);
		ret->len = size;
	}

	return ret;
}

void fac(soft_array* sa)
{
	int i;

	if (1 == sa->len) {
		sa->array[0] = 1;
	} else {
		sa->array[0] = 1;
		sa->array[1] = 1;

		/* 注意从2开始计算 */
		for (i = 2; i < sa->len; i++) {
			sa->array[i] = sa->array[i-1] + sa->array[i-2];
		}
	}
}

void delete_soft_array(soft_array* sa)
{
	free(sa);
}

int main(int argc, char** argv)
{
	int i;
	soft_array* sa_fac = create_soft_array(10);

	if (NULL != sa_fac) {
		fac(sa_fac);

		for (i = 0; i < sa_fac->len; i++) {
			printf("%d = %d\n", i+1, sa_fac->array[i]);
		}
	}

	delete_soft_array(sa_fac);
	return 0;
}
```

最后附上斐波拉契曲线，黄金比，蒙娜丽莎的整体构图就符合该曲线。

![](http://ww2.sinaimg.cn/mw690/7fcfb6a1gw1ecw4uve7skj20go0b4dgm.jpg)
