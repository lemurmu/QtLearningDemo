#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

private slots:
  void on_connectBtn_clicked();
  void on_disConnectBtn_clicked();
  void on_sendBtn_clicked();
  void newConnection_Slot();
  void readyRead_Slot();

public:
  QTcpServer *tcpServer;
  QTcpSocket *tcpSocket;


};
#endif // WIDGET_H
