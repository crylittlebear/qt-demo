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
    // qDebug() << ui->tableView->width();
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

    // 设置自定义代理
    spinBoxDelegate_ = new CustomFloatSpinDelegate(this);
    ui->tableView->setItemDelegateForColumn(1, spinBoxDelegate_);
    ui->tableView->setItemDelegateForColumn(2, spinBoxDelegate_);
    ui->tableView->setItemDelegateForColumn(3, spinBoxDelegate_);

    QStringList strList;
    strList << "优" << "良" << "一般" << "不及格";
    comboxDelegate_ = new CustomComboBoxDelegate(this);
    comboxDelegate_->setItems(strList, true);
    ui->tableView->setItemDelegateForColumn(4, comboxDelegate_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initModelData(QStringList &fileContent)
{
    int rowCount = fileContent.size();
    // qDebug() << rowCount;
    model_->setRowCount(rowCount - 1);
    QString header = fileContent.at(0);
    QStringList headList = header.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    model_->setHorizontalHeaderLabels(headList);
    int j;
    QStandardItem* item;
    for (int i = 1; i < rowCount; ++i) {
        QString line = fileContent.at(i);
        QStringList list = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        // qDebug() << list;
        for (j = 0; j < FixColClount - 1; ++j) {
            item = new QStandardItem(list.at(j));
            model_->setItem(i - 1, j, item);
        }
        item = new QStandardItem(model_->headerData(j, Qt::Horizontal, Qt::DisplayRole).toString());
        item->setCheckable(true);
        item->setBackground(QBrush(Qt::yellow));
        if (list.at(j) == "1") {
            item->setCheckState(Qt::Checked);
        } else {
            item->setCheckable(Qt::Unchecked);
        }
        model_->setItem(i - 1, j, item);
    }
}

void MainWindow::sltCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (current.isValid()) {
        labelCurPos_->setText(QString("当前单元格: %1行, %2列").arg(current.row() + 1).arg(current.column() + 1));
        QStandardItem* item = model_->itemFromIndex(current);
        labelCellText_->setText(QString("单元格内容: %1").arg(item->text()));
        QFont font = item->font();
        ui->actionBold->setChecked(font.bold());
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QString(__FILE__);
    // qDebug() << "file path: " << filePath;
    int pos = filePath.lastIndexOf("/");
    QString fileDir = filePath.left(pos);
    // qDebug() << "file dir path: " << fileDir;
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
    QList<QStandardItem*> itemList;
    QStandardItem* item;
    for (int i = 0; i < FixColClount - 1; ++i) {
        item = new QStandardItem("0");
        itemList << item;
    }
    QString str = model_->headerData(model_->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    item = new QStandardItem(str);
    item->setCheckable(true);
    item->setBackground(QBrush(Qt::yellow));
    itemList << item;
    model_->insertRow(model_->rowCount(), itemList);
    QModelIndex index = model_->index(model_->rowCount() - 1, 0);
    selectModel_->clearSelection();
    selectModel_->setCurrentIndex(index, QItemSelectionModel::Select);
}


void MainWindow::on_actionInsert_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem* item;
    for (int i = 0; i < FixColClount - 1; ++i) {
        item = new QStandardItem("0");
        itemList << item;
    }
    QString str = model_->headerData(model_->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    item = new QStandardItem(str);
    item->setCheckable(true);
    item->setCheckState(Qt::Unchecked);
    item->setBackground(QBrush(Qt::yellow));
    itemList << item;
    // 插入到相应的行之前
    QModelIndex curIndex = ui->tableView->currentIndex();
    model_->insertRow(curIndex.row(), itemList);
}


void MainWindow::on_actionSave_triggered()
{
    // 保存文件
    QStringList strList;
    QStandardItem* item;
    QString str;
    for (int i = 0; i < FixColClount; ++i) {
        QString tempStr = model_->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        if (i == FixColClount - 1) {
            str = str + tempStr;
        } else {
            str = str + tempStr + "\t";
        }
    }
    strList << str;
    for (int i = 0; i < model_->rowCount(); ++i) {
        str = "";
        for (int j = 0; j < FixColClount - 1; ++j) {
            QStandardItem* item = model_->item(i, j);
            str = str + item->text() + "\t";
        }
        item = model_->item(i, FixColClount - 1);
        if (item->checkState() == Qt::Checked) {
            str += "1";
        } else {
            str += "0";
        }
        // qDebug() << "str = " << str;
        strList << str;
    }
    QString srcPath(__FILE__);
    int pos = srcPath.lastIndexOf("/");
    QString fileDir = srcPath.left(pos);
    // qDebug() << "fileDir: " << fileDir;
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件", fileDir, "文本文件(*.txt);;所有文件(*.*)");
    QFile file(fileName);
    // qDebug() << "fileName: " << fileName;
    if (file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream stream(&file);
        for (int i = 0; i < strList.size(); ++i) {
            stream << strList.at(i) << "\n";
        }
    }
    file.close();
}


void MainWindow::on_actionDelete_triggered()
{
    QModelIndex index = selectModel_->currentIndex();
    if (index.row() == model_->rowCount() - 1) {
        model_->removeRow(index.row());
    } else {
        model_->removeRow(index.row());
        selectModel_->setCurrentIndex(index, QItemSelectionModel::Select);
    }
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_actionPreview_triggered()
{
    ui->plainTextEdit->clear();
    QStandardItem* item;
    QString str;
    for (int i = 0; i < model_->columnCount(); ++i) {
        item = model_->horizontalHeaderItem(i);
        str = str + item->text() + "\t";
    }
    ui->plainTextEdit->appendPlainText(str);
    for (int i = 0; i < model_->rowCount(); ++i) {
        str = "";
        for (int j = 0; j < model_->columnCount() - 1; ++j) {
            item = model_->item(i, j);
            str = str + item->text() + QString("\t");
        }
        item = model_->item(i, model_->columnCount() - 1);
        if (item->checkState() == Qt::Checked) {
            str = str + "1";
        } else {
            str = str + "0";
        }
        ui->plainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_actionAlignLeft_triggered()
{
    if (!selectModel_->hasSelection()) {
        return;
    }
    QModelIndexList indexList = selectModel_->selectedIndexes();
    for (int i = 0; i < indexList.size(); ++i) {
        QStandardItem* item = model_->itemFromIndex(indexList.at(i));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
}


void MainWindow::on_actionAlignCenter_triggered()
{
    if (!selectModel_->hasSelection()) {
        return;
    }
    QModelIndexList indexList = selectModel_->selectedIndexes();
    for (int i = 0; i < indexList.size(); ++i) {
        QStandardItem* item = model_->itemFromIndex(indexList.at(i));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}


void MainWindow::on_actionAlignRight_triggered()
{
    if (!selectModel_->hasSelection()) {
        return;
    }
    QModelIndexList indexList = selectModel_->selectedIndexes();
    for (int i = 0; i < indexList.size(); ++i) {
        QStandardItem* item = model_->itemFromIndex(indexList.at(i));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}


void MainWindow::on_actionBold_triggered()
{
    if (!selectModel_->hasSelection()) {
        return;
    }
    QModelIndexList indexList = selectModel_->selectedIndexes();
    for (int i = 0; i < indexList.size(); ++i) {
        QStandardItem* item = model_->itemFromIndex(indexList.at(i));
        QFont font = item->font();
        font.setBold(!font.bold());
        item->setFont(font);
    }
}

