#ifndef CUSTOMCOMBOBOXDELEGATE_H
#define CUSTOMCOMBOBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class CustomComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CustomComboBoxDelegate(QObject *parent = nullptr);

    void setItems(QStringList items, bool editable);

    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QStringList strList_;
    bool editable_;

signals:
};

#endif // CUSTOMCOMBOBOXDELEGATE_H
