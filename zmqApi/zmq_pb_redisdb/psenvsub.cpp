#include "zhelpers.hpp"
#include <unistd.h>
#include <sys/time.h>

int main () {
    //  Prepare our context and subscriber
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
    // 有就拉下来，不过滤
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0);

    // 时间相关
    struct timeval start, end;

    bool isFirstTime = true;
    bool run = true;
    while (run) {
 
		//  Read envelope with address
		std::string address = s_recv (subscriber);
		//  Read message contents
		std::string contents = s_recv (subscriber);
		
        // 处理接收到的数据
        std::cout << "[" << address << "] " << contents << std::endl;
        if(isFirstTime)
        {
            // 开始时间
            gettimeofday( &start, NULL );
            printf("start : %d.%d\n", start.tv_sec, start.tv_usec);
            isFirstTime = false;
        }
        if (address.compare("finish") == 0)
        {
            printf("s_recv finish \n");
            // 结束时间打印下
            gettimeofday( &end, NULL );
            printf("end   : %d.%d\n", end.tv_sec, end.tv_usec);
            run = false;
        }
    }
    return 0;
}
