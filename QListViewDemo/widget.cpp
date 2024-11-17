#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    strList_ << "北京" << "上海" << "广州" << "南京" << "苏州" << "无锡";
    model_ = new QStringListModel(this);
    model_->setStringList(strList_);
    ui->listView->setModel(model_);
    ui->checkBox->setChecked(true);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnRecover_clicked()
{
    model_->setStringList(strList_);
}


void Widget::on_btnClear_clicked()
{
    model_->removeRows(0, model_->rowCount());
}


void Widget::on_btnAdd_clicked()
{
    model_->insertRow(model_->rowCount());
    QModelIndex index = model_->index(model_->rowCount() - 1, 0);
    model_->setData(index, "new Item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void Widget::on_btnInsert_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    model_->insertRow(index.row());
    model_->setData(index, "insert item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void Widget::on_btnDelete_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    model_->removeRow(index.row());
}


void Widget::on_btnMoveUp_clicked()
{
    int curRow = ui->listView->currentIndex().row();
    QModelIndex index = QModelIndex();
    model_->moveRow(index, curRow, index, curRow - 1);
}


void Widget::on_btnMoveDown_clicked()
{
    int curRow = ui->listView->currentIndex().row();
    if (curRow == model_->rowCount() - 1) {
        return;
    }
    QModelIndex index = QModelIndex();
    model_->moveRow(index, curRow, index, curRow + 2);
}


void Widget::on_btnSort_clicked()
{
    model_->sort(0, Qt::AscendingOrder);
}


void Widget::on_btnClearPlaintext_clicked()
{
    ui->plainTextEdit->clear();
}


void Widget::on_btnShowDataModel_clicked()
{
    QStringList tempList = model_->stringList();
    ui->plainTextEdit->clear();
    for (int i = 0; i < tempList.size(); ++i) {
        ui->plainTextEdit->appendPlainText(tempList.at(i));
    }
}


void Widget::on_checkBox_clicked(bool checked)
{
    if (checked) {
        ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked
                                        | QAbstractItemView::SelectedClicked);
    } else {
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}


void Widget::on_listView_clicked(const QModelIndex &index)
{
    QString str1 = QString("模型索引: row = %1, column = %2;").arg(index.row()).arg(index.column());
    QVariant var = model_->data(index, Qt::DisplayRole);
    QString str2 = var.toString();
    ui->labelStatus->setAlignment(Qt::AlignCenter);
    ui->labelStatus->setText(str1 + str2);
}

