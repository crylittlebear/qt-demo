#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // TableWidget每一列的类型
    enum CellType { TypeName = 1000, TypeSex, TypeBirth, TypeNation, TypePartyM, TypeScore};

    // 各字段在TableWidget中的列号
    enum FieldColumn {ColName = 0, ColSex, ColBirth, ColNation, ColParty, ColScore};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSetTableHeader_clicked();

    void on_btnSetRowCount_clicked();

    void on_btnSetTableData_clicked();

    void on_btnInsertRow_clicked();

    void on_btnAddRow_clicked();

    void on_btnDeleteCurRow_clicked();

    void on_btnSetRowHeight_clicked();

    void on_btnSetColWidth_clicked();

    void on_btnShowTable_clicked();

    void on_checkBoxEditable_clicked(bool checked);

    void on_checkBoxSpaceRowColor_clicked(bool checked);

    void on_checkBoxShowHHeader_clicked(bool checked);

    void on_checkBoxshowVHeader_clicked(bool checked);

    void on_radioButtonRowSelect_clicked(bool checked);

    void on_radioButtonBoxSelect_clicked(bool checked);

    void on_spinBoxRow_valueChanged(int arg1);

    void on_tableWidget_cellClicked(int row, int column);

private:
    void createItemShow(int rowNo, QString name, QString sex, QDate birth,
                        QString nation, bool isPm, int score);

private:
    QLabel* labelIndex_;
    QLabel* labelCellType_;
    QLabel* labelStudID_;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
