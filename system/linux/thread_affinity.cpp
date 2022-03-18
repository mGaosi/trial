/**
 * @file thread_affinity.cpp
 * @author Jiangjie Gao (gaojiangjie@live.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-18
 * 
 * 
 */

#include <iostream>
#include <thread>
#include <future>

#include <pthread.h>
#include <sched.h>

void idle()
{
    uint64_t u = 0;
    while (true)
    {
        ++u;
    }
}

// Driver code
int main(int argc, char* args[])
{
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET_S(6, sizeof(set), &set);
    sched_setaffinity(0, sizeof(set), &set);
    auto fu = std::async(
        []()
        {
            cpu_set_t set;
            CPU_ZERO(&set);
            CPU_SET(0, &set);
            pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
            uint64_t u = 0;
            while (true)
            {
                ++u;
            }
        });
    std::thread thread1(idle);
    std::thread thread2(idle);
    uint64_t u = 0;
    while (true)
    {
        ++u;
    }
}
