试用一下boost/interprocess库

====helloworld====
遇到文件依赖问题
![Image text](https://s2.ax1x.com/2019/08/01/eNHVL6.png)

1、undefined reference to `shm_open' 解决方式：
g++ -c -Wall file_cpp // .cpp -> .o
g++ -I /usr/lib/x86_64-linux-gnu/ file_0 -o file -lrt // .o -> 可执行文件
参考：
https://stackoverflow.com/questions/48410966/undefined-reference-to-shm-open

2、undefined reference to `shm_unlink' 解决方式：
g++ -I /usr/lib/x86_64-linux-gnu/ file_0 -o file -lrt -lpthread // .o -> 可执行文件
参考：
https://stackoverflow.com/questions/19901934/libpthread-so-0-error-adding-symbols-dso-missing-from-command-line

