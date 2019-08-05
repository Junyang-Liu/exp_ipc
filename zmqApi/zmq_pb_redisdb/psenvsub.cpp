#include "zhelpers.hpp"

int main () {
    //  Prepare our context and subscriber
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");
    // 有就拉下来，不过滤
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0);

    bool run = true;
    while (run) {
 
		//  Read envelope with address
		std::string address = s_recv (subscriber);
		//  Read message contents
		std::string contents = s_recv (subscriber);
		
        // 处理接收到的数据
        // std::cout << "[" << address << "] " << contents << std::endl;
        if (address.compare("finish") == 0)
        {
            printf("s_recv finish \n");
            run = false;
        }
    }
    return 0;
}
