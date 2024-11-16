#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QDate>
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labelIndex_ = new QLabel("当前单元格坐标: ", this);
    labelIndex_->setMinimumWidth(250);

    labelCellType_ = new QLabel("当前单元格类型: ", this);
    labelCellType_->setMinimumWidth(200);

    labelStudID_ = new QLabel("学生ID: ", this);
    labelStudID_->setMinimumWidth(200);

    ui->statusbar->addWidget(labelIndex_);
    ui->statusbar->addWidget(labelCellType_);
    ui->statusbar->addWidget(labelStudID_);

    // ui->tableWidget->setColumnCount(6);
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // qDebug() << ui->plainTextEdit->width();
    // ui->tableWidget->setColumnWidth(MainWindow::ColName, ui->plainTextEdit->width() / 6);
    // ui->tableWidget->setColumnWidth(MainWindow::ColSex, ui->plainTextEdit->width() / 6);
    // ui->tableWidget->setColumnWidth(MainWindow::ColBirth, ui->plainTextEdit->width() / 6);
    // ui->tableWidget->setColumnWidth(MainWindow::ColNation, ui->plainTextEdit->width() / 6);
    // ui->tableWidget->setColumnWidth(MainWindow::ColParty, ui->plainTextEdit->width() / 6);
    // ui->tableWidget->setColumnWidth(MainWindow::ColScore, ui->plainTextEdit->width() / 6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createItemShow(int rowNo, QString name, QString sex, QDate birth,
                                QString nation, bool isPm, int score)
{
    // 学号基数
    uint studentId = 203105000;
    // 姓名
    QTableWidgetItem* item = new QTableWidgetItem(name, MainWindow::TypeName);
    item->setTextAlignment(Qt::AlignCenter);
    studentId += rowNo;
    item->setData(Qt::UserRole, QVariant(studentId));
    ui->tableWidget->setItem(rowNo, MainWindow::ColName, item);

    // 设置性别
    QIcon icon;
    if (sex == "男") {
        icon.addFile(":/img/male-student.png");
    } else {
        icon.addFile(":/img/female-student.png");
    }
    item = new QTableWidgetItem(sex, MainWindow::TypeSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignCenter);
    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    item->setFlags(flags);
    ui->tableWidget->setItem(rowNo, MainWindow::ColSex, item);

    // 出生日期
    QString str = birth.toString("yyyy-MM-dd");
    item = new QTableWidgetItem(str, MainWindow::TypeBirth);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(rowNo, MainWindow::ColBirth, item);

    // 设置民族
    item = new QTableWidgetItem(nation, MainWindow::TypeNation);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(rowNo, MainWindow::ColNation, item);

    // 设置是否党员
    item = new QTableWidgetItem("党员", MainWindow::TypePartyM);
    item->setTextAlignment(Qt::AlignCenter);
    flags = Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    item->setFlags(flags);
    if (isPm) {
        item->setCheckState(Qt::Checked);
    } else {
        item->setCheckState(Qt::Unchecked);
    }
    item->setBackground(QBrush(Qt::yellow));
    ui->tableWidget->setItem(rowNo, MainWindow::ColParty, item);

    // 设置分数
    str.setNum(score);
    item = new QTableWidgetItem(str, MainWindow::TypeScore);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(rowNo, MainWindow::ColScore, item);
}

void MainWindow::on_btnSetTableHeader_clicked()
{
    QStringList headerList;
    headerList << "姓名" << "性别" << "出生日期" << "民族" << "分数" << "是否党员";
    ui->tableWidget->setColumnCount(headerList.size());
    for (int i = 0; i < headerList.size(); ++i) {
        QTableWidgetItem* headerItem = new QTableWidgetItem(headerList.at(i));
        QFont font = headerItem->font();
        font.setBold(true);
        font.setPointSize(11);
        headerItem->setForeground(QBrush(Qt::red));
        headerItem->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i, headerItem);
    }
}


void MainWindow::on_btnSetRowCount_clicked()
{
    ui->tableWidget->setRowCount(ui->spinBoxRow->value());
    ui->tableWidget->setAlternatingRowColors(ui->checkBoxSpaceRowColor->isChecked());
}


void MainWindow::on_btnSetTableData_clicked()
{
    QDate birth(2001, 4, 6);
    ui->tableWidget->clearContents();
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QString strName = QString("学生%1").arg(i);
        QString strSex((i % 2) ? "男" : "女");
        bool isParty = i % 2;
        int score = QRandomGenerator::global()->bounded(60, 100);
        createItemShow(i, strName, strSex, birth, "汉族", isParty, score);
    }
}


void MainWindow::on_btnInsertRow_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(currentRow);
    createItemShow(currentRow, "新生", "女", QDate::fromString("2002-10-1", "yyyy-M-d"), "苗族", true, 99);
}


void MainWindow::on_btnAddRow_clicked()
{
    int currentRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(currentRow);
    createItemShow(currentRow, "新生", "女", QDate::fromString("2002-10-1", "yyyy-M-d"), "满族", false, 99);
}


void MainWindow::on_btnDeleteCurRow_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(currentRow);
}


void MainWindow::on_btnSetRowHeight_clicked()
{
    ui->tableWidget->resizeRowsToContents();
}


void MainWindow::on_btnSetColWidth_clicked()
{
    ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::on_btnShowTable_clicked()
{

}


void MainWindow::on_checkBoxEditable_clicked(bool checked)
{

}


void MainWindow::on_checkBoxSpaceRowColor_clicked(bool checked)
{

}


void MainWindow::on_checkBoxShowHHeader_clicked(bool checked)
{

}


void MainWindow::on_checkBoxshowVHeader_clicked(bool checked)
{

}


void MainWindow::on_radioButtonRowSelect_clicked(bool checked)
{

}


void MainWindow::on_radioButtonBoxSelect_clicked(bool checked)
{

}


void MainWindow::on_spinBoxRow_valueChanged(int arg1)
{

}

