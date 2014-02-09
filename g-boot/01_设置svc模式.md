### 自己实现bootloader - 设置svc模式

#### 处理器模式
参考手册，ARM处理器支持7种模式，bootloader需要在较高的模式下运行，即Supervisor模式。
svc模式的模式位是`0b10011`，所以只需要将`CPSR`寄存器的低5位设置为该值就ok了。

#### CPSR格式
![CPSR_format][1]

  [1]: http://ww4.sinaimg.cn/mw690/7fcfb6a1gw1eclqp9r91jj20jy03kmxl.jpg
  
#### 实现

 1. 将低5位清0: `bic`
 2. 再将对应位设置1: `orr`
 
```asm
set_svc:
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x13    @  0x13 => 0b10011 
    msr cpsr, r0
```

#### 改进
在阅读其他bootloader源码，比如U-Boot，发现置1的那条指令是这样写的`orr r0, r0, #0xd3`，将0xd3转换成二进制为`0b11010011`，发现低5位不变，对照上面那幅图，F和I位都置1了，阅读手册有：
> I bit Disables IRQ interrupts when it is set.
> F bit Disables FIQ interrupts when it is set.

这里就理解了，它屏蔽了中断和快速中断。所以我也参考它的实现，这样就更完整了。