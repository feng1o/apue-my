#include <netdb.h>
#include "error.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>
#include "daemonize.c"

#define BUFLEN		128
#define MAXADDRLEN	256

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void serve(int sockfd)
{
	int				n;
	socklen_t		alen;
	FILE			*fp;
	char			buf[BUFLEN];
	char			abuf[MAXADDRLEN];
	struct sockaddr	*addr = (struct sockaddr *)abuf;

//	set_cloexec(sockfd);

	for (;;) {
    printf(" listen .....before ");
		alen = MAXADDRLEN;
		if ((n = recvfrom(sockfd, buf, BUFLEN, 0, addr, &alen)) < 0) {
			syslog(LOG_ERR, "ruptimed: recvfrom error: %s",
			  strerror(errno));
			exit(1);
		}
		if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
			sprintf(buf, "error: %s\n", strerror(errno));
			sendto(sockfd, buf, strlen(buf), 0, addr, alen);
		} else {
			if (fgets(buf, BUFLEN, fp) != NULL)
				sendto(sockfd, buf, strlen(buf), 0, addr, alen);
			pclose(fp);
		}
	}
}

int main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n;
	char			*host;

	if (argc != 1)
		printf("usage: ruptimed");
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX;	/* best guess */
	if ((host = (char *)malloc(n)) == NULL)
		printf("malloc error");
	if (gethostname(host, n) < 0)
		printf("gethostname error");
	//daemonize("ruptimed");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_DGRAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if ((err = getaddrinfo("127.0.0.1", "ruptime", &hint, &ailist)) != 0) {
    //需要加入、etc/service里面的  upd 
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
		  gai_strerror(err));
    printf("...exit..............\n");
		exit(1);
	}
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_DGRAM, aip->ai_addr,
		  aip->ai_addrlen, 0)) >= 0) {
    printf("ok ...............\n");
			serve(sockfd);
			exit(0);
		}
	}
	exit(1);
}
