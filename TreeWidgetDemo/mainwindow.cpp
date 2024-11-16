#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口名称
    setWindowTitle("TreeWidget图片浏览器");
    setWindowIcon(QIcon(":/img/icon.png"));


    //创建状态栏上的组件
    labelNodeText_=new QLabel("节点标题",this);
    labelNodeText_->setMinimumWidth(200);
    ui->statusbar->addWidget(labelNodeText_);

    //用于显示图片缩放比例的QSpinBox组件
    spinRatio_=new QSpinBox(this);
    spinRatio_->setRange(0,2000);
    spinRatio_->setValue(100);
    spinRatio_->setSuffix(" %");
    spinRatio_->setReadOnly(true);

    //不显示上下调节按钮
    spinRatio_->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->statusbar->addPermanentWidget(spinRatio_);

    // 用于显示图片的文件名
    labelFileName_=new QLabel("文件名",this);
    ui->statusbar->addPermanentWidget(labelFileName_);

    //初始化目录树

    //重新构建目录树表头
    buildTreeHeader();
    //初始化目录树
    initTree();

    setCentralWidget(ui->scrollArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildTreeHeader()
{
    ui->treeFiles->clear();

    // 设置TreeWidget头的各项属性
    QTreeWidgetItem* header = new QTreeWidgetItem();
    header->setText(MainWindow::ColItem, "目录和文件");
    header->setText(MainWindow::ColItemType, "节点类型");
    header->setText(MainWindow::ColDate, "最后修改日期");

    header->setTextAlignment(ColItem, Qt::AlignHCenter | Qt::AlignVCenter);
    header->setTextAlignment(ColItemType, Qt::AlignLeft | Qt::AlignVCenter);

    ui->treeFiles->setHeaderItem(header);
}

void MainWindow::initTree()
{
    QIcon icon(":/img/folder.png");
    QTreeWidgetItem*  item=new QTreeWidgetItem(MainWindow::TopItem); //节点类型为TopItem
    item->setIcon(MainWindow::ColItem, icon);          //设置第1列的图标
    item->setText(MainWindow::ColItem, "图片");     //设置第1列的文字
    item->setText(MainWindow::ColItemType, "Top Item");     //设置第2列的文字
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(MainWindow::ColItem, Qt::Checked);  //设置为选中

    //    item->setData(MainWindow::colItem,Qt::UserRole,QVariant(dataStr)); //设置节点第1列的Qt::UserRole的Data
    ui->treeFiles->addTopLevelItem(item);//添加顶层节点
}

void MainWindow::addFolderItem(QTreeWidgetItem *parItem, QString dirName)
{
    QIcon icon(":/img/folder.png");
    QString nodeText = getFinalFolderName(dirName);

    QTreeWidgetItem* item = new QTreeWidgetItem(MainWindow::GroupItem);
    item->setIcon(ColItem, icon);
    item->setText(ColItem, nodeText);
    item->setText(ColItemType, "Group Item");

    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate); //设置节点选项
    item->setCheckState(ColItem, Qt::Checked); //节点选中
    item->setData(ColItem,Qt::UserRole,QVariant(dirName)); //设置角色为Qt::UserRole的Data,存储完整目录名称

    parItem->addChild(item);  //在父节点下面添加子节点
}

QString MainWindow::getFinalFolderName(const QString &fullPathName)
{
    int cnt = fullPathName.size();
    int i = fullPathName.lastIndexOf("/");
    QString str = fullPathName.right(cnt - i - 1);
    return str;
}

void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString fileName)
{
    QIcon   icon(":/img/image.png");

    QFileInfo fileInfo(fileName);      //QFileInfo对象
    QString NodeText=fileInfo.fileName();          //不带路径的文件名
    QDateTime birthDate=fileInfo.lastModified();   //文件的创建日期

    //    QTreeWidgetItem *item;
    QTreeWidgetItem *item=new QTreeWidgetItem(MainWindow::ImageItem); //节点类型为itImageItem
    item->setIcon(ColItem,icon);
    item->setText(ColItem,NodeText);            //第1列文字
    item->setText(ColItemType,"Image Item");    //第2列文字
    item->setText(ColDate,birthDate.toString("yyyy-MM-dd"));    //第3列文字
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(ColItem,Qt::Checked);

    item->setData(ColItem,Qt::UserRole,QVariant(fileName)); //设置用户数据,存储完整文件名称
    parItem->addChild(item);  //在父节点下面添加子节点
}

void MainWindow::displayImage(QTreeWidgetItem *item)
{
    QString fileName = item->data(ColItem, Qt::UserRole).toString();
    labelFileName_->setText(fileName);
    labelNodeText_->setText(item->text(ColItem));
    curPixmap_.load(fileName);
    ui->actionFitHeight->trigger();

    ui->actionZoomPlus->setEnabled(true);
    ui->actionZoomMinus->setEnabled(true);
    ui->actionFitHeight->setEnabled(true);
    ui->actionFitWidth->setEnabled(true);
    ui->actionRealSize->setEnabled(true);
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str="*"+item->text(ColItem);    //节点文字前加“*”
    item->setText(ColItem,str);             //设置节点文字

    if (item->childCount()>0)   //如果有子节点
        for (int i=0;i<item->childCount();i++)  //遍历子节点
            changeItemCaption(item->child(i));  //递归调用自己
}

