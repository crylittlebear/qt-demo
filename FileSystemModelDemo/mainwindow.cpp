#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    model_ = new QFileSystemModel(this);
    model_->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model_);
    ui->listView->setModel(model_);
    ui->tableView->setModel(model_);

    QStringList filterList;
    filterList << "*.h;*.cpp;*.ui";
    filterList << "*.txt;*.jpg;*.png";
    ui->comboBoxFilter->addItems(filterList);

    connect(ui->treeView, &QTreeView::clicked, ui->listView, &QListView::setRootIndex);
    connect(ui->treeView, &QTreeView::clicked, ui->tableView, &QTableView::setRootIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->chkBoxIsDir->setChecked(model_->isDir(index));
    ui->labelPath->setText("文件路径为: " + model_->filePath(index));
    ui->labelNodeType->setText("文件类型为: " + model_->type(index));
    ui->labelFileName->setText("文件名为: " + model_->fileName(index));
    int size = model_->size(index) / 1024;
    if (size < 1024) {
        ui->labelFileSize->setText(QString("文件大小为: %1 KB").arg(size));
    } else {
        ui->labelFileSize->setText(QString("文件大小为: %1 MB").arg(size / 1024.0));
    }
}


void MainWindow::on_actionSetRootDIr_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, "打开文件夹", QDir::currentPath());
    if (!dir.isEmpty()) {
        model_->setRootPath(dir);
        ui->treeView->setRootIndex(model_->index(dir));
    }
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_rBtnShowFileDir_clicked()
{
    ui->groupBoxFilter->setEnabled(true);
    model_->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
}


void MainWindow::on_rBtnShowDir_clicked()
{
    ui->groupBoxFilter->setEnabled(false);
    model_->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
}


void MainWindow::on_chkBoxFileNameFilter_clicked(bool checked)
{
    model_->setNameFilterDisables(!checked);
    ui->comboBoxFilter->setEnabled(checked);
    ui->tBtnApply->setEnabled(checked);
}


void MainWindow::on_tBtnApply_clicked()
{
    QString filters = ui->comboBoxFilter->currentText().trimmed();
    QStringList filter = filters.split(";", Qt::SkipEmptyParts);
    model_->setNameFilters(filter);
}

