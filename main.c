#include "dynamic_que.h"
#include "que_ctl.h"

int main()
{
    start_que_thread();
    while(1)
    {
        usleep(1);
    }
}