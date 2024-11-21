#include "customlabel.h"
#include <QPainter>

CustomLabel::CustomLabel(QWidget *parent)
    : QLabel{parent}
{

}

void CustomLabel::setImage(QString path)
{
    path_ = path;
}

void CustomLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPixmap pixmap(path_);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}
