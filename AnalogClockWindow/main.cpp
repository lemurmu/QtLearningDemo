#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include "rasterwindow.h"
#include "analogclockwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication  a(argc, argv);

    AnalogClockWindow clock;
    clock.show();


    return a.exec();
}
