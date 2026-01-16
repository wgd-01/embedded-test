#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <atomic>

static std::atomic_ullong counter{0};

static void* waste(void*)
{
    while (1) {
        void* p = malloc(1024);
        if (p) free(p);
        ++counter;
    }
    return nullptr;
}

int main()
{
    pthread_t t[4];
    for (int i = 0; i < 4; ++i)
        pthread_create(&t[i], nullptr, waste, nullptr);

    unsigned long long last = 0;
    while (1) {
        sleep(1);
        unsigned long long curr = counter.load();
        printf("speed %llu ops/s\n", curr - last);
        last = curr;
    }
    return 0;
}

