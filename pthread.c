#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>


void *thread_fun(void *arg)
{
    printf("thread id: %ld\n", pthread_self());

    return NULL;
}


int main(void)
{
    int ret = 0;
    pthread_t thread_id;
 
    ret = pthread_create(&thread_id, NULL, thread_fun, NULL);
    if (ret != 0)
    {
        printf("pthread_creat failed, error num: %d\n", ret);
        printf("%s\n", strerror(ret));
        goto ERR;
    }
    printf("chi thread id: %ld\n", thread_id); 
    
    sleep(2);  // 测试主线程的生命周期和子线程生命周期的关系，可以将该行注释来测试主次线程生命周期的相互影响。
    printf("main thread id: %ld\n", pthread_self());

ERR:
    return ret;
}

