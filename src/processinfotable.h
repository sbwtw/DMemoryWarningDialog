#ifndef PROCESSINFOTABLE_H
#define PROCESSINFOTABLE_H

#include <QTableView>

class ProcessInfoTable : public QTableView
{
    Q_OBJECT

public:
    explicit ProcessInfoTable(QWidget *parent = nullptr);
};

#endif // PROCESSINFOTABLE_H
