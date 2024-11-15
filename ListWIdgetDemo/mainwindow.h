#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include "qmainwindow.h"
#include "customwidget.h"

#include <QListWidgetItem>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public CustomMovableWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();

    void on_actionDelete_triggered();

    void on_actionExit_triggered();

    void on_actionSelAll_triggered();

    void on_actionSelNone_triggered();

    void on_actionSelInvs_triggered();

    void on_actionInit_triggered();

    void on_actionClear_triggered();

    void on_actionInsert_triggered();

    void on_checkBoxEditable_clicked(bool checked);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_listWidget_currentRowChanged(int currentRow);

private:
    void setActionForToolButtons();

    void createSelectionMenu();

private:
    Ui::MainWindow *ui;

    QLabel* labelText_;
};

#endif // MAINWINDOW_H
