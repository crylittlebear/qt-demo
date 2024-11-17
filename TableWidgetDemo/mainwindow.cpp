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

    // 设置plainText字体及颜色
    QFont font = ui->plainTextEdit->font();
    font.setFamily("宋体");
    font.setPointSize(10);
    ui->plainTextEdit->setFont(font);
    ui->plainTextEdit->setStyleSheet("color: red");

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
        font.setPointSize(10);
        font.setFamily("微软雅黑");
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
    ui->plainTextEdit->clear();
    int rowCount = ui->tableWidget->rowCount();
    int colCount = ui->tableWidget->columnCount();
    for (int i = 0; i < rowCount; ++i) {
        QString tempStr;
        QTableWidgetItem* item = ui->tableWidget->item(i, 0);
        tempStr +=  ("姓名: " + item->text());
        item = ui->tableWidget->item(i, 1);
        tempStr += ("   性别: " + item->text());
        item = ui->tableWidget->item(i, 2);
        tempStr += ("   出生日期: " + item->text());
        item = ui->tableWidget->item(i, 3);
        tempStr += ("   名族: " + item->text());
        item = ui->tableWidget->item(i, 4);
        if (item->checkState() == Qt::Checked) {
            tempStr += "    党员";
        } else {
            tempStr += "    非党员";
        }
        item = ui->tableWidget->item(i, 5);
        tempStr += ("   分数: " + item->text());
        ui->plainTextEdit->appendPlainText(tempStr);
    }
}


void MainWindow::on_checkBoxEditable_clicked(bool checked)
{
    if (checked) {
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    } else {
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}


void MainWindow::on_checkBoxSpaceRowColor_clicked(bool checked)
{
    // 设置间隔行底色
    ui->tableWidget->setAlternatingRowColors(checked);
    // 设置间隔行底色的颜色
    ui->tableWidget->setPalette(QPalette(Qt::gray));
}


void MainWindow::on_checkBoxShowHHeader_clicked(bool checked)
{
    ui->tableWidget->horizontalHeader()->setVisible(checked);
}


void MainWindow::on_checkBoxshowVHeader_clicked(bool checked)
{
    ui->tableWidget->verticalHeader()->setVisible(checked);
}


void MainWindow::on_radioButtonRowSelect_clicked(bool checked)
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::on_radioButtonBoxSelect_clicked(bool checked)
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}


void MainWindow::on_spinBoxRow_valueChanged(int arg1)
{

}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    labelIndex_->setText(QString("当前单元格坐标: %1行，%2列").arg(row).arg(column));
    QString str;
    switch ((MainWindow::FieldColumn)column) {
    case MainWindow::ColName:
        str = "当前单元格类型为: 姓名";
        break;
    case MainWindow::ColSex:
        str = "当前单元格类型为: 性别";
        break;
    case MainWindow::ColBirth:
        str = "当前单元格类型为: 出生日期";
        break;
    case MainWindow::ColNation:
        str = "当前单元格类型为: 民族";
        break;
    case MainWindow::ColParty:
        str = "当前单元格类型为: 是否党员";
        break;
    case MainWindow::ColScore:
        str = "当前单元格类型为: 分数";
        break;
    }
    labelCellType_->setText(str);
    QTableWidgetItem* item = ui->tableWidget->item(row, 0);
    uint id = item->data(Qt::UserRole).toInt();
    labelStudID_->setText(QString("学生ID: %1").arg(id));
}

