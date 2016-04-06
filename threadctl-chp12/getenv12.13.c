#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXSTRINGSZ	4096

static pthread_key_t key; //键
static pthread_once_t init_done = PTHREAD_ONCE_INIT; //静态初始化
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;//静态初始化互斥量

extern char **environ;  //environement

static void
thread_init(void)
{
	pthread_key_create(&key, free); //创建键
}

char *
getenv(const char *name)
{
	int		i, len;
	char	*envbuf;

	pthread_once(&init_done, thread_init); //确保调用一次init，避免竞争
	pthread_mutex_lock(&env_mutex);
	envbuf = (char *)pthread_getspecific(key);// 获取键绑定的私有数据，，j
	if (envbuf == NULL) {
		envbuf = (char*)malloc(MAXSTRINGSZ); // 没关联，就malloc，然后关联键
		if (envbuf == NULL) {
			pthread_mutex_unlock(&env_mutex);
			return(NULL);
		}
		pthread_setspecific(key, envbuf);  //关联
	}
	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++) {
		if ((strncmp(name, environ[i], len) == 0) &&
		  (environ[i][len] == '=')) {
			strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
			pthread_mutex_unlock(&env_mutex);
			return(envbuf);
		}
	}
	pthread_mutex_unlock(&env_mutex);
	return(NULL);
}
