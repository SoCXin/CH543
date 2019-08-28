
南京沁恒电子有限公司 2022.2
最新资料请到我们的网站上查询
http://wch.cn


文件目录
  |
  |-- README.TXT：目录文件说明
  |-- DS
  |      |--CH543DS1.PDF：CH543应用手册
  |-- EVT
  |      |-- EXAM: C例程
  |      |      |--CH543.uvproj：CH543 keil4工程文件
  |      |      |--obj：CH543 keil4 EXAM目标文件目录    
  |      |      |--Public
  |      |      |      |--CH543.H：CH543 C语言头文件，SFR定义
  |      |      |      |--Debug.C：UART0&1初始化、常用延时函数、UART0&1数据收发子函数,看门狗初始化
  |      |      |      |--Debug.H：UART0&1初始化、常用延时函数、UART0&1数据收发子函数、看门狗初始化声明
  |      |      |--USB
  |      |      |      |-- Device
  |      |      |      |      |-- CompositeKM.C:模拟键鼠例程，支持部分类命令
  |      |      |      |      |-- CompositeKM.hex 
  |      |      |      |      |-- VendorDefinedDev.C:模拟厂商自定义设备，需要安装CH372驱动，可以通过372test.exe调试(批量数据收发)
  |      |      |      |      |-- VendorDefinedDev.hex
  |      |      |      |      |-- CompatibilityHID.C:模拟HID兼容设备，支持中断上下传
  |      |      |      |      |-- CompatibilityHID.hex  
  |      |      |      |-- Host
  |      |      |      |      |-- HOST.C: USB主机应用例子,初始化和枚举USB端口连接的设备，可实现键盘、鼠标、U盘枚举、HID兼容
  |      |      |      |      |-- HOST.hex:   
  |      |      |      |-- USB_LIB
  |      |      |      |      |-- USBHOST.C&H:CH543 USB 主机接口函数
  |      |      |--PD_PROT
  |      |      |      |-- main.C: Type-C正反插检测及PD通讯初始化
  |      |      |      |-- PD_PHY.C&H: Type-C PD PHY层
  |      |      |      |-- PD_PROT.C&H: Type-C PD PROTOCOL层
  |      |      |      |-- PD_PROT.hex
  |      |      |--TouchKey
  |      |      |      |-- Main.C:CH543 触摸按键中断和查询方式进行采集并报告当前采样通道按键状态，包含初始化和按键采样等演示函数  
  |      |      |      |-- TouchKey.C&H:TouchKey开启，通道切换和中断采集函数
  |      |      |      |-- TouchKey.hex
  |      |      |--Compare
  |      |      |      |-- Main.C:CH543 比较器示例，比较器使能，通道设置，中断/查询方式查询结果  
  |      |      |      |-- Compare.C&H:比较器使能，通道选择，中断函数
  |      |      |      |-- Compare.hex    
  |      |      |--ADC：
  |      |      |      |-- Main.C:ADC使用示例
  |      |      |      |-- ADC.C&H:ADC初始化，采样时钟设定，通道变化和电压比较功能函数定义
  |      |      |      |-- ADC.hex
  |      |      |--FlashRom
  |      |      |      |-- Main.C:DataFlash使用示例
  |      |      |      |-- FlashRom.C&H:DataFlash读写函数定义
  |      |      |      |-- FlashRom.hex
  |      |      |--GPIO
  |      |      |      |-- Main.C:GPIO使用示例
  |      |      |      |-- GPIO.C&H:GPIO设置函数定义
  |      |      |      |-- GPIO.hex
  |      |      |--PWM
  |      |      |      |-- Main.C:PWM使用示例
  |      |      |      |-- PWM.C&H:PWM初始化、设置函数定义
  |      |      |      |-- PWM.hex
  |      |      |--SPI
  |      |      |      |-- SPI.C&H:SPI主从设置和收发函数定义 
  |      |      |      |      |-- SPI_SLAVE
  |      |      |      |      |      |-- MainSlave.C&hex 从机收发演示程序     
  |      |      |      |      |-- SPI_MASTER  
  |      |      |      |      |      |-- MainMaster.C&Hex SPI主机收发演示程序    
  |      |      |      |      |-- SPI_FLASH 
  |      |      |      |      |      |-- Main.C 
  |      |      |      |      |      |-- SPIFlash.C&H&Hex SPI操作外部Flash接口函数      
  |      |      |--Timer
  |      |      |      |-- Main.C:Timer0&1&2定时，计数设置和捕捉功能使用示例
  |      |      |      |-- Timer.C&H:Timer0&1&2定时，计数设置和捕捉函数定义
  |      |      |      |-- Timer.hex  
  |      |-- PUB: 评估板说明
  |      |      |-- CH543EVT.PDF: 评估板和EVT资料包说明
  |      |      |-- CH543SCH.PDF: 评估板原理图


