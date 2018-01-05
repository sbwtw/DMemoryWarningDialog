#include "processinfodelegate.h"

#include <QApplication>
#include <QDebug>

ProcessInfoDelegate::ProcessInfoDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

void ProcessInfoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::paint(painter, option, index);
}
