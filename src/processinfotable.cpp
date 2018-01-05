#include "processinfotable.h"

#include <QHeaderView>
#include <QDebug>

ProcessInfoTable::ProcessInfoTable(QWidget *parent)
    : QTableView(parent)
{
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    setFrameStyle(QFrame::NoFrame);
    setSelectionMode(NoSelection);
}
