#ifndef WIDGET_H
#define WIDGET_H

#include "customwidget.h"
#include <QToolBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public CustomMovableWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QToolBar* toolBar_;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
