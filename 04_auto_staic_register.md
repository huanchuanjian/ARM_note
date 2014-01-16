auto | static | register
------------------------

众所周知，在C语言里 auto, static, register 这三个关键字是用来**修饰变量的属性的**。
本篇博文详细整理这三个关键字的注意点，欢迎拍砖。

### auto
* auto定义的变量只能为 **局部变量**，因为用auto修饰的变量表示编译器会为它在 **栈区域** 分配一块内存空间，而 **全局变量** 是被分配在程序的 **全局区域** 的，所以像下面这样的写法是错误的：

```
auto int i = 0;    /* error: file-scope declaration of ‘i’ specifies ‘auto’ */

int main()
{
	return 0;
}

```

* 而我们通常的局部变量默认就具有auto属性，所以可以省略

```
int main()
{
	int i = 0;    /* 等价于auto int i = 0; */
}
```

### register
* register关键字，表明 **想要使** 该变量存储在寄存器中，但由于CPU寄存器的数量有限，所以这里存在随机性。

* 使用register定义的变量只能是局部变量，为什么呢？试想如果定义一个寄存器全局变量，那么在 **运行时** CPU必须腾出一个寄存器来存放该变量，并且在这段时间内，该寄存器只能用来存放该变量。可想而知，数量有限的寄存器是不可能允许编译器这样做的。我们可以测试一下：

```
register int i = 0;    /* 报错：error: register name not specified for ‘i’ */

int main()
{
	return 0;
}
```

* 注意：寄存器变量不能对其使用&，因为&是指“取存储在内存里的变量的地址”，这里的变量在寄存器内，所以就谈不上使用&了。

* 寄存器变量的适用范围：对于频繁使用且对性能要求极高的实时任务中


### static 
static关键字是最容易混淆的，下面重点分析static，把握static关键字，主要理解下面两点：

1. 使用static修饰的 **局部变量** 是存储在程序的 **静态区** 的。
2. static的另一个意义是：文件作用域标示符 
	* 使用static修饰的 **全局变量** 作用域只是在声明的文件里
	* 使用static修饰的 **函数** 作用域只是在声明的文件里

下面就围绕上面2点分析

* 首先来说第1点，下面的这段代码很多同学都见过，也知道结果原因，这里不做过多解释。


```
#include <stdio.h>

void foo()
{
	static int i = 0;
	i++;
	
	printf("i=%d\n", i);
}

void bar()
{
	int i = 0;
	i++

	printf("i=%d\n", i);
}

int main()
{
	int j;
	for (j = 0; j < 5; j++) {
		foo();
	}

	for (j = 0; j < 5; j++) {
		bar();
	}

	return 0;
}

```

结果是：

```
i=1
i=2
i=3
i=4
i=5
i=1
i=1
i=1
i=1
i=1
```

这里只需要记住：**用static修饰的静态局部变量，在程序的静态区仅初始化一次**


* 下面来说第2点，下面创建2个C源文件用于测试，分别为test1.c, test2.c

	* 通常我们是像这样定义一个全局变量并引用它

```
/* test1.c */
#include <stdio.h>

extern int g_in_test2;

int main()
{
	printf("%d\n", g_in_test2);
	return 0;
}


/* test2.c */

/* 当然这样定义不是很合理，后面会写一篇博文关于定义全局变量的小技巧*/
int g_in_test2 = 1;    

```
	* 这里有个问题，这样定义的全局变量副作用太大，这里我们可以利用static第二点意义，就是 **文件作用域标示符**，将用static修饰的 **静态全局变量** 限定在定义它的文件内，如果外部想要访问的话，只能使用类似 Java, C#等面向对象语言中使用的 get(), set()的方式。

```
/* test1.c */
#include <stdio.h>

extern int get();

int main()
{
	printf("%d\n", get());
	return 0;
}


/* test2.c */

static int g_in_test2 = 1; 

int get()
{
	return g_in_test2;
}

```

	* 对于使用static修饰的函数也具有同样的使用，这里就不多说了，直接上代码

```
/* test1.c */
#include <stdio.h>

extern int do_get();

int main()
{
	printf("%d\n", do_get());
	return 0;
}


/* test2.c */

static int g_in_test2 = 1; 

static int get()
{
	return g_in_test2;
}

int do_get()
{
	return get();
}
```


关于auto, static, register就总结这么多，理解了上面这些要点就OK了。






