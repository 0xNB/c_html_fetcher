#include "fetchSource.h"

char* fetchSource(char* hostname, char* filename) {
	char response[RESPONSE_RECV_LIMIT + 1]; // we use one char more for null
	char *source;
	int sockfd, newfd, err;
	char ip[INET6_ADDRSTRLEN];
	struct addrinfo *p, hints, *res;
	int len, len_s;
	int yes = 1;
	//struct socketaddr_storage their_addr;
	socklen_t addr_size;
	void *addr;
	char *ver;
	char request[100];
	char* null_terminator = malloc(sizeof(char));
	*null_terminator = '\0';

	sprintf(request, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", filename, hostname);
	printf("%s\n\n", request);	// print the request we are making

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_family=AF_UNSPEC;

	if ((err = getaddrinfo(hostname, PORT, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		return NULL;
	}
	for(p=res; p!=NULL; p=p->ai_next) {
		if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			printf("Socket error.\n");
			return(NULL);
		}
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}
	}
	if(send(sockfd, request, strlen(request), 0) < strlen(request)) {
		perror("Error while sending.");
	}

	//freeadrinfo(res);
	ssize_t _nmbts = 0;

	_nmbts = recv(sockfd, response, RESPONSE_RECV_LIMIT, 0);
	printf("%zd bytes read", _nmbts);

	response[_nmbts] = '\0';
	close(sockfd);

	printf("%s", response);
	source = strstr(response, SOURCE_START_IDENTIFIER);

	if(source == NULL) {
		source = strstr(response, SOURCE_START_IDENTIFIER2);
	}
	if(source == NULL) {
		source = response;
	}

	printf("%s\n", source);

	return source;
}
