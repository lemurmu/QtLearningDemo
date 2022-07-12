#include "mythread.h"

MyThread::MyThread(int _index, QWaitCondition* _condition, QMutex* _mutex, QSemaphore* _semaphore, QObject* parent) :
    QThread(parent), index(_index), condition(_condition), mutex(_mutex), semaphore(_semaphore) {
    //    this->condition=_condition;
    //    this->mutex=_mutex;
    //    this->semaphore=_semaphore;
    //可以输出函数的宏 :__FUNCTION__

    qDebug() << __FUNCTION__ << " : " << index;
}

MyThread::~MyThread() { qDebug() << __FUNCTION__ << " : " << index; }

/* QWaitCondition 用于多线程的同步，一个线程调用QWaitCondition::wait()
 *阻塞等待，直到另一个线程调用QWaitCondition::wake() 唤醒才继续往下执行。 QSemaphore
 *用于保护一定数量的相同资源。信号支持两种基本操作：获取资源 acquire()和释放资源 release()
 *
 *
 * QMutex类提供的是线程之间的访问顺序化。
 * QMutex的目的是保护一段代码，使得同一时间只有一个线程可以访问它。但在一个线程中调用lock()，
 * 其它线程将会在同一地点试图调用lock()时会被阻塞，直到这个线程调用unlock()之后其它线程才会获得这个锁。
 *
 *信号量QSemaphore可以理解为对互斥量QMutex功能的扩展，互斥量只能锁定一次而信号量可以获取多次，它可以用来保护一定数量的同种资源。
 *acquire()函数用于获取n个资源，当没有足够的资源时调用者将被阻塞直到有足够的可用资源。release(n)函数用于释放n个资源。
 *
 * QSemaphore sem(5); // sem.available() == 5
 * sem.acquire(2); // sem.available() == 0
 * sem.release(5); // sem.available() == 5
 * sem.release(5); // sem.available() == 10
 * sem.tryAcquire(1); // sem.available() == 9, returns true
 * sem.tryAcquire(250); // sem.available() == 9, returns false
 *
 * acquire()从该信号量守护的资源中获取n个资源。如果获取的资源数目大于available()返回值，那么该调用将阻塞，直到可获取足够的资源数。
 */
void MyThread::doSomething() {
    mutex->lock();  //同步锁 类似c#的lock关键字
    qDebug() << index << ":enter wait block";
    semaphore->release(1);   //释放一个资源
    condition->wait(mutex);  //先解锁mutex，使其他线程能够使用mutex
    mutex->unlock();
    qDebug() << index << ":start";
    nProgress = 0;
    for (;;) {
        msleep(1000);
        nProgress += generator->bounded(1, 10);  //产生1,20的随机数
        if (nProgress >= 100) {
            nProgress = 100;
            emit updateProgress(nProgress);
            break;
        } else {
            emit updateProgress(nProgress);
        }
    }

    qDebug() << index << ":finished";
}

void MyThread::run() { doSomething(); }
