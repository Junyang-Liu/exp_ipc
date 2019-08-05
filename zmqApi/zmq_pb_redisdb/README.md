使用hiredis连接redis，zmq pub/sub 实现

参考：
https://github.com/redis/hiredis

这里的实现成功率不算太高，要么是：
1、pub先起起来了，发数据，sub连接途中pub发完数据退出了，导致数据收不到
2、sub起起来，pub起起来发数据，sub依然在连接中，数据又没收到

ToDo：在pub发数据和退出之前读一下连接的配置，获取sub状态。

