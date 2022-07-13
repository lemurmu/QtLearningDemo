#include "widget.h"

#include <QStyle>

#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->tcpServer = new QTcpServer(this);
    this->tcpSocket = new QTcpSocket(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection_Slot()));

    this->setWindowTitle("服务端");
    this->setWindowState(Qt::WindowState::WindowNoState);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    this->setStyleSheet("font: 25 9pt 'Microsoft YaHei';");
}

Widget::~Widget() { delete ui; }

void Widget::on_connectBtn_clicked() {
    tcpServer->listen(QHostAddress::Any, ui->portnum->text().toUInt());
    ui->receivewd->appendPlainText("开始监听:" + ui->portnum->text());
    ui->connectBtn->setEnabled(false);
    ui->disConnectBtn->setEnabled(true);
}

void Widget::on_disConnectBtn_clicked() {
    tcpServer->close();
    ui->connectBtn->setEnabled(true);
    ui->disConnectBtn->setEnabled(false);
}

void Widget::on_sendBtn_clicked() { tcpSocket->write(ui->sendwd->text().toLocal8Bit().data()); }

void Widget::newConnection_Slot() {
    tcpSocket = tcpServer->nextPendingConnection();  //获取已经连接的客户端嵌套字
    QString ip = tcpSocket->peerAddress().toString();
    ip = ip.replace("::ffff:", "");
    int port = tcpSocket->peerPort();

    ui->receivewd->appendPlainText(QString("[%1:%2] %3").arg(ip).arg(port).arg("客户端上线"));

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead_Slot()));
}

void Widget::readyRead_Slot() {
    QString buf;
    buf = tcpSocket->readAll();
    ui->receivewd->appendPlainText(buf);
}
