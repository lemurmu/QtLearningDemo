#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QMutex>
#include <QRandomGenerator>
#include <QSemaphore>
#include <QThread>
#include <QWaitCondition>
#include <QDebug>

class MyThread : public QThread {
    Q_OBJECT
  public:
    /* QWaitCondition类提供了一个用于同步线程的条件变量
     * QMutex类提供线程之间的访问序列化(互斥锁）
     * QSemaphore类提供了一个通用的计数信号量
     */
    MyThread(int _index, QWaitCondition* _condition, QMutex* _mutex, QSemaphore* _semaphore, QObject* parent = nullptr);
    ~MyThread();
  signals:
    void updateProgress(int);

  public:
    void doSomething();

    void run() override;

    QWaitCondition* condition;
    QMutex* mutex;
    QSemaphore* semaphore;
    int index;

  private:
    int nProgress = 0;
    QRandomGenerator* generator = QRandomGenerator::global();  //随机数发生器
};

#endif  // MYTHREAD_H
