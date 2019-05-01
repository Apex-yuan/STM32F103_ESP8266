# ESP8266(ESP-01)模块驱动程序

- APP/ap_test: ESP8266模块工作在AP server模式

- APP/sta_test: ESP8266模块工作在STA server模式

- APP/ap_sta_test: ESP8266模块工作在AP server+STA server模式

  ### AP(Access Point)模式：

  ---

  **将ESP8266设置一个热点，手机电脑等可直接连接：**

  - **1.**AT+RST    复位

  - **2.**AT+CWMODE=2  设置为AP模式

  - **3.**AT+RST  复位，使AP模式生效

  - **4.**AT+CWSAP=”ESP8266","123456",1,4    设置模块的热点名称和密码

  - **5.**AT+CIPMUX=1  启动多连接模式

  - **6.**AT+CIPSERVER=1,8086  设置本地的端口号，连接的时候需要用到该端口号

  - **7.**AT+CIPSTO=5000  设置超时时间

  - **8.**AT+CIFSR  获取本地的IP地址
    
    配置完这些之后，连上该热点后，就可以通过网络调试助手，与该模块进行通信了。

  ### STA(Station)模式：

  ---

  。。。

  ### AP+STA模式：

  ---

  。。。