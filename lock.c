/*
 *@author: Austin Cieslinski
 *lockc
 */
#include <pthread.h>
#include "lock.h"

pthread_mutex_t sharedLock;

///locks the mutex lock for all threads
int lock() {
    return pthread_mutex_lock( &sharedLock );
}

///unlocks the mutex lock for all threads
int unlock() {
    return pthread_mutex_unlock( &sharedLock );
}
