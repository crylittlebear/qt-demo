#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = nullptr);

    void setImage(QString path);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString path_;
};

#endif // CUSTOMLABEL_H
