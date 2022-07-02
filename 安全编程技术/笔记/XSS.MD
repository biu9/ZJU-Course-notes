### 反射型XSS

> 反射型XSS将用户输入的内容作为代码让浏览器执行以达到攻击目的，一般需要让用户访问攻击者构造的URL

##### WebGoat XSS lab5

在搜索框中输入`<script>alert("attack!");</script>`,别的用户点击搜索时会受到攻击

### XST

> cross-site tracing；跨站式追踪攻击
>
> 客户端发送trace / track请求至服务器；如果服务器实现了trace 、 track响应，则在response body里会返回此次请求的完整头信息，通过这种方式，客户端可以获取某些敏感的header字段

