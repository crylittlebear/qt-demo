#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : CustomMovableWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui->toolBar->setStyleSheet("background-color: gray");

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    setActionForToolButtons();

    createSelectionMenu();

    labelText_ = new QLabel(this);
    labelText_->setMidLineWidth(150);
    ui->statusbar->addWidget(labelText_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * action for tool buttons
 * add by sadlittlebear
*/
void MainWindow::setActionForToolButtons()
{
    ui->tBtnInit->setDefaultAction(ui->actionInit);
    ui->tBtnListClear->setDefaultAction(ui->actionClear);
    ui->tBtnListInsert->setDefaultAction(ui->actionInsert);
    ui->tBtnListDel->setDefaultAction(ui->actionDelete);
    ui->tBtnListAppend->setDefaultAction(ui->actionAdd);

    ui->tBtnSelAll->setDefaultAction(ui->actionSelAll);
    ui->tBtnSelNone->setDefaultAction(ui->actionSelNone);
    ui->tBtnSelInv->setDefaultAction(ui->actionSelInvs);
}

void MainWindow::createSelectionMenu()
{
    // 创建下拉菜单
    QMenu* menuSelection = new QMenu(this);
    menuSelection->addAction(ui->actionSelAll);
    menuSelection->addAction(ui->actionSelNone);
    menuSelection->addAction(ui->actionSelInvs);

    // 设置tBenSelectItem按钮
    ui->tBtnSelItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tBtnSelItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tBtnSelItem->setDefaultAction(ui->actionSelPopMenu);
    ui->tBtnSelItem->setMenu(menuSelection);

    // 工具栏下拉式菜单按钮
    QToolButton* toolBarMenu = new QToolButton(this);
    toolBarMenu->setPopupMode(QToolButton::InstantPopup);
    toolBarMenu->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBarMenu->setDefaultAction(ui->actionSelPopMenu);
    toolBarMenu->setMenu(menuSelection);
    ui->toolBar->addWidget(toolBarMenu);


    // 在toolBar上创建退出Action
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionExit);
}

void MainWindow::on_actionAdd_triggered()
{
    QIcon icon(":/img/check.png");
    QListWidgetItem* item = new QListWidgetItem("New Item");
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);
    ui->listWidget->insertItem(ui->listWidget->count(), item);
}


void MainWindow::on_actionDelete_triggered()
{
    int itemRow = ui->listWidget->currentRow();
    QListWidgetItem* item = ui->listWidget->takeItem(itemRow);
    delete item;
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_actionSelAll_triggered()
{
    int size = ui->listWidget->count();
    QListWidgetItem* item;
    for (int i = 0; i < size; ++i) {
        item = ui->listWidget->item(i);
        if (item->checkState() != Qt::Checked) {
            item->setCheckState(Qt::Checked);
        }
    }
}


void MainWindow::on_actionSelNone_triggered()
{
    int size = ui->listWidget->count();
    QListWidgetItem* item;
    for (int i = 0; i < size; ++i) {
        item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            item->setCheckState(Qt::Unchecked);
        }
    }
}


void MainWindow::on_actionSelInvs_triggered()
{
    int size = ui->listWidget->count();
    QListWidgetItem* item;
    for (int i = 0; i < size; ++i) {
        item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            item->setCheckState(Qt::Unchecked);
        } else {
            item->setCheckState(Qt::Checked);
        }
    }
}

void MainWindow::on_actionInit_triggered()
{
    QListWidgetItem* item;
    QIcon icon(":/img/check.png");
    bool chk = ui->checkBoxEditable->isChecked();

    ui->listWidget->clear();
    for (int i = 0; i < 10; ++i) {
        QString itemName = QString("item %1").arg(i);
        item = new QListWidgetItem;
        item->setText(itemName);
        item->setIcon(icon);
        item->setCheckState(Qt::Checked);
        if (chk) {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable 
                | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        } else {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable 
                | Qt::ItemIsEnabled);
        }
        ui->listWidget->addItem(item);
    }
}


void MainWindow::on_actionClear_triggered()
{
    ui->listWidget->clear();
}


void MainWindow::on_actionInsert_triggered()
{
    QIcon icon(":/img/check.png");
    bool chk = ui->checkBoxEditable->isChecked();
    QListWidgetItem* item = new QListWidgetItem("New Item");
    item->setIcon(icon);
    item->setCheckState(Qt::Checked);
    if (chk) {
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable 
            | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    } else {
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable 
            | Qt::ItemIsEnabled);
    }
    ui->listWidget->insertItem(ui->listWidget->currentRow(), item);
}


void MainWindow::on_checkBoxEditable_clicked(bool checked)
{
    int cnt = ui->listWidget->count();
    QListWidgetItem* item;
    for (int i = 0; i < cnt; ++i) {
        item = ui->listWidget->item(i);
        if (checked) {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable 
                | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        } else {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable 
                | Qt::ItemIsEnabled);
        }
    }
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, 
                                                  QListWidgetItem *previous)
{
    QString str;
    if (current != nullptr) {
        if (previous == nullptr) {
            str = "当前: " + current->text();
        } else {
            str = "前一项: " + previous->text() + "; 当前项: " + current->text();
        }
    }
    ui->lineEdit->setText(str);
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu* menu = new QMenu;

    menu->addAction(ui->actionInit);
    menu->addAction(ui->actionClear);
    menu->addAction(ui->actionInsert);
    menu->addAction(ui->actionDelete);
    menu->addAction(ui->actionAdd);
    menu->addSeparator();
    menu->addAction(ui->actionSelAll);
    menu->addAction(ui->actionSelNone);
    menu->addAction(ui->actionSelInvs);

    menu->exec(QCursor::pos());
    delete menu;
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    QString str = QString("QListWidget::CurrentRowChanged()信号被发出, currentRow = %1").arg(currentRow);
    labelText_->setText(str);
}

