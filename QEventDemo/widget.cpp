#include "widget.h"
#include "./ui_widget.h"

#include <QPainter>
#include <QMessageBox>
#include <QCloseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), QPixmap(":/img/15654564.png"));
}

void Widget::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button =  QMessageBox::question(this, "消息框", "确定要关闭吗？", QMessageBox::Yes
                                                                | QMessageBox::No | QMessageBox::Cancel);
    if (button == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    QPoint point = ui->pushButton->pos();
    if (event->key() == Qt::Key_A) {
        ui->pushButton->move(point.x() - 20, point.y());
    } else if (event->key() == Qt::Key_W) {
        ui->pushButton->move(point.x(), point.y() - 20);
    } else if (event->key() == Qt::Key_S) {
        ui->pushButton->move(point.x(), point.y() + 20);
    } else if (event->key() == Qt::Key_D) {
        ui->pushButton->move(point.x() + 20, point.y());
    }
    QWidget::keyPressEvent(event);
}

void Widget::showEvent(QShowEvent *event)
{

}

void Widget::hideEvent(QHideEvent *event)
{

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint pt = event->pos();
        QPointF realPt = event->position();
        QPointF winPt = event->scenePosition();
        QPointF globPt = event->globalPosition();
        QString str = QString("pos() = (%1, %2)").arg(pt.x()).arg(pt.y());
        str += QString("\nposition() = (%1, %2)").arg(realPt.x()).arg(realPt.y());
        str += QString("\nscenePosition() = (%1, %2)").arg(winPt.x()).arg(winPt.y());
        str += QString("\nglobalPos() = (%1, %2)").arg(globPt.x()).arg(globPt.y());

        ui->label->setText(str);
        ui->label->adjustSize();
        ui->label->move(event->pos());
    }
    QWidget::mousePressEvent(event);
}
