#include "widget.h"
#include "./ui_widget.h"

#include <QDIr>
#include <QFileDialog>
#include <QMenu>

Widget::Widget(QWidget *parent)
    : CustomMovableWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->listWidget->installEventFilter(this);
    ui->listWidget->setDragEnabled(true);
    ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);

    ui->labelMusicName->setMaximumWidth(200);

    player_ = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    player_->setAudioOutput(audioOutput);

    initConnections();

    // 为播放模式按钮创建下拉菜单
    buildCycleMenu();

    // 加载背景图片
    loadBackground();

    // 设置播放相关按钮为无效状态
    setBtnControlDisable();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    // Q_UNUSED(previous);
    // ui->labelMusicName->setText(QString("曲名: %1").arg(current->text()));
}

void Widget::initConnections()
{
    connect(player_, &QMediaPlayer::positionChanged, this, &Widget::sltPositionChanged);
    connect(player_, &QMediaPlayer::durationChanged, this, &Widget::sltDurationChanged);
    connect(player_, &QMediaPlayer::sourceChanged, this, &Widget::sltSourceChanged);
    connect(player_, &QMediaPlayer::playbackStateChanged, this, &Widget::sltStateChanged);
    connect(player_, &QMediaPlayer::metaDataChanged, this, &Widget::sltMetaDataChanged);
}

void Widget::loadBackground()
{
    QString filePath = __FILE__;
    int pos = filePath.lastIndexOf("/");
    QString dirPath = filePath.left(pos);
    QDir dir;
    dir.setCurrent(dirPath + "/img/background");
    qDebug() << "dir current path = " << dir.currentPath();
    backgroundList_ = dir.entryList(QDir::Files);
    backgroundDir_ = dir.currentPath() + "/";
}

void Widget::changeBackground()
{
    QRandomGenerator generator;
    // 随机挑选一张背景图片
    QString backgroundPath = backgroundDir_ + backgroundList_.at(generator.global()->bounded(0, backgroundList_.size()));
    QPixmap pixmap(backgroundPath);
    QPixmap pix = pixmap.scaled(ui->label->width(), ui->label->height());
    ui->label->setPixmap(pix);
}

void Widget::setBtnControlDisable()
{
    ui->tBtnPlay->setEnabled(false);
    ui->tBtnPause->setEnabled(false);
    ui->tBtnStop->setEnabled(false);
    ui->tBtnPre->setEnabled(false);
    ui->tBtnNext->setEnabled(false);
}

void Widget::setBtnControlEnable()
{
    ui->tBtnPlay->setEnabled(true);
    ui->tBtnPause->setEnabled(true);
    ui->tBtnStop->setEnabled(true);
    ui->tBtnPre->setEnabled(true);
    ui->tBtnNext->setEnabled(true);
}

void Widget::buildCycleMenu()
{
    QMenu* menu = new QMenu(this);
    QAction* actionSeqPlay = new QAction("顺序播放");
    QAction* actionSiglePlay = new QAction("单曲循环");
    QAction* actionCycle = new QAction("循环播放");
    actionSeqPlay->setIcon(QIcon(":/img/seqPlay.png"));
    actionSiglePlay->setIcon(QIcon(":/img/repeat.png"));
    actionCycle->setIcon(QIcon(":/img/cyclePlay.png"));

    menu->addAction(actionSeqPlay);
    menu->addAction(actionSiglePlay);
    menu->addAction(actionCycle);
    ui->tBtnPalyMode->setMenu(menu);
    ui->tBtnPalyMode->setDefaultAction(actionSeqPlay);

    connect(actionSeqPlay, &QAction::triggered, [=](){
        ui->tBtnPalyMode->setDefaultAction(actionSeqPlay);
    });
    connect(actionSiglePlay, &QAction::triggered, [=](){
        ui->tBtnPalyMode->setDefaultAction(actionSiglePlay);
    });
    connect(actionCycle, &QAction::triggered, [=](){
        ui->tBtnPalyMode->setDefaultAction(actionCycle);
    });
}

QUrl Widget::getUrlFromItem(QListWidgetItem *item)
{
    QVariant itemData = item->data(Qt::UserRole);
    QUrl url = itemData.value<QUrl>();
    return url;
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
    if (watched == ui->listWidget) {
        qDebug() << ui->listWidget->currentRow();
        QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        delete item;
    }
    return true;
}

