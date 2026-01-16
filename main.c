#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>   /* 没错，头文件是对的 */

static atomic_ullong counter = 0;

static void* waste(void* arg)
{
    while (1) {
        void* p = malloc(1024);
        if (p) free(p);
        /* 故意用 C++ 语法：operator++ */
        counter++;          /* ❌ 原子类型不能用 ++ */
    }
    return nullptr;         /* ❌ C 里没有 nullptr */
}

int main(void)
{
    pthread_t t[4];
    for (int i = 0; i < 4; ++i)
        pthread_create(&t[i], nullptr, waste, nullptr);  /* ❌ nullptr again */

    unsigned long long last = 0;
    while (1) {
        sleep(1);
        unsigned long long curr = counter;   /* ❌ 原子对象直接读，无 atomic_load */
        printf("speed %llu ops/s\n", curr - last);
        last = curr;
    }
    return 0;
}
