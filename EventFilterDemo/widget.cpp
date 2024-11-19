#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover, true);

    ui->labelHover->installEventFilter(this);
    ui->labelDBClicked->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->labelHover) {
        if (event->type() == QEvent::Enter) {
            ui->labelHover->setStyleSheet("background-color: rgb(170, 255, 255)");
        } else if (event->type() == QEvent::Leave) {
            ui->labelHover->setStyleSheet("");
            ui->labelHover->setText("靠见我, 点击我");
        } else if (event->type() == QEvent::MouseButtonPress) {
            ui->labelHover->setText("我被点击了");
        } else if (event->type() == QEvent::MouseButtonDblClick) {
            ui->labelHover->setText("我被双击了");
        }
    }
    if (watched == ui->labelDBClicked) {
        if (event->type()== QEvent::Enter)
            ui->labelDBClicked->setStyleSheet("background-color: rgb(85, 255, 127);");
        else if (event->type()== QEvent::Leave)
        {
            ui->labelDBClicked->setStyleSheet("");
            ui->labelDBClicked->setText("可双击的标签");
        }
        else if (event->type()== QEvent::MouseButtonDblClick)
            ui->labelDBClicked->setText("double clicked");
    }
    return QWidget::eventFilter(watched, event);
}
