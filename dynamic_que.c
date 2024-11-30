#include "dynamic_que.h"

void init_que(dynamic_que_t *q)
{
    int ret = sem_init(&q->sem, 0, 1);
    if(ret < 0)
    {
        perror("sem init");
    }

    q->front = (list_t *)malloc(sizeof(list_t));
    q->rear = q->front;
}

void push_que(dynamic_que_t *q, uint8_t *buffer, size_t buffer_size)
{
    q->rear->buf = (uint8_t *)malloc(buffer_size * sizeof(uint8_t));
    q->rear->next = (list_t *)malloc(sizeof(list_t));

    memcpy(q->rear->buf, buffer, buffer_size);
    q->rear->buf_size = buffer_size;
    q->rear = q->rear->next;
}

int pop_que(dynamic_que_t *q, uint8_t *buffer, size_t buffer_size)
{
    list_t *temp = q->front;
    int len = temp->buf_size;
    if(q->front == q->rear)
    {
        //printf("que is null\n");
        return -1;
    }

    if(q->front->buf_size > buffer_size)
    {
        printf("pop que size error\n");
        return -1;
    }

    memcpy(buffer, q->front->buf, q->front->buf_size);

    q->front = q->front->next;
    temp->next = NULL;
    
    free(temp->buf);
    free(temp);

    return len;
}