#include "customslider.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

CustomSlider::CustomSlider(QWidget *parent)
    : QWidget{parent}
{
    sliderHeight_ = this->height() / 5.0;
    curPoint_ = QPoint(sliderHeight_ + 2, this->height() / 2.0);
}

void CustomSlider::setMaxValue(int value)
{
    maxValue_ = value;
}

void CustomSlider::setMinValue(int value)
{
    minValue_ = value;
}

void CustomSlider::setValue(int value)
{
    curValue_ = value;
}

qreal CustomSlider::getCurValue()
{
    return curValue_;
}

qreal CustomSlider::getMinValue()
{
    return minValue_;
}

qreal CustomSlider::getMaxValue()
{
    return maxValue_;
}

bool CustomSlider::isInDragingArea(QPoint pos)
{
    qreal x = pos.x(),  y = pos.y();
    qreal cx = curPoint_.x(), cy = curPoint_.y();
    if ((cx - x) * (cx - x) + (cy - y) * (cy - y) <= (sliderHeight_ * sliderHeight_)) {
        return true;
    }
    return false;
}

void CustomSlider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QColor(0, 0, 255));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRoundedRect(QRectF(sliderHeight_ + 2, this->height() * 2 / 5.0,
                                   curPoint_.x() - sliderHeight_ - 2, sliderHeight_), 5, 5);
    painter.setBrush(QColor(200, 200, 200));
    painter.drawRoundedRect(QRectF(curPoint_.x(), this->height() * 2 / 5.0,
                                   this->width() - sliderHeight_ - 2 - curPoint_.x(), sliderHeight_), 5, 5);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(206, 206, 206));
    painter.setBrush(Qt::white);
    painter.setPen(pen);
    painter.drawEllipse(QPointF(curPoint_.x(), this->height() / 2.0), sliderHeight_, sliderHeight_);
}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isInDragingArea(event->pos())) {
        isDraging_ = true;
        qDebug() << "In Draging Area!!!";
    }
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (isDraging_ && (event->buttons() & Qt::LeftButton)) {
        if (event->pos().x() > (this->width() - sliderHeight_ - 2)) {
            curPoint_.setX(this->width() - sliderHeight_ - 2);
        } else if (event->pos().x() < sliderHeight_ + 2) {
            curPoint_.setX(sliderHeight_ + 2);
        } else {
            curPoint_.setX(event->pos().x());
        }
        update();
    }
}

void CustomSlider::getCUrPoint(QMouseEvent *event)
{

}
