#include <bits/stdc++.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


using namespace std;

pthread_t thread1, thread2;
int sem_var = 2;
int t = 10;

void handler1(int signum)
{
    cout << "signal received by thread1" << endl;
    fflush(stdout);
    t--;
    pthread_kill(thread2, SIGUSR2);
}

void handler2(int signum)
{
    cout << "signal received by thread2" << endl;
    fflush(stdout);
    t--;
    pthread_kill(thread1, SIGUSR1);
}

void *reader(void *p)
{
    signal(SIGUSR1, handler1);
    sem_var-- ;
    while (t);
}

void *writer(void *p)
{
    signal(SIGUSR2, handler2);
    sem_var-- ;
    while (t);
}

int main()
{
    int arg;
    pthread_create(&thread1, NULL, reader, (void *)&arg);
    pthread_create(&thread2, NULL, writer, (void *)&arg);

    while (sem_var)   ;
    pthread_kill(thread1, SIGUSR1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}





