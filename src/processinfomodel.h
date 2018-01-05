#ifndef PROCESSINFOMODEL_H
#define PROCESSINFOMODEL_H

#include "processinfomanager.h"

#include <QAbstractTableModel>
#include <QPointer>

class ProcessInfoModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ProcessInfoModel(QObject *parent = nullptr);

    enum ProcessInfoRole
    {
        DisplayRole = Qt::DisplayRole,

        StateRole = Qt::UserRole,
    };

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;

private:
    QPointer<ProcessInfoManager> m_processInfos;
    QMap<int, bool> m_buttonPressedState;
};

#endif // PROCESSINFOMODEL_H
