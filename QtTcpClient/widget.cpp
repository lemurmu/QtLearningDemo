#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);

    this->setWindowTitle("客户端");
    this->setWindowState(Qt::WindowState::WindowNoState);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    this->setStyleSheet("font: 25 9pt 'Microsoft YaHei';");
}

Widget::~Widget() { delete ui; }

void Widget::on_openBtn_clicked() {
    tcpSocket->connectToHost(ui->iptxt->text(), ui->porttxt->text().toUInt());
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected_Solt()));
    printf("打开客户端!");
}

void Widget::on_closeBtn_clicked() {
    tcpSocket->close();
    printf("关闭客户端 ");
}

void Widget::on_sentBtn_clicked() {
    tcpSocket->write(ui->sendtxt->text().toLocal8Bit().data());
}

void Widget::connected_Solt() {
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));  //将信号连接到槽，书写比较明确
}

void Widget::readyReadSlot() {
    QString buf;
    buf = tcpSocket->readAll();
    ui->recvtxt->appendPlainText(buf);  //接收由tcp发送过来的信息
}
