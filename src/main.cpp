
#include "dmemorywarningdialog.h"

#include <DApplication>

DWIDGET_USE_NAMESPACE

int main(int argc, char *args[])
{
    DApplication::loadDXcbPlugin();
    DApplication dapp(argc, args);

    DMemoryWarningDialog dialog;
    dialog.show();

    return dapp.exec();
}
