#include "customfloatspindelegate.h"
#include <QDoubleSpinBox>
#include <QStyleOptionViewItem>

CustomFloatSpinDelegate::CustomFloatSpinDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

QWidget *CustomFloatSpinDelegate::createEditor(QWidget *parent,
                                               const QStyleOptionViewItem &option,
                                               const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(20000);
    editor->setDecimals(2);
    return editor;
}

void CustomFloatSpinDelegate::setEditorData(QWidget *editor,
                                            const QModelIndex &index) const
{
    float value = index.model()->data(index, Qt::DisplayRole).toFloat();
    QDoubleSpinBox* spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setValue(value);
}

void CustomFloatSpinDelegate::setModelData(QWidget *editor,
                                           QAbstractItemModel *model,
                                           const QModelIndex &index) const
{
    QSpinBox* spinBox = static_cast<QSpinBox*>(editor);
    float value = spinBox->value();
    QString str = QString::asprintf("%.2f", value);
    model->setData(index, str, Qt::EditRole);
}

void CustomFloatSpinDelegate::updateEditorGeometry(QWidget *editor,
                                                   const QStyleOptionViewItem &option,
                                                   const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
