#include "centraldelegate.h"

CentralDelegate::CentralDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}


QWidget *CentralDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
    return {};
}

void CentralDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    return;
}
void CentralDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const {
    return;
}

void CentralDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const {
    return;
}
