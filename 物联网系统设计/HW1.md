# MQTT.fx和阿里云平台通信

### 创建产品和设备

进入阿里云物联网平台，点击公共实例

![image-20220301162251974](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301162251974.png)

进入设备管理->产品->创建产品，以创建产品

![image-20220301162333647](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301162333647.png)

选择以下参数创建产品

![image-20220301162404915](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301162404915.png)

复制`ProductKey`，黏贴在下载的物模型中

![image-20220301162532457](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301162532457.png)

点击编辑草稿->快速导入->导入物模型以导入

![image-20220301162638675](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301162638675.png)

点击发布上线以发布物模型

![image-20220301162712785](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301162712785.png)

### 计算MQTT和阿里云链接的参数，链接阿里云

输入以下参数计算得到password

![image-20220301164031032](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301164031032.png)

输入以下参数后点击OK，再connect，此时可以在阿里云控制台观察到设备在线

![image-20220301164711046](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301164711046.png)

![image-20220301164906980](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301164906980.png)

### 利用sub订阅消息，通过pub发布消息

订阅topic

![image-20220301170449524](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301170449524.png)

MQTT接收到消息123

![image-20220301170604008](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301170604008.png)

使用MQTT发布消息，在MQTT中输入以下参数，可以在阿里云平台看到以下信息

![image-20220301171004546](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301171004546.png)

![image-20220301170952928](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301170952928.png)

### 利用Alink Json格式改变温度，闪烁数据

在MQTT中输入以下数据，上传

![image-20220301171833141](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301171833141.png)

可以发现阿里云平台上的物模型数据发生了改变

![image-20220301171901727](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220301171901727.png)



