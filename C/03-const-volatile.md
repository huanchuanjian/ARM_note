## const-volatile

#### const
1. 在很多人的概念里，`const`定义的是“常量”。其实`const`本质上定义的是 **只读变量** ，通过const关键字，来告诉编译器，该变量不可以作为左值。我们可以测试一下
```cpp
const int cval = 1;
cval = 2;	/* 编译器报错：error: assignment of read-only variable ‘cval’ */
```
通过出错信息，我们也可以看出cval是一个 **read-only variable**

2. 虽然我们不能直接把const变量作为左值来修改它的内容，但作为一个 **只读变量** ，它是占有内存空间的。既然这样，那我们就可以通过取到const变量的内存地址，通过指针来 **间接修改** 它的值。下面来测试一下：
```cpp
const int cval = 1;
int* pcval = (int*) &cval;
*pcval = 2;

printf("cval = %d\n", cval);
```

3. const数组
	* 同样，const修饰的数组也是只读的
	* C语言标准里，const修饰的数组空间不可以修改。（这里我测试了一下，gcc g++是可以修改的）
	

#### volatile