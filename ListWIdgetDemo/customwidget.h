#pragma once

// 去掉QWidget边框并实现窗口可拖动功能的窗口基类

#include "qmainwindow.h"

#define SCALE_WIDTH 9
#define DRAG_HEITH  50

enum ScaleDirection {
    None,
    Right,
    Down,
    BottomRight
};

class CustomMovableWidget  : public QMainWindow
{
    Q_OBJECT

public:
    CustomMovableWidget(QWidget *parent);
    ~CustomMovableWidget();

protected:
    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    bool event(QEvent* event) override;

private:
    // 判断是否处于拖动区域
    bool isInDragArea(QPoint p);
    // 判断是否处于可缩放区域
    bool isInScaleArea(QPoint p);
    // 是否处于左右边缘
    bool isInLeftRightEdge(QPoint p);
    // 是否处于上下边缘
    bool isInTopBottomEdge(QPoint p);
    // 是否处于左上角或右下角
    bool isInCornerTopLeft(QPoint p);
    // 是否处于左下角或右上角
    bool isInCornerTopRight(QPoint p);

private:
    // 用于记录鼠标点击位置距离窗口左上角的距离
    QPoint point_;
    // 判断是否正在移动
    bool isMoving_;
    // 判断是否正在缩放
    bool isScaling_;
    // 缩放的方向
    ScaleDirection direction_;
};
