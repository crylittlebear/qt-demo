#include "customcomboboxdelegate.h"

#include <QComboBox>

CustomComboBoxDelegate::CustomComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void CustomComboBoxDelegate::setItems(QStringList items, bool editable)
{
    strList_ = items;
    editable_ = editable;
}

QWidget *CustomComboBoxDelegate::createEditor(QWidget *parent,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox* editor = new QComboBox(parent);
    editor->setEditable(editable_);
    editor->addItems(strList_);
    return editor;
}

void CustomComboBoxDelegate::setEditorData(QWidget *editor,
                                           const QModelIndex &index) const
{
    QString str = index.model()->data(index, Qt::EditRole).toString();
    QComboBox* box = static_cast<QComboBox*>(editor);
    box->setCurrentText(str);
}

void CustomComboBoxDelegate::setModelData(QWidget *editor,
                                          QAbstractItemModel *model,
                                          const QModelIndex &index) const
{
    QComboBox* box = static_cast<QComboBox*>(editor);
    QString str = box->currentText();
    model->setData(index, str, Qt::EditRole);
}

void CustomComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                                  const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
