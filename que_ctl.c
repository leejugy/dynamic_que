#include "que_ctl.h"
#include "dynamic_que.h"

dynamic_que_t q;

static void thread_pop()
{
    int ret = 0;
    char recv_buffer[128] = {0, };
    while (1)
    {
        memset(recv_buffer, 0, sizeof(recv_buffer));
        ret = pop_que(&q, recv_buffer, sizeof(recv_buffer));
        if(ret > 0)
        {
            printf("[we recv]%s\n", recv_buffer);
        }
        else
        {
            sleep(5);
        }
    }
}

static void thread_push()
{
    char send_buffer[128] = {0, };
    while(1)
    {
        memset(send_buffer, 0, sizeof(send_buffer));
        fgets(send_buffer, sizeof(send_buffer), stdin);
        strtok(send_buffer, "\n");
        push_que(&q, send_buffer, sizeof(send_buffer));
    }
}

void start_que_thread()
{
    pthread_t tid[QUE_THREAD] = {0, };
    void (*function_pointer[QUE_THREAD]) = {thread_pop, thread_push};

    int ret = 0;
    uint8_t i = 0;

    init_que(&q);

    for(i = 0; i < QUE_THREAD; i++)
    {
        ret = pthread_create(&tid[i], NULL, function_pointer[i], NULL);
        if(ret < 0)
        {
            perror("thread create");
        }

        ret = pthread_detach(tid[i]);
        if(ret < 0)
        {
            perror("thread detach");
        }
    }
}