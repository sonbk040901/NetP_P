#ifndef CONNECT_H_
#define CONNECT_H_
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include "tienlen.h"
#include "request.h"
#include "response.h"
void test()
{
    sizeof(Req);
    sizeof(ReqT);
    sizeof(Response);
    sizeof(CLUB);
    sizeof(ReqD);
    Req req;
    sizeof(req.data.play.cards);
}
#endif // CONNECT_H_