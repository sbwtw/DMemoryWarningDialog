#include "processinfomodel.h"

#define COLUMN_ICON     0
#define COLUMN_NAME     1
#define COLUMN_MEM      2
#define COLUMN_FREE_BTN 3
#define COLUMN_NUMS     4

ProcessInfoModel::ProcessInfoModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int ProcessInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 10;
}

int ProcessInfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return COLUMN_NUMS;
}

QVariant ProcessInfoModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case DisplayRole:
        switch (index.column())
        {
        case COLUMN_FREE_BTN:
            return QString(tr("Free"));
        default:
            return QString("%1, %2").arg(index.row()).arg(index.column());
        }
        break;
    case StateRole:
        return m_buttonPressedState.value(index.row(), false);
    default:;
    }

    return QVariant();
}

bool ProcessInfoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)

    if (index.column() == COLUMN_FREE_BTN)
        m_buttonPressedState[index.row()] = value.toBool();

    return true;
}