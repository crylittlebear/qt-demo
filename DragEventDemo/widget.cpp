#include "widget.h"
#include "./ui_widget.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QMimeData>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setAcceptDrops(true);
    // ui->plainTextEdit->setAcceptDrops(false);
    ui->label->setAcceptDrops(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "in drag enter event process";
    // ui->plainTextEdit->clear();
    // ui->plainTextEdit->appendPlainText("dragEnterEvent事件 mimeData()->formats()");
    for (int i = 0; i < event->mimeData()->formats().size(); ++i) {
        // ui->plainTextEdit->appendPlainText(event->mimeData()->formats().at(i));
    }
    // ui->plainTextEdit->appendPlainText("\n dragEnter event事件 mimeData()->urls()");
    for (int i = 0; i < event->mimeData()->urls().size(); ++i) {
        QUrl url = event->mimeData()->urls().at(i);
        // ui->plainTextEdit->appendPlainText(url.path());
    }
    if (event->mimeData()->hasUrls()) {
        QString fileName = event->mimeData()->urls().at(0).fileName();
        QFileInfo fileInfo(fileName);
        QString ext = fileInfo.suffix().toUpper();
        if (ext == "JPG") {
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    } else {
        event->ignore();
    }
}

void Widget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "in resize event process";
}

void Widget::dropEvent(QDropEvent *event)
{
    qDebug() << "in drop event process";
    QString fileName = event->mimeData()->urls().at(0).path();
    fileName = fileName.right(fileName.length() - 1);
    QPixmap pixmap(fileName);
    ui->label->setPixmap(pixmap);
    event->accept();
}
