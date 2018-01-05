#ifndef PROCESSINFOMANAGER_H
#define PROCESSINFOMANAGER_H

#include <QObject>
#include <QList>

class ProcessInfo
{

};

class ProcessInfoModel;
class ProcessInfoManager : public QObject
{
    Q_OBJECT

    friend class ProcessInfoModel;

public:
    explicit ProcessInfoManager(QObject *parent = nullptr);

signals:
    void processInfoListChanged() const;

private slots:
    void scanProcessInfos();

private:
    void appendProcess(const int pid);

private:
    QList<ProcessInfo> processInfoList;
};

#endif // PROCESSINFOMANAGER_H
