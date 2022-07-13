#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

  public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
    QTcpSocket *tcpSocket;

  private:
    Ui::Widget* ui;

private slots:
    void  on_openBtn_clicked();
    void  on_closeBtn_clicked();
    void  on_sentBtn_clicked();
    void  connected_Solt();
    void  readyReadSlot();

};
#endif  // WIDGET_H
