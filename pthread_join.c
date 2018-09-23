#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

int num = 100;  // 退出原因必须保存在全局生命周期的内存中，不能是线程的栈区。

void *thread_fun(void *arg)
{
    printf("thread id: %ld\n", pthread_self());
  
    // 线程的三种退出方式
    pthread_exit(&num);  // 可想等待回收自己的线程传递自己死亡的原因
    //exit(1);
    //return NULL;
}


int main(void)
{
    int ret = 0;
    pthread_t thread_id;
 
    ret = pthread_create(&thread_id, NULL, thread_fun, NULL);
    if (ret != 0)
    {
        printf("pthread_creat failed, error num: %d\n", ret);
        printf("%s\n", strerror(ret));  // 打印pthread_create创建线程失败的原因, 不能使用进程的error变量
        goto ERR;
    }
    printf("chi thread id: %ld\n", thread_id); 

    //sleep(2);
    //pthread_exit(NULL);  // 主线程退出，对子线程没有影响
    
    printf("main thread id: %ld\n", pthread_self());
    
    void *retval = NULL;
    pthread_join(thread_id, &retval);  // 阻塞等待子线程退出
    printf("retval = %d\n", *(int *)retval);

ERR:
    return ret;
}
