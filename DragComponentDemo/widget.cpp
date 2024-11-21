#include "widget.h"
#include "./ui_widget.h"

#include <QEvent>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 为每个Widget安装事件过滤器
    ui->listWidgetSource->installEventFilter(this);
    ui->listWidget->installEventFilter(this);
    ui->treeWidget->installEventFilter(this);
    ui->tableWidget->installEventFilter(this);

    // 设置item widget组件的拖放操作属性
    ui->listWidgetSource->setAcceptDrops(true);
    ui->listWidgetSource->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidgetSource->setDragEnabled(true);
    ui->listWidgetSource->setDefaultDropAction(Qt::CopyAction);

    ui->listWidget->setAcceptDrops(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDefaultDropAction(Qt::CopyAction);

    ui->treeWidget->setAcceptDrops(true);
    ui->treeWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeWidget->setDragEnabled(true);
    ui->treeWidget->setDefaultDropAction(Qt::CopyAction);

    ui->tableWidget->setAcceptDrops(true);
    ui->tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->tableWidget->setDragEnabled(true);
    ui->tableWidget->setDefaultDropAction(Qt::CopyAction);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() != QEvent::KeyPress) {
        return QWidget::eventFilter(watched, event);
    }
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() != Qt::Key_Delete) {
        return QWidget::eventFilter(watched, event);
    }
    if (watched == ui->listWidgetSource) {
        QListWidgetItem* item = ui->listWidgetSource->takeItem(ui->listWidgetSource->currentRow());
        delete item;
    } else if (watched == ui->listWidget) {
        QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete item;
    } else if (watched == ui->treeWidget) {
        QTreeWidgetItem* item = ui->treeWidget->currentItem();
        if (item->parent() != nullptr) {
            QTreeWidgetItem* parent = item->parent();
            parent->removeChild(item);
        } else {
            int index = ui->treeWidget->indexOfTopLevelItem(item);
            ui->treeWidget->takeTopLevelItem(index);
        }
        delete item;
    } else if (watched == ui->tableWidget) {
        QTableWidgetItem* item = ui->tableWidget->takeItem(ui->tableWidget->currentRow(),
                                                           ui->tableWidget->currentColumn());
        delete item;
    }
    return true;
}

int Widget::getDropActionIndex(Qt::DropAction actionType)
{
    switch (actionType) {
    case Qt::CopyAction:
        return 0;

    case Qt::MoveAction:
        return 1;

    case Qt::LinkAction:
        return 2;

    case Qt::IgnoreAction:
        return 3;

    default:
        return 0;
    }
}

Qt::DropAction Widget::getDropActionType(int index)
{
    switch (index) {
    case 0:
        return Qt::CopyAction;

    case 1:
        return Qt::MoveAction;

    case 2:
        return Qt::LinkAction;

    case 3:
        return Qt::IgnoreAction;

    default:
        return Qt::CopyAction;
    }
}

void Widget::refreshToUi(QGroupBox *curGroupBox)
{
    ui->chkBoxAcceptDrops->setChecked(itemView_->acceptDrops());
    ui->chkBoxDragEnabled->setChecked(itemView_->dragEnabled());

    ui->cBoxDropMode->setCurrentIndex((int)itemView_->dragDropMode());
    int index = getDropActionIndex(itemView_->defaultDropAction());
    ui->cBoxDropAction->setCurrentIndex(index);

    QFont font = ui->groupBoxSource->font();
    font.setBold(false);
    ui->groupBoxSource->setFont(font);
    ui->groupBoxList->setFont(font);
    ui->groupBoxTree->setFont(font);
    ui->groupBoxTable->setFont(font);

    font.setBold(true);
    curGroupBox->setFont(font);
}

void Widget::on_rBtnSource_clicked()
{
    itemView_ = ui->listWidgetSource;
    refreshToUi(ui->groupBoxSource);
}


void Widget::on_rBtnList_clicked()
{
    itemView_ = ui->listWidget;
    refreshToUi(ui->groupBoxList);
}


void Widget::on_rBtnTree_clicked()
{
    itemView_ = ui->treeWidget;
    refreshToUi(ui->groupBoxTree);
}


void Widget::on_rBtnTable_clicked()
{
    itemView_ = ui->tableWidget;
    refreshToUi(ui->groupBoxTable);
}


void Widget::on_chkBoxAcceptDrops_clicked(bool checked)
{
    itemView_->setAcceptDrops(checked);
}


void Widget::on_chkBoxDragEnabled_clicked(bool checked)
{
    itemView_->setDragEnabled(checked);
}


void Widget::on_cBoxDropMode_currentIndexChanged(int index)
{
    QAbstractItemView::DragDropMode mode = (QAbstractItemView::DragDropMode)index;
    itemView_->setDragDropMode(mode);
}


void Widget::on_cBoxDropAction_currentIndexChanged(int index)
{
    Qt::DropAction actionType = getDropActionType(index);
    itemView_->setDefaultDropAction(actionType);
}