void Widget::sltStateChanged(QMediaPlayer::PlaybackState state)
{
    if (state == QMediaPlayer::StoppedState) {
        qDebug() << "music stoped";
        int curRow = ui->listWidget->currentRow();
        if (curRow < ui->listWidget->count() - 1) {
            ui->listWidget->setCurrentRow(curRow + 1);
            QListWidgetItem* item = ui->listWidget->currentItem();
            QUrl url = getUrlFromItem(item);
            player_->setSource(url);
            player_->play();
        }
    }
}

void Widget::sltSourceChanged(const QUrl &media)
{
    ui->labelMusicName->setText(QString("当前曲目: %1").arg(media.fileName()));
}

void Widget::sltDurationChanged(quint64 duration)
{

}

void Widget::sltPositionChanged(quint64 position)
{

}

void Widget::sltMetaDataChanged()
{

}

void Widget::on_tBtnClose_clicked()
{
    this->close();
}


void Widget::on_tBtnOpen_clicked()
{
    // QString curPath = QDir::homePath();
    QString curPath = QString("E:\\音乐\\new\\");
    QString dlgTitile = "选择音频文件";
    QString filter = QString("音频文件(*.mp3 *.wav *.wma);;所有文件(*.*)");
    QStringList files = QFileDialog::getOpenFileNames(this, dlgTitile, curPath, filter);
    if (files.isEmpty()) {
        return;
    }
    for (int i = 0; i < files.size(); ++i) {
        QString file = files.at(i);
        QFileInfo fileInfo(file);
        QListWidgetItem* item = new QListWidgetItem(QIcon(":/img/tune.png"), fileInfo.fileName());
        item->setData(Qt::UserRole, QUrl::fromLocalFile(file));
        ui->listWidget->addItem(item);
    }
    if (ui->listWidget->count() > 0) {
        setBtnControlEnable();
        ui->listWidget->setCurrentRow(0);
    }
}


void Widget::on_tBtnMax_clicked()
{
    if (this->isMaximized()) {
        this->showNormal();
    } else {
        this->showMaximized();
    }
}


void Widget::on_tBtnMin_clicked()
{
    if (!this->isMinimized()) {
        this->showMinimized();
    }
}


void Widget::on_tBtnRemove_clicked()
{
    if (ui->listWidget->count() == 0) {
        return;
    }
    // 如果当前播放的音乐和ListWidget的当前条目相同
    if (player_->playbackState() == QMediaPlayer::PlayingState) {
        if (player_->source() == getUrlFromItem(ui->listWidget->currentItem())) {
            player_->stop();
        }
    }
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
    if (ui->listWidget->count() == 0) {
        setBtnControlDisable();
    }
}


void Widget::on_tBtnClear_clicked()
{
    loopPlay_ = false;
    ui->listWidget->clear();
    player_->stop();
    setBtnControlDisable();
}


void Widget::on_listWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    loopPlay_ = false;
    changeBackground();
    player_->setSource(getUrlFromItem(ui->listWidget->currentItem()));
    player_->play();
    loopPlay_ = (ui->tBtnPalyMode->text() == "单曲循环");
    qDebug() << ui->tBtnPalyMode->text();
}


void Widget::on_tBtnPlay_clicked()
{
    changeBackground();

    if (player_->source() == getUrlFromItem(ui->listWidget->currentItem())) {
        if (player_->playbackState() == QMediaPlayer::PlayingState) {
        } else {
            player_->play();
        }
        return;
    }
    QListWidgetItem* item = ui->listWidget->currentItem();
    QUrl url = getUrlFromItem(item);
    player_->setSource(url);
    player_->play();
}


void Widget::on_tBtnPause_clicked()
{
    if (player_->playbackState() == QMediaPlayer::PlayingState) {
        player_->pause();
    }
}


void Widget::on_tBtnStop_clicked()
{
    player_->stop();
}


void Widget::on_tBtnPre_clicked()
{
    changeBackground();
    int row = ui->listWidget->currentRow();
    row--;
    row = row < 0 ? 0 : row;
    ui->listWidget->setCurrentRow(row);
    loopPlay_ = false;
    player_->setSource(getUrlFromItem(ui->listWidget->currentItem()));
    player_->play();
    loopPlay_ = (ui->tBtnPalyMode->text() == "循环播放");
}


void Widget::on_tBtnNext_clicked()
{
    changeBackground();
    int curRow = ui->listWidget->currentRow();
    curRow = (curRow == ui->listWidget->count() - 1) ? curRow : curRow + 1;
    ui->listWidget->setCurrentRow(curRow);
    loopPlay_ = false;
    player_->setSource(getUrlFromItem(ui->listWidget->currentItem()));
    player_->play();
    loopPlay_ = (ui->tBtnPalyMode->text() == "循环播放");
}

