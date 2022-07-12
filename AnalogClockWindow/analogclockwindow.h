#ifndef ANALOGCLOCKWINDOW_H
#define ANALOGCLOCKWINDOW_H

#include "rasterwindow.h"
#include <QPoint>
#include <QPointF>


class AnalogClockWindow : public RasterWindow
{
public:
    AnalogClockWindow();

protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;

private:
    int m_timerId;
    QPoint CustomRotate(QPointF point,qreal from_angle,qreal rotate);

};

#endif // ANALOGCLOCKWINDOW_H
