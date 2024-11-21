#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QAbstractItemView>
#include <QGroupBox>

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
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    int getDropActionIndex(Qt::DropAction actionType);

    Qt::DropAction getDropActionType(int index);

    void refreshToUi(QGroupBox* curGroupBox);

private slots:

    void on_rBtnSource_clicked();

    void on_rBtnList_clicked();

    void on_rBtnTree_clicked();

    void on_rBtnTable_clicked();

    void on_chkBoxAcceptDrops_clicked(bool checked);

    void on_chkBoxDragEnabled_clicked(bool checked);

    void on_cBoxDropMode_currentIndexChanged(int index);

    void on_cBoxDropAction_currentIndexChanged(int index);

private:
    Ui::Widget *ui;

    QAbstractItemView* itemView_ = nullptr;
};
#endif // WIDGET_H
