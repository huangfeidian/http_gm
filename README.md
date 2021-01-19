
# http gm server
## 依赖
1. http_server https://github.com/huangfeidian/http_server 


## 使用方法

参考test/test.cpp 绑定一个端口，启动http服务器，接收的请求需要为json的object。
里面需要有两个字段，一个是method 值为string， 一个是params 值为json map。收到请求之后，服务端会根据method查找对应的gm_handler来处理，然后返回结果。
如果返回的状态码是ok的话，返回结果的body是一个json dict， 里面有两个字段：
1. suc 这个字段对应的值为bool 代表这个指令是否执行成功
2. reply 字段 代表指令返回的详细结果 是一个json 值
