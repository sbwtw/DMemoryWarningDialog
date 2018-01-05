#include "processinfomanager.h"

#include <QTimer>
#include <QDebug>

ProcessInfoManager::ProcessInfoManager(QObject *parent)
    : QObject(parent)
{
    QTimer::singleShot(1, this, &ProcessInfoManager::scanProcessInfos);
}

void ProcessInfoManager::scanProcessInfos()
{
    PROCTAB *procTable = openproc(PROC_FILLMEM);
    proc_t procInfo;
    memset(&procInfo, 0, sizeof(proc_t));

    while (readproc(procTable, &procInfo) != nullptr) {
        processInfoList << procInfo;
    }
    closeproc(procTable);

    emit processInfoListChanged();
}
