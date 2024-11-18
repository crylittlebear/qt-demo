#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

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

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_actionSetRootDIr_triggered();

    void on_actionExit_triggered();

    void on_rBtnShowFileDir_clicked();

    void on_rBtnShowDir_clicked();

    void on_chkBoxFileNameFilter_clicked(bool checked);

    void on_tBtnApply_clicked();

private:
    QFileSystemModel* model_;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
