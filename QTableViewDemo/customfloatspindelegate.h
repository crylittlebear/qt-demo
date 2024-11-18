#ifndef CUSTOMFLOATSPINDELEGATE_H
#define CUSTOMFLOATSPINDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>

class CustomFloatSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CustomFloatSpinDelegate(QObject *parent = nullptr);

    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    virtual void updateEditorGeometry(QWidget *editor,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const override;

signals:
};

#endif // CUSTOMFLOATSPINDELEGATE_H
