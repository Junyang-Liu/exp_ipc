#include <hiredis/hiredis.h> 
#include <iostream>

int main()
{
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

	redisReply *reply;
	// 取list “1” 中 0->3 个
	reply = (redisReply*)redisCommand(contextTmp,"lrange 1 0 3");
	if (reply->element != NULL)
	{	for (int i = 0; i < reply->elements; ++i)
		{
			printf("%s\n", reply->element[i]->str);
		}
	}
	freeReplyObject(reply);
	return 0;
}
