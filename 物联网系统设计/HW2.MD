# 使用设备端连接阿里云

### 1
将空白程序写入uno板

### 2
将JP 1开关拨到右侧，JP 2开关拨到左侧

### 3

打开XCOM软件，设置波特率为115200

![image-20220308161943204](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220308161943204.png)

发送AT指令建立连接

依次输入以下指令：

`AT`

`AT+UARTE=ON`

`AT+WJAP=iQOO3,a1756127061`，将设备连接到手机热点上

`AT+WEVENT=ON`

`AT+REBOOT`，重启WIFI模块

`AT+MQTTAUTH=3213123&gw77zYa96eU,715bc7fe87634833b2af61e850fb8be5bee5ad2417f7eb00cf34735298cf756d`，设置连接的用户名与密码

`AT+MQTTCID=gw77zYa96eU.3213123|securemode=2\,signmethod=hmacsha256\,timestamp=2524608000000|`，把阿里云中的cilentID属性输入到设备端

`AT+MQTTSOCK=gf5jSDJdQ6Q.iot-as-mqtt.cn-shanghai.aliyuncs.com,1883`，输入阿里云的网络地址

`AT+MQTTAUTOSTART=OFF`

`AT+MQTTSTART`，开始连接

得到如下结果，设备端成功连接上阿里云

![image-20220308170025126](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220308170025126.png)

### 4-sub

输入以下指令，订阅阿里云上的topic，

`AT+MQTTSUB=0./gw77zYa96eU/3213123/user/get.1`

![image-20220308171903786](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220308171903786.png)

在阿里云上发送消息以测试是否订阅成功

![image-20220308172001547](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220308172001547.png)

得到结果如下，可以看到订阅成功

![image-20220308172009475](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220308172009475.png)

### 4-pub

输入如下指令以将设备端的数据发送到阿里云上

`AT+MQTTPUB=/sys/gw77zYa96eU/3213123/thing/event/property/post,1`

`AT+MQTTSEND=123,`

`{"method":"/sys/gw77zYa96eU/3213123/thing/event/property/post","id":"109342997","params":{"Frequency":17},"version":"1.0"}`

![image-20220308173211939](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220308173211939.png)

![image-20220308174542165](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220308174542165.png)

### 获取当前时间

输入以下指令获取当前时间，第一条指令调节时区，得到的结果如截图所示

`AT+SNTPCFG=+8`

`AT+SNTPTIME`

![image-20220308171410983](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220308171410983.png)

