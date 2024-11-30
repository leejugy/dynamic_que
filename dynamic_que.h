#ifndef __DYNAMIC_QUE__
#define __DYNAMIC_QUE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <semaphore.h>

typedef struct list_t
{
    size_t buf_size;
    uint8_t *buf;
    struct list_t *next;
}list_t;

typedef struct
{
    list_t *front;
    list_t *rear;
    sem_t sem;
}dynamic_que_t;

void init_que(dynamic_que_t *q);
void push_que(dynamic_que_t *q, uint8_t *buffer, size_t buffer_size);
int pop_que(dynamic_que_t *q, uint8_t *buffer, size_t buffer_size);

#endif