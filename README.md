
# http gm server
## 依赖
一个基于asio standalone, http parser和json的 http server，主要用来处理gm指令
1. asio https://github.com/chriskohlhoff/asio 需要用1.12以后的版本 因为他根据cpp 20改了接口
2. http parser https://github.com/nodejs/http-parser 对应的代码已经内嵌
3. json https://github.com/nlohmann/json

编译选项开启cpp 17， cmake编译时需要传入-DASIO_DIR,来指定asio.hpp所在的文件夹。

## 使用方法

参考test/test.cpp 绑定一个端口，启动http服务器，接收的请求需要为json的object。
里面需要有两个字段，一个是method 值为string， 一个是params 值为json map。收到请求之后，服务端会根据method查找对应的gm_handler来处理，然后返回结果。
如果返回的状态码是ok的话，返回结果的body是一个json dict， 里面有两个字段：
1. suc 这个字段对应的值为bool 代表这个指令是否执行成功
2. reply 字段 代表指令返回的详细结果 是一个json 值
