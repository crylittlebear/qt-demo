#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QLabel>

#include "customcomboboxdelegate.h"
#include "customfloatspindelegate.h"

#define FixColClount 6

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initModelData(QStringList& fileContent);

private slots:
    void sltCurrentChanged(const QModelIndex& current, const QModelIndex& previous);

    void on_actionOpen_triggered();

    void on_actionAppend_triggered();

    void on_actionInsert_triggered();

    void on_actionSave_triggered();

    void on_actionDelete_triggered();

    void on_actionExit_triggered();

    void on_actionPreview_triggered();

    void on_actionAlignLeft_triggered();

    void on_actionAlignCenter_triggered();

    void on_actionAlignRight_triggered();

    void on_actionBold_triggered();

private:
    QStandardItemModel* model_;
    QItemSelectionModel* selectModel_;

    QLabel* labelCurFile_;
    QLabel* labelCurPos_;
    QLabel* labelCellText_;

    CustomComboBoxDelegate* comboxDelegate_;
    CustomFloatSpinDelegate* spinBoxDelegate_;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
