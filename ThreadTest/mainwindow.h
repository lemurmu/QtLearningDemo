#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qboxlayout.h>

#include <QMainWindow>
#include <QMutex>
#include <QProgressBar>
#include <QPushButton>
#include <QSemaphore>
#include <QVector>
#include <QWaitCondition>
#include <QDebug>
#include <QThread>
#include <QProgressBar>

#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  public:
    Ui::MainWindow* ui;
    QWaitCondition condition;
    QMutex mutex;
    QSemaphore semaphore;

  private slots:
    void on_pushButton_clicked();

  public:
    QVector<MyThread*> vecThread;
    QVector<QProgressBar*> vecProgressBar;
    QVBoxLayout* layout;
    QPushButton* btn;
    const int cnt = 7;
    void init();
    void reset();
};
#endif  // MAINWINDOW_H
