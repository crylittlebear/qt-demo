#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QWidget>

class CustomSlider : public QWidget
{
    Q_OBJECT
public:
    explicit CustomSlider(QWidget *parent = nullptr);

    void setMaxValue(int value);

    void setMinValue(int value);

    void setValue(int value);

    qreal getCurValue();

    qreal getMinValue();

    qreal getMaxValue();

    bool isInDragingArea(QPoint pos);

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void getCUrPoint(QMouseEvent* event);

signals:
    void sigPositionChanged(qreal curValue);

private:
    QPointF curPoint_;
    qreal maxValue_;
    qreal minValue_;
    qreal curValue_;
    qreal sliderHeight_;

    bool isDraging_;
};

#endif // CUSTOMSLIDER_H
