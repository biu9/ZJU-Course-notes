## lab1.1

### 安装java

由于我的电脑上本来就装好了Java，这里演示一下安装完成的效果

![image-20220510191626583](lab1.1&1.2.assets/image-20220510191626583.png)

### 安装tomcat

1. 在官网上下载对应版本的安装包

   ![image-20220510195257718](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510195257718.png)

2. 编辑环境变量

   ![image-20220423190834469](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220423190834469.png)

3. 启动tomcat

   ![image-20220423203113258](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220423203113258.png)

4. 观察结果![image-20220423203133288](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220423203133288.png)

### 安装eclipse

1. 在官网上下载安装包并安装

2. 开发hello world

   ![image-20220423212436865](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220423212436865.png)

## lab1.2

### 应用场景

个人博客

### 个人程序是怎么设计的

- 前端：React+Typescript
- 后端：tomcat+mysql
- 服务器：腾讯云轻量应用服务器+TencentDB

### 数据库

##### 前端访问api以及数据库访问

一共有如下api

- `/api/uploadBlog`；这个api用于上传文章，上传的同时还会生成一张新的表用于储存这篇文章的评论数据

  ![image-20220510200318842](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510200318842.png)

- `/api/login`；这个api用于登录，实现了管理员登录，登录后能在home上传文章的功能

  ![image-20220510200338593](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510200338593.png)

- `/api/getPosts`；这个api用于访问`blog_content`表，用于获取文章内容

  ![image-20220510200355214](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510200355214.png)

- `/api/getComments`；这个api用于获取评论数据

  ![image-20220510200407983](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510200407983.png)

- `/api/postComments`；用于上传评论数据

  ![image-20220510200426839](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510200426839.png)

### 数据库设计

使用`blog_content`表储存文章数据，这个表中有id，title，time，content，tags等列，其中id是主键，当我通过`/api/postBlog`上传文章时，后端会同步在数据库中生成一张`comment_${id}`的表，这样就实现了每篇文章的评论区都相互对应

`comment_${id}`的表中则有id，name，content等列，用于储存用户的评论信息

### 部署网站

运行`npm run build`打包项目，设置`homepage:'.'`；将打包好的文件发布到服务器上，tomcat的`server.xml`的相应配置如下：

```xml
<Context path="" docBase="/usr/src/sp2022/apache-tomcat-10.0.20/webapps/blog" debug="0" reloadable="true" />
```

现在可以访问`http://124.220.6.76`来观察效果

### 实现截图

网站首页

![image-20220510201643293](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510201643293.png)

文章界面

![image-20220510201700007](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510201700007.png)

评论部分

![image-20220510201748963](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510201748963.png)

home界面

![image-20220510201724127](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220510201724127.png)

