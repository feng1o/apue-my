#include <netdb.h>
#include <syslog.h>
#include <sys/socket.h>
#include "unistd.h"
#include "error.h"
#include "tellwait.h"

//#include "daemonize.c"

#define BUFLEN	128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void serve(int sockfd)
{
    printf("serve..................\n");
	int		clfd;
	FILE	*fp;
	char	buf[BUFLEN];

//	set_cloexec(sockfd);

	for (;;) {
		if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
			syslog(LOG_ERR, "ruptimed: accept error: %s",
			  strerror(errno));
			exit(1);
		}
//		set_cloexec(clfd);
    
		if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clfd, buf, strlen(buf), 0);
		} else {
			while (fgets(buf, BUFLEN, fp) != NULL)
				send(clfd, buf, strlen(buf), 0);
printf("send ok\n");
			pclose(fp);
		}
		close(clfd);
	}
}

int main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n;
	char			*host;

	if (argc != 1)
		err_quit("usage: ruptimed");
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX;	/* best guess */
//    printf("host namelength = %d\n", n);
	if ((host = (char *)malloc(n)) == NULL)
		printf("malloc error");
	if (gethostname(host, n) < 0)
		printf("gethostname error");
    
    printf("host name = %s\n", host);
	//daemonize("ruptimed");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
//    printf("................................\n");

	if ((err = getaddrinfo("127.0.0.1", "ruptime", &hint, &ailist)) != 0) {
    // host改为了127.0.0.1 ，获取的可能无法getaddrinfo，见youdaonote记录，可能需要设置etc/service里面的 
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
		  gai_strerror(err));
        printf("exit 1111 %s\n",gai_strerror(err));
		exit(1);
	}
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
		  aip->ai_addrlen, QLEN)) >= 0) {
          printf("serve before \n");
			serve(sockfd);
			exit(0);
		}
	}
	exit(1);
    return 0;
}
