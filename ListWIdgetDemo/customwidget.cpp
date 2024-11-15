#include "customwidget.h"

#include "qevent.h"
#include "qdebug.h"

CustomMovableWidget::CustomMovableWidget(QWidget *parent)
    : QMainWindow(parent)
{
    isMoving_ = false;

    isScaling_ = false;

    direction_ = ScaleDirection::None;

    // 设置窗口无边框
    setWindowFlag(Qt::FramelessWindowHint);

    // 设置窗口的最小尺寸
    setMinimumSize(800, 540);
}

CustomMovableWidget::~CustomMovableWidget()
{}

void CustomMovableWidget::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标位置
        point_ = event->pos();
        // 如果处于缩放区域内，则设置缩放标记为true
        if (isInScaleArea(event->pos())) {
            isScaling_ = true;
            if (isInCornerTopLeft(event->pos())) {
                direction_ = ScaleDirection::BottomRight;
            } else if (isInTopBottomEdge(event->pos())) {
                direction_ = ScaleDirection::Down;
            } else if (isInLeftRightEdge(event->pos())) {
                direction_ = ScaleDirection::Right;
            }
        }
    }
    event->accept();
}

void CustomMovableWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (isInDragArea(event->pos())) {
        // 如果目前没有处于移动状态
        if (!isMoving_) {
            isMoving_ = true;
        }
        // 判断是否正在拖动
        if (isMoving_ && event->buttons() & Qt::LeftButton) {
            this->move(event->globalPosition().toPoint() - point_);
        }
    } else if (isScaling_ && (event->buttons() & Qt::LeftButton)){
        // 如果正在移动，则缩放窗口
        int tempWidth = 0, tempHeight = 0;
        switch (direction_) {
        case ScaleDirection::BottomRight:
            tempWidth = event->globalPosition().toPoint().x() - this->geometry().x();
            tempHeight = event->globalPosition().toPoint().y() - this->geometry().y();
            break;
        case ScaleDirection::Right:
            tempWidth = event->globalPosition().toPoint().x() - this->geometry().x();
            tempHeight = this->geometry().height();
            break;
        case ScaleDirection::Down:
            tempWidth = this->geometry().width();
            tempHeight = event->globalPosition().toPoint().y() - this->geometry().y();
            break;
        }
        this->resize(tempWidth, tempHeight);
    }
    event->accept();
}

void CustomMovableWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (isMoving_) {
        isMoving_ = false;
    }
    if (isScaling_) {
        isScaling_ = false;
    }
}

bool CustomMovableWidget::event(QEvent* event)
{
    if (event->type() == QEvent::HoverMove) {
        QMouseEvent* mEvent = static_cast<QMouseEvent*>(event);
        if (isInCornerTopLeft(mEvent->pos())) {
            this->setCursor(Qt::SizeFDiagCursor);
        } else if (isInCornerTopRight(mEvent->pos())) {
            this->setCursor(Qt::SizeBDiagCursor);
        } else if (isInLeftRightEdge(mEvent->pos())) {
            this->setCursor(Qt::SizeHorCursor);
        } else if (isInTopBottomEdge(mEvent->pos())) {
            this->setCursor(Qt::SizeVerCursor);
        } else {
            this->setCursor(Qt::ArrowCursor);
        }
    }
    return QMainWindow::event(event);
}

bool CustomMovableWidget::isInDragArea(QPoint p)
{
    if ((p.x() >= SCALE_WIDTH) && (p.x() <= width() - SCALE_WIDTH) && (p.y() < DRAG_HEITH)) {
        return true;
    }
    return false;
}

bool CustomMovableWidget::isInScaleArea(QPoint p)
{
    return isInLeftRightEdge(p) || isInTopBottomEdge(p);
}

bool CustomMovableWidget::isInLeftRightEdge(QPoint p)
{
    if (p.x() < SCALE_WIDTH || p.x() > this->width() - SCALE_WIDTH) {
        return true;
    }
    return false;
}

bool CustomMovableWidget::isInTopBottomEdge(QPoint p)
{
    if (p.y() < SCALE_WIDTH || p.y() > this->height() - SCALE_WIDTH) {
        return true;
    }
    return false;
}

bool CustomMovableWidget::isInCornerTopLeft(QPoint p)
{
    if (p.x() < SCALE_WIDTH && p.y() < SCALE_WIDTH || (p.x() > width() - SCALE_WIDTH) && (p.y() > height() - SCALE_WIDTH)) {
        return true;
    }
    return false;
}

bool CustomMovableWidget::isInCornerTopRight(QPoint p)
{
    if ((p.x() > width() - SCALE_WIDTH) && (p.y() < SCALE_WIDTH) || (p.x() < SCALE_WIDTH) && (p.y() > height() - SCALE_WIDTH)) {
        return true;
    }
    return false;
}
