#include "analogclockwindow.h"

AnalogClockWindow::AnalogClockWindow() {
    setTitle("Analog Clock");
    resize(400, 300);

    m_timerId = startTimer(1000);
}

void AnalogClockWindow::timerEvent(QTimerEvent* event) {
    if (event->timerId() == m_timerId)
        renderLater();
}

//渲染
void AnalogClockWindow::render(QPainter* p) {
    static const QPoint hourHand[3] = {QPoint(7, 8), QPoint(-7, 8), QPoint(0, -40)};    //时针点
    static const QPoint minuteHand[3] = {QPoint(7, 8), QPoint(-7, 8), QPoint(0, -70)};  //分针点

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    p->setRenderHint(QPainter::Antialiasing);  //设置抗锯齿绘制

    p->translate(width() / 2, height() / 2);  //重新定义坐标原点，为窗口的中心点，默认是左上角

    int side = qMin(width(), height());    // 300
    p->scale(side / 200.0, side / 200.0);  //修改格子刻度 400/200=2 默认是1

    p->setPen(Qt::NoPen);
    p->setBrush(hourColor);

    QTime time = QTime::currentTime();

    //此时保存，保存了QPainter的颜色和钢笔的状态
    p->save();  //保存当前绘制状态（将状态推送到堆栈上）。save（）后面必须跟一个相应的restore
    p->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));  //顺时针旋转多少度 时针的每一个角度为360/12=30
    p->drawConvexPolygon(hourHand, 3);                         //绘制多边形
    p->restore();  //恢复QPainter对象的状态为之前保存时候的状态。可以再次使用QPainter对象

    p->setPen(hourColor);  //设置笔为时针颜色

    for (int i = 0; i < 12; ++i) {
        p->drawLine(76, 0, 86, 0);
        p->rotate(30.0);  //每次旋转30 这个应该是没有restore 所以旋转角度是上次的角度+30 就一直累积
    }

    int angle = 0;
    QPoint point(96, 0);  //从(100,0)开始填文字
    for (int k = 0; k < 12; ++k) {
        if (k + 3 > 12) {
            p->drawText(point.x() - 5, point.y() - 5, 12, 11, Qt::AlignCenter, QString("%1").arg(k + 3 - 12));
        } else {
            p->drawText(point.x() - 5, point.y() - 5, 12, 11, Qt::AlignCenter, QString("%1").arg(k + 3));
        }
        point = CustomRotate(point, angle, 30);
        angle -= 30;
    }

    p->setPen(Qt::NoPen);      // no line at all 没得线条
    p->setBrush(minuteColor);  //分针颜色 实心画刷填充
    p->save();
    p->rotate(6.0 * (time.minute() + time.second() / 60.0));  //分针旋转 360/60=6
    p->drawConvexPolygon(minuteHand, 3);
    p->restore();

    p->setPen(minuteColor);

    //设置分针
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            p->drawLine(82, 0, 86, 0);
        p->rotate(6.0);
    }
}

/*  point: 文字所在的点
 *  from_angle : 文字所在的度数
 *  rotate : 需要旋转的角度,值为-360~360(为负数表示逆时针旋转,为正数表示顺时针旋转)
 */
QPoint AnalogClockWindow::CustomRotate(QPointF point, qreal from_angle, qreal rotate) {
    qreal PI = 3.141592653589;
    QPointF Tmp;
    qreal arc = (rotate - from_angle) / 180 * PI;
    qreal Length = qSqrt(point.x() * point.x() + point.y() * point.y());
    Tmp.setX(Length * qCos(arc));
    Tmp.setY(Length * qSin(arc));
    return Tmp.toPoint();
}
// void AnalogClockWindow::paintEvent(QPaintEvent *)
//{
//     int angle = 0;
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing,true);
//     painter.translate(width()/2,height()/2);
//     painter.drawRect(-2,-2,4,4);
//     painter.setFont(QFont(0,11));
//     QPoint point(100,0);        //从(100,0)开始填文字

//    for(int i=0;i<10;i++)
//    {
//       painter.drawText(point.x()-10,point.y()-10,20,20,Qt::AlignCenter,QString("%1").arg(i));
//       point=CustomRotate(point,angle, 36);         //以当前angle度,顺时针旋转36度
//       angle -=36;                                  //更新度数,由于顺时针,所以用减
//    }
//}
