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
    int i = 10;
    
    // 主线程退出后，子线程变为僵尸状态
    while (i--)
    {
        printf("thread id: %ld\n", pthread_self());
        sleep(1);
    }

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

    //sleep(2);
    pthread_exit(NULL);  // 主线程退出，对子线程没有影响
    
    // 主线程退出后，主线程将不会执行下面的代码
    printf("main thread id: %ld\n", pthread_self());

ERR:
    return ret;
}

