ARM常用名词归类
--------------

ARM的一些常用名词可以分为这3类：ARM芯片，ARM处理器核，ARM指令架构。这三者之间的关系如下，通过阅读 **ARM芯片手册** 和 **ARM核手册**，可以这样归类

* 6410, 2440, 210这三款均出自SAMSUNG公司，它们属于 **ARM芯片**
* ARM11, ARM9, Cortex A8为上面ARM芯片内部的 **处理器核**，所以它跟芯片是包含关系。
他们分别对应于上面三款芯片
* ARMv7, ARMv4, ARMv6是指 **ARM指令架构**，它跟处理器核有关，通过查看核手册，可以发现这三个指令架构分别对应上面的三个处理器核

6410 -> ARM11(ARMv7)

2440 -> ARM9(ARMv4)

210 -> Cortex A8(ARMv6)


ARM核演变图
----------

![](http://ww3.sinaimg.cn/mw690/7fcfb6a1gw1eckkg4gqjyj20jm0as759.jpg)

* 从图中可以看出ARM核从“ARM经典系列”演变到后来的“Cortex系列”
* 性能上ARM7 **大致** 跟Cortex-M3相当，ARM9 ARM11则跟Cortex-R4相当
* Cortex-M系列主要应用于 **工控领域**，无OS，可以理解为单片机。但性能要比单片机高
* Cortex-R系列主要应用于 **实时领域**，可以安装OS
* Cortex-A系列主要应用于 **多媒体设备领域**，比如现在的大多数智能手机


ARM处理器比较
------------

```
			2440		    6410			  	210

处理器速度  400-500MHz  	 533-667MHz  			800-1GHz
缓存		    16KB        	16KB        		32KB
内存接口     SDRAM      	SDRAM/DDR   			DDR/DDR2
支持的OS winCE/Linux   winCE/Linux/Android 	winCE/Linux/Android 
其他         停产       		未停产       		未停产      

```

