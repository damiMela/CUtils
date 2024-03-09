#pragma once
#include <pthread.h>

namespace cutils
{
    class CThread
    {
    public:
        CThread() : threadId(0) {}

        virtual ~CThread()
        {
            if (threadId != 0)
                pthread_detach(threadId);
        }

        bool Start()
        {
            if (threadId != 0)
                return true;
            if (pthread_create(&threadId, NULL, &CThread::threadFunction, this) != 0)
                return false;
            else
                return true;
        }

        void Join()
        {
            if (threadId != 0)
                pthread_join(threadId, NULL);
        }

    private:
        pthread_t threadId;

        static void *threadFunction(void *arg)
        {
            CThread *thread = static_cast<CThread *>(arg);
            thread->_Run();
            return NULL;
        }

        virtual void _Run() = 0; // Pure virtual function to be overridden by derived classes
    };
};