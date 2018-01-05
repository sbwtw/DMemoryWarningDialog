#include "processinfomodel.h"

#include <QDebug>
#include <QIcon>

#define COLUMN_ICON     0
#define COLUMN_NAME     1
#define COLUMN_MEM      2
#define COLUMN_FREE_BTN 3
#define COLUMN_NUMS     4

inline QString formatMem(const unsigned mem_bytes)
{
    return QString("%1M").arg(mem_bytes / 1024 / 1024);
}

ProcessInfoModel::ProcessInfoModel(QObject *parent)
    : QAbstractTableModel(parent)

    , m_processInfos(new ProcessInfoManager)
{
    connect(m_processInfos, &ProcessInfoManager::processInfoListChanged, this, [=] { emit layoutChanged(); });
}

int ProcessInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_processInfos->processInfoList.size();
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
        case COLUMN_MEM:
            return formatMem(m_processInfos->processInfoList[index.row()].total_mem_bytes);
        case COLUMN_NAME:
            return m_processInfos->processInfoList[index.row()].app_name;
        default:;
        }
        break;
    case IconRole:
        if (index.column() == COLUMN_ICON)
            return QIcon::fromTheme(m_processInfos->processInfoList[index.row()].app_name).pixmap(24, 24);
        break;
    case StateRole:
        return m_buttonPressedState.value(index.row(), false);
    case PidListRole:
        return m_processInfos->processInfoList[index.row()].pid_list;
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
