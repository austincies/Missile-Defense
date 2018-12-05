#include <pthread.h>
#include "lock.h"

pthread_mutex_t sharedLock;

int lock() {
    return pthread_mutex_lock( &sharedLock );
}

int unlock() {
    return pthread_mutex_unlock( &sharedLock );
}
