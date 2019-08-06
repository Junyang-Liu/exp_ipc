#include <hiredis/hiredis.h> 
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/time.h>

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

    printf("SUBSCRIBE--start run\n");
    redisReply *reply;
    bool run = true;

    while(run)
    {
        // ToDo:这里应该是错误的用法,具体SUBSCRIBE返回reply要怎么用,返回数据的模式是什么样子的,待了解
        reply = (redisReply*)redisCommand(contextTmp,"SUBSCRIBE channelTmp");
        if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3)
        {
            for (int i = 0; i < reply->elements; i++)
            {   
                if (reply->element[i]->str)
                {
                    // 处理接收到的数据
                    // printf("%s\n", reply->element[i]->str);
                }
                else
                {
                    // 
                    struct timeval start, end;
                    gettimeofday( &start, NULL );
                    printf("start : %d.%d\n", start.tv_sec, start.tv_usec);
                    
                    printf(" no message... sleep 1 second... \n");
                    sleep(1);
                    //
                    
                    gettimeofday( &end, NULL );
                    printf("end   : %d.%d\n", end.tv_sec, end.tv_usec);
                    
                }
            }
        }
        else
        {   
            // run = false;
        }
        freeReplyObject(reply);
        
        // sleep(1);
    }
    printf("SUBSCRIBE--end run\n");
    
    return 0;
}
