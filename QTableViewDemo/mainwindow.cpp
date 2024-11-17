#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model_ = new QStandardItemModel(2, FixColClount, this);
    selectModel_ = new QItemSelectionModel(model_, this);
    connect(selectModel_, &QItemSelectionModel::currentChanged, this,
                &MainWindow::sltCurrentChanged);
    // 为tableView设置数据模型和选择模型
    ui->tableView->setModel(model_);
    ui->tableView->setSelectionModel(selectModel_);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    // 设置tableVIew每一列的宽度
    qDebug() << ui->tableView->width();
    // ui->tableView->setColumnWidth(0, 80);
    // ui->tableView->setColumnWidth(1, 80);
    // ui->tableView->setColumnWidth(2, 80);
    // ui->tableView->setColumnWidth(3, 80);
    // ui->tableView->setColumnWidth(4, 80);
    // ui->tableView->setColumnWidth(5, 80);
    // 创建状态栏组件
    labelCurFile_ = new QLabel(this);
    labelCurFile_->setMinimumWidth(400);
    labelCurPos_ = new QLabel(this);
    labelCurPos_->setMinimumWidth(200);
    labelCellText_ = new QLabel(this);
    labelCellText_->setMinimumWidth(200);
    ui->statusbar->addWidget(labelCurFile_);
    ui->statusbar->addWidget(labelCurPos_);
    ui->statusbar->addWidget(labelCellText_);

    ui->actionAppend->setEnabled(false);
    ui->actionInsert->setEnabled(false);
    ui->actionDelete->setEnabled(false);
    ui->actionSave->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initModelData(QStringList &fileContent)
{
    int rowCount = fileContent.size();
    qDebug() << rowCount;
    model_->setRowCount(rowCount - 1);
    QString header = fileContent.at(0);
    QStringList headList = header.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    model_->setHorizontalHeaderLabels(headList);
    int j;
    QStandardItem* item;
    for (int i = 1; i < rowCount; ++i) {
        QString line = fileContent.at(i);
        QStringList list = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for (j = 0; j < FixColClount - 1; ++j) {
            item = new QStandardItem(list.at(j));
            model_->setItem(i - 1, j, item);
        }
        item = new QStandardItem(list.at(j));
        item->setCheckable(true);
        item->setBackground(QBrush(Qt::yellow));
        if (list.at(j) == "0") {
            item->setCheckState(Qt::Unchecked);
        } else {
            item->setCheckable(Qt::Checked);
        }
        model_->setItem(i - 1, j, item);
    }
}

void MainWindow::sltCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (current.isValid()) {
        labelCurPos_->setText(QString("当前单元格: %1行, %2列").arg(current.row()).arg(current.column()));
        QStandardItem* item = model_->itemFromIndex(current);
        labelCellText_->setText(QString("单元格内容: %1").arg(item->text()));
        QFont font = item->font();
        ui->actionBold->setChecked(font.bold());
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QString(__FILE__);
    qDebug() << "file path: " << filePath;
    int pos = filePath.lastIndexOf("/");
    QString fileDir = filePath.left(pos);
    qDebug() << "file dir path: " << fileDir;
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", fileDir, "数据文件(*.txt);;所有文件(*.*)");
    if (fileName.isEmpty()) {
        return;
    }
    QStringList fileContent;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        while (!stream.atEnd()) {
            QString str = stream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fileContent.append(str);
        }
        file.close();
        labelCurFile_->setText(QString("当前文件: %1").arg(fileName));
        ui->actionAppend->setEnabled(true);
        ui->actionInsert->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        ui->actionSave->setEnabled(true);
        initModelData(fileContent);
    } else {
        QMessageBox::warning(this, "警告", "文件打开失败");
    }
}


void MainWindow::on_actionAppend_triggered()
{

}


void MainWindow::on_actionInsert_triggered()
{

}


void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::on_actionDelete_triggered()
{

}


void MainWindow::on_actionExit_triggered()
{

}


void MainWindow::on_actionPreview_triggered()
{

}


void MainWindow::on_actionAlignLeft_triggered()
{

}


void MainWindow::on_actionAlignCenter_triggered()
{

}


void MainWindow::on_actionAlignRight_triggered()
{

}


void MainWindow::on_actionBold_triggered()
{

}

