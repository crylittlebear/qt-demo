#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent* event) override;

    void closeEvent(QCloseEvent *event) override;

    void keyReleaseEvent(QKeyEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

    void showEvent(QShowEvent* event) override;

    void hideEvent(QHideEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
