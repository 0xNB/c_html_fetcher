#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define RESPONSE_RECV_LIMIT 500000
#define SOURCE_START_IDENTIFIER "<!DOCTYPE>"
#define SOURCE_START_IDENTIFIER2 "<html>"
#define PORT     "80"

char* fetchSource(char*, char*);
