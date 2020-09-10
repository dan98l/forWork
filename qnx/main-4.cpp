#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t semaphore;
pthread_mutex_t mut;
pthread_t thread1, thread2;

void *func_semaphore(void* args) {
    sem_wait(&semaphore);
    cout << "Hello from semaphore" << endl;
    sem_post(&semaphore);
}

void *func_mutex(void* args) {
    pthread_mutex_lock(&mut);
    cout << "Hello from mutex" << endl;
    pthread_mutex_unlock(&mut);
}

int main() {
    pthread_mutex_init(&mut, nullptr);
    timespec begin, end;

    pthread_create(&thread1, nullptr, func_semaphore, nullptr);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
    pthread_join(thread1, nullptr);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    double elapsed = end.tv_nsec - begin.tv_nsec;

    cout << "Clocks taken for semaphore: " << elapsed << endl;

    pthread_create(&thread2, nullptr, func_mutex, nullptr);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
    pthread_join(thread2, nullptr);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    elapsed = end.tv_nsec - begin.tv_nsec;

    cout << "Clocks taken for mutex: " << elapsed << endl;

    pthread_kill(thread1, 0);
    pthread_kill(thread2, 0);
    return 0;
}