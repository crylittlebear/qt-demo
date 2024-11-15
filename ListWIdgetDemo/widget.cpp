#include "widget.h"
#include "./ui_widget.h"

#include <QBoxLayout>
#include <QAction>

Widget::Widget(QWidget *parent)
    : CustomMovableWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    toolBar_ = new QToolBar;
    toolBar_->setMinimumWidth(this->width());
    toolBar_->setIconSize(QSize(20, 20));
    toolBar_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // toolBar_->setStyleSheet("border-width:2px; border-color:gray; border-style:solid");

    QAction* actionNew = new QAction("新建", this);
    QAction* actionOpen = new QAction("打开", this);
    actionNew->setIcon(QIcon(":/img/new.png"));
    actionOpen->setIcon(QIcon(":/img/open.png"));
    toolBar_->addAction(actionNew);
    toolBar_->addSeparator();
    toolBar_->addAction(actionOpen);
    toolBar_->addAction(ui->actionExit);

    QWidget* toolBarWidget = new QWidget;
    toolBarWidget->setStyleSheet("background-color: gray");
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(toolBar_);
    hLayout->setContentsMargins(0, 0, 0, 0);
    toolBarWidget->setLayout(hLayout);
    QWidget* mainWidget = new QWidget;
    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(toolBarWidget);
    vLayout->addWidget(mainWidget);
    vLayout->setStretch(0, 1);
    vLayout->setStretch(1, 10);
    vLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(vLayout);


    connect(ui->actionExit, &QAction::triggered, [=](){
        this->close();
    });
}

Widget::~Widget()
{
    delete ui;
}
