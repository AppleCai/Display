一：D:\ws\server_png
1.server用for(;;)永远不会关。
2.client是循环读取所有文件后，会断开socket连接。

应该client可以添加一个标志位，让它传完所有帧后断开连接。
二：D:\ws\server_prokey_new
采用了c++类进行重构设计，添加了HMIctrl的策略模式，有serverEx的继承类，有虚类重写，有全局变量，有函数传参数，有一个类引用另外一个类。