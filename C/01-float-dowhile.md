C编程技巧 - float 和 do...while()
--------------------------------

#### float
我们在程序内定义一个float类型的变量，并在if的条件表达式中使用，像下面这样的代码相信很多童鞋写过（当然包括我啦）

```
float f = 0.0;

if (0 == f) {
	/* ... */
}
```

这样其实是不正确的，因为在计算机内部，是用 **离散值** 来表示float数的，所以float能够表示的精度也是有限的。所以我们在进行float数的比较计算时，需要 **定义精度** ，比如像这样

```
#define EPSINON 0.000001

float f = 0.0;

if ((0 - EPSINON <= f) && (0 + EPSINON >= f)) {
	/* ... */
}
```

这样使得f位于一个 **闭区间** 内，即 [0-EPSINON, 0+EPSINON]


#### do...while()
起初，我跟很多童鞋一样，认为do...while()这条循环语句没什么用。下面我们来看看它到底有木有用，首先通常的函数流程基本都是像下面这幅图所描述的：

![](http://ww4.sinaimg.cn/mw690/7fcfb6a1gw1ecsfq8was2j20gl068t99.jpg)

结合图，再看代码

```
int foo(int num)
{
	int i = 0;
	int ret = 0;
	int *p = (int *) malloc(sizeof(int) * num);

	do {
		if (NULL == p) break;
		
		if (num < 0) break;

		for (i = 1; i <= num; i++) {
			p[i] = i;
		}

		ret = 1;
	} while (0);

	free(p);
	return ret;
}

```

这里do...while()起到了代码块的作用，从而可以 **统一释放资源，避免内存泄漏** 。