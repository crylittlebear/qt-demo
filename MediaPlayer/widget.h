#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QtMultimedia>

#include "customwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public CustomMovableWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void initConnections();

    void loadBackground();

    void changeBackground();

    void setBtnControlDisable();

    void setBtnControlEnable();

    void buildCycleMenu();

    QUrl getUrlFromItem(QListWidgetItem* item);

    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void sltStateChanged(QMediaPlayer::PlaybackState state);

    void sltSourceChanged(const QUrl& media);

    void sltDurationChanged(quint64 duration);

    void sltPositionChanged(quint64 position);

    void sltMetaDataChanged();

    void on_tBtnOpen_clicked();

    void on_tBtnClose_clicked();

    void on_tBtnMax_clicked();

    void on_tBtnMin_clicked();

    void on_tBtnRemove_clicked();

    void on_tBtnClear_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_tBtnPlay_clicked();

    void on_tBtnStop_clicked();

    void on_tBtnPre_clicked();

    void on_tBtnNext_clicked();

    void on_tBtnVolumn_clicked();

    void on_tBtnMusic_clicked();

    void on_tBtnVideo_clicked();

private:
    Ui::Widget *ui;

private:
    QMediaPlayer* player_;
    bool loopPlay_ = true;
    QString duringTime_;
    QString positionTime_;

    QStringList backgroundList_;
    QString backgroundDir_;
};
#endif // WIDGET_H
