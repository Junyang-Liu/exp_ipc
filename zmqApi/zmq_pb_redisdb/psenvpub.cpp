#include <hiredis/hiredis.h> 
#include "zhelpers.hpp"
#include <iostream>
#include <string>

int main () {
    // 连接redis
    redisContext *contextTmp = redisConnect("127.0.0.1", 6379);
    if (contextTmp == NULL || contextTmp->err) {
        if (contextTmp) {
            printf("Error: %s\n", contextTmp->errstr);
            // handle error
        } else {
            printf("Can't allocate redis contextTmp\n");
        }
        return -1;
    }
    printf("redisConnect success\n");

    //  Prepare our context and publisher
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5563");

    redisReply *reply;
    int index = 0;
    bool run = true;
    while (run) {
        std::string strTmp= "lrange TmpDataSet ";
        // 取100条
        strTmp += std::to_string(index) + " " + std::to_string(index+99);
        printf("pub %s\n",strTmp.c_str());
        reply = (redisReply*)redisCommand(contextTmp,(char*)strTmp.data());
        if (reply->element != NULL)
        {   for (int i = 0; i < reply->elements; ++i)
            {
            s_sendmore (publisher, std::to_string(i+index));
            s_send (publisher, reply->element[i]->str);
            }
        }
        else
        {
            printf("reply element NULL\n");
        }

        if ( reply->elements < 100)
        {
            s_sendmore (publisher, "finish");
            s_send (publisher, "bye~");

            printf("pub finish \n");
            run = false;
            sleep(60);
        }
        else
        {
            index += 100;
        }

        freeReplyObject(reply);
    }
    return 0;
}
