#pragma once

#include <pthread.h>

namespace cutils
{
    class CThreadLock //: public CObject
    {
    public:
        inline CThreadLock()
        {
            pthread_mutexattr_init(&_attr);
            pthread_mutexattr_settype(&_attr, PTHREAD_MUTEX_RECURSIVE);
            pthread_mutex_init(&_lock, &_attr);
        }
        inline ~CThreadLock()
        {
            pthread_mutex_destroy(&_lock);
            pthread_mutexattr_destroy(&_attr);
        }
        inline void Lock() { pthread_mutex_lock(&_lock); }
        inline void Unlock() { pthread_mutex_unlock(&_lock); }

    private:
        pthread_mutex_t _lock;
        pthread_mutexattr_t _attr;

    private:
        CThreadLock(const CThreadLock &);
        CThreadLock &operator=(const CThreadLock &);
    };

    template <class T>
    class CScopeLock
    {
    public:
        inline CScopeLock(T &lock) : _lock(lock) { _lock.Lock(); }
        inline ~CScopeLock() { _lock.Unlock(); }

    private:
        T &_lock;
    };
}