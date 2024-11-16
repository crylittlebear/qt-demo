#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum TreeItemType {TopItem = 1001, GroupItem, ImageItem};
    enum TreeColNum {ColItem, ColItemType, ColDate};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAddFolder_triggered();

    void on_actionAddFiles_triggered();

    void on_actionZoomPlus_triggered();

    void on_actionZoomMinus_triggered();

    void on_actionRealSize_triggered();

    void on_actionFitWidth_triggered();

    void on_actionFitHeight_triggered();

    void on_actionDelete_triggered();

    void on_actionQuit_triggered();

    void on_actionScan_triggered();

    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, 
                                         QTreeWidgetItem *previous);

    void on_actionVisible_triggered(bool checked);

    void on_actionFloat_triggered(bool checked);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_topLevelChanged(bool topLevel);

private:
    void buildTreeHeader();

    void initTree();

    void addFolderItem(QTreeWidgetItem* parItem, QString dirName);

    QString getFinalFolderName(const QString& fullPathName);

    void addImageItem(QTreeWidgetItem* parItem, QString fileName);

    void displayImage(QTreeWidgetItem* parItem);

    void changeItemCaption(QTreeWidgetItem* item);

    void deleteItem(QTreeWidgetItem* parItem, QTreeWidgetItem* item);

private:
    QLabel* labelFileName_;
    QLabel* labelNodeText_;
    QSpinBox* spinRatio_;

    QPixmap curPixmap_;
    float ratio_;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
