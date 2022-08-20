//
// Created by sjhuang on 2022/8/18.
//

#ifndef WEB_SERVER_LOCK_H
#define WEB_SERVER_LOCK_H
#include <semaphore.h>
#include <pthread.h>
#include <exception>

class sem{
public:
    sem(){
        if(sem_init(&m_sem, 0, 0)! =0){
            throw std::exception();
        }
    }
    sem(int num){
        if(sem_init(&m_sem, 0, num)! =0){
            throw std::exception();
        }
    }
    ~sem(){
        sem_destroy(&m_sem);
    }

    bool p(){
        sem_wait(&m_sem) == 0;
    }

    bool v(){
        sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
};


class locker{
public:
    locker(){
        if(pthread_mutex_init(&m_mutex, nullptr) != 0){
            return std::exception();
        }
    };
    ~locker(){
        pthread_mutex_destroy(&m_mutex);
    };

    bool lock(){
        return pthread_mutex_lock(&m_mutex) == 0;
    }

    bool unlock(){
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

private:
    pthread_mutex_t m_mutex;
};

#endif //WEB_SERVER_LOCK_H