void MainWindow::deleteItem(QTreeWidgetItem *parItem, QTreeWidgetItem *item)
{
    if (item->childCount()>0)   //如果有子节点,需要先删除所有子节点
    {
        int count=item->childCount();       //子节点个数
        QTreeWidgetItem *tempParItem=item;  //临时父节点
        for (int i=count-1; i>=0; i--)      //遍历子节点
            deleteItem(tempParItem, tempParItem->child(i));   //递归调用自己
    }

    //删除完子节点之后，再删除自己
    parItem->removeChild(item); //移除节点
    delete  item;
}

void MainWindow::on_actionAddFolder_triggered()
{
    QString dir = QFileDialog::getExistingDirectory();
    if (dir.isEmpty()) {
        return;
    }
    QTreeWidgetItem* item = ui->treeFiles->currentItem();
    if (item == nullptr) {
        return;
    }
    if (item->type() != ImageItem) {
        addFolderItem(item, dir);
    }
}


void MainWindow::on_actionAddFiles_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "文件选择", "", "图片(*.jpg *.png);;文本(*.txt)");
    if (files.isEmpty()) {
        return;
    }
    QTreeWidgetItem* partItem, *item;
    item = ui->treeFiles->currentItem();
    if (item == nullptr) {
        item = ui->treeFiles->topLevelItem(0);
    }
    if (item->type() == ImageItem) {
        partItem = item->parent();
    } else {
        partItem = item;
    }
    for (int i = 0; i < files.size(); ++i) {
        QString fileName = files.at(i);
        addImageItem(partItem, fileName);
    }
    partItem->setExpanded(true);
}


void MainWindow::on_actionZoomPlus_triggered()
{
    ratio_ = ratio_ * 1.1;
    spinRatio_->setValue(100 * ratio_);

    int w = ratio_ * curPixmap_.width();
    int h = ratio_ * curPixmap_.height();

    QPixmap pix = curPixmap_.scaled(w, h);
    ui->label->setPixmap(pix);
}


void MainWindow::on_actionZoomMinus_triggered()
{
    ratio_ = ratio_ * 0.9;
    spinRatio_->setValue(100 * ratio_);

    int w = ratio_ * curPixmap_.width();
    int h = ratio_ * curPixmap_.height();

    QPixmap pix = curPixmap_.scaled(w, h);
    ui->label->setPixmap(pix);
}


void MainWindow::on_actionRealSize_triggered()
{
    ratio_ = 1;
    spinRatio_->setValue(100);
    ui->label->setPixmap(curPixmap_);
}


void MainWindow::on_actionFitWidth_triggered()
{
    int w = ui->scrollArea->width();
    int realW = curPixmap_.width();
    ratio_ = float(w) / realW;

    spinRatio_->setValue(100 * ratio_);

    QPixmap pix = curPixmap_.scaledToWidth(w - 30);
    ui->label->setPixmap(pix);
}


void MainWindow::on_actionFitHeight_triggered()
{
    int H=ui->scrollArea->height(); //得到scrollArea的高度
    int realH=curPixmap_.height();   //原始图片的实际高度
    ratio_=float(H)/realH;        //当前显示比例，必须转换为浮点数

    spinRatio_->setValue(100 * ratio_);  //状态栏上显示缩放百分比

    QPixmap pix=curPixmap_.scaledToHeight(H-30);     //图片缩放到指定高度
    ui->label->setPixmap(pix);     //设置Label的PixMap
}


void MainWindow::on_actionDelete_triggered()
{
    QTreeWidgetItem* item = ui->treeFiles->currentItem();
    if (item == nullptr) {
        return;
    }
    QTreeWidgetItem* parentItem = item->parent();
    deleteItem(parentItem, item);
}


void MainWindow::on_actionQuit_triggered()
{
    this->close();
}


void MainWindow::on_actionScan_triggered()
{
    for (int i = 0; i < ui->treeFiles->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = ui->treeFiles->topLevelItem(i);
        changeItemCaption(item);
    }
}

void MainWindow::on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // qDebug("currentItemChanged() is emitted");
    if (current==nullptr)         //当前节点为空
        return;

    if (current == previous)     //没有切换节点，只是列变化
        return;

    int var=current->type();    //节点的类型
    switch(var)
    {
    case  TopItem:        //顶层节点
        ui->actionAddFolder->setEnabled(true);
        ui->actionAddFiles->setEnabled(true);
        ui->actionDelete->setEnabled(false);    //顶层节点不允许删除
        break;

    case  GroupItem:      //文件组节点
        ui->actionAddFolder->setEnabled(true);
        ui->actionAddFiles->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        break;

    case  ImageItem:      //图片文件节点
        ui->actionAddFolder->setEnabled(false);    //图片节点下不能添加目录节点
        ui->actionAddFiles->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        displayImage(current);                  //显示图片
    }
}


void MainWindow::on_actionVisible_triggered(bool checked)
{
    ui->dockWidget->setVisible(checked);
}


void MainWindow::on_actionFloat_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}


void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actionVisible->setChecked(visible);
}


void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->actionFloat->setChecked(topLevel);
}

