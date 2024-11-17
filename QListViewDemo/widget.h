#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QStringList>
#include <QStringListModel>

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

private slots:
    void on_btnRecover_clicked();

    void on_btnClear_clicked();

    void on_btnAdd_clicked();

    void on_btnInsert_clicked();

    void on_btnDelete_clicked();

    void on_btnMoveUp_clicked();

    void on_btnMoveDown_clicked();

    void on_btnSort_clicked();

    void on_btnClearPlaintext_clicked();

    void on_btnShowDataModel_clicked();

    void on_checkBox_clicked(bool checked);

    void on_listView_clicked(const QModelIndex &index);

private:
    QStringList strList_;
    QStringListModel* model_;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
