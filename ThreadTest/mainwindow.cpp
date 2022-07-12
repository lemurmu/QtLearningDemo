#include "mainwindow.h"

#include "ui_mainwindow.h"

struct ThreadClass : public QThread {
    MainWindow* main;

    void run() override {
        MyThread* thread;
        for (int i = 0; i < main->cnt; ++i) {
            thread = new MyThread(i, &main->condition, &main->mutex, &main->semaphore);
            main->vecThread.push_back(thread);
            connect(main->vecThread.at(i), &MyThread::updateProgress, main->vecProgressBar.at(i),
                    &QProgressBar::setValue);
            connect(main->vecThread.at(i), &MyThread::finished, main, [=]() {
                thread->deleteLater();
                main->vecThread[i] = nullptr;
            });
            main->vecThread.at(i)->start();
        }

        main->semaphore.acquire(main->cnt);  //获取cnt个资源
        qDebug() << "all ready";
        main->condition.wakeAll();  //唤醒所有
    }

    ThreadClass(MainWindow* _widget) :
        main(_widget)  //将主窗体传过去
    {
        qDebug() << __FUNCTION__;
    }

    ~ThreadClass() { qDebug() << __FUNCTION__; }
};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow() { delete ui; }

ThreadClass* th;

void MainWindow::on_pushButton_clicked() {
    reset();
    if (th != nullptr) {
        th->quit();
        th = nullptr;
    }

    th = new ThreadClass(this);
    connect(th, &ThreadClass::finished, th, &QObject::deleteLater);
    th->start();
    qDebug() << "Leave " << __FUNCTION__;
}

void MainWindow::init() {
    this->vecProgressBar.push_back(ui->progressBar);
    this->vecProgressBar.push_back(ui->progressBar_2);
    this->vecProgressBar.push_back(ui->progressBar_3);
    this->vecProgressBar.push_back(ui->progressBar_4);
    this->vecProgressBar.push_back(ui->progressBar_5);
    this->vecProgressBar.push_back(ui->progressBar_6);
    this->vecProgressBar.push_back(ui->progressBar_7);

    for (int i = 0; i < this->cnt; ++i) {
        this->vecProgressBar.at(i)->setValue(0);
        this->vecProgressBar.at(i)->setRange(0, 100);
    }
}

void MainWindow::reset() {
    for (int i = 0; i < cnt; i++) {
        vecProgressBar[i]->reset();
    }
    vecThread.clear();
}
