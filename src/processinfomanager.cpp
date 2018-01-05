#include "processinfomanager.h"

#include <QTimer>
#include <QDebug>
#include <QX11Info>
#include <QWindow>
#include <QFile>

#include <X11/Xlib.h>
#include <X11/Xatom.h>

ProcessInfoManager::ProcessInfoManager(QObject *parent)
    : QObject(parent)
{
    QTimer::singleShot(1, this, &ProcessInfoManager::scanProcessInfos);
}

void ProcessInfoManager::scanProcessInfos()
{
    auto *display = QX11Info::display();
    const Atom clients_atom = XInternAtom(display, "_NET_CLIENT_LIST", true);
    const Atom pid_atom = XInternAtom(display, "_NET_WM_PID", true);

    Atom actual_type_return;
    int actual_format_return;
    unsigned long n_items_return;
    unsigned long bytes_after_return;
    unsigned char *prop_to_return;

    int scaned_windows_num = 0;
    const int items_per_loop = 16;
    do {
        const auto r = XGetWindowProperty(display, DefaultRootWindow(display), clients_atom, scaned_windows_num, items_per_loop, false, XA_WINDOW,
                                          &actual_type_return, &actual_format_return, &n_items_return, &bytes_after_return, &prop_to_return);
        if (r)
        {
            XFree(prop_to_return);
            break;
        }

        scaned_windows_num += n_items_return;
        const unsigned long *clients = reinterpret_cast<const unsigned long *>(prop_to_return);
        for (int i(0); i != n_items_return; ++i)
        {
            // get PID of window
            unsigned long n_items_return;
            unsigned char *prop_to_return;
            const auto r = XGetWindowProperty(display, clients[i], pid_atom, 0, 1, false, XA_CARDINAL,
                                              &actual_type_return, &actual_format_return, &n_items_return, &bytes_after_return, &prop_to_return);

            // append pid
            if (!r && n_items_return)
                appendProcess(reinterpret_cast<const unsigned long *>(prop_to_return)[0]);

            XFree(prop_to_return);
        }

        XFree(prop_to_return);
    } while (n_items_return == items_per_loop);

    emit processInfoListChanged();
}

void ProcessInfoManager::appendProcess(const int pid)
{
    QFile cgroupInfo(QString("/proc/%1/cgroup").arg(pid));
    if (!cgroupInfo.open(QIODevice::ReadOnly))
        return;

    const QString &content = cgroupInfo.readAll();
    for (const auto &info : content.split('\n'))
    {
        const auto &items = info.split(':');
        if (items.size() != 3 || items[1] != "memory" || !items[2].contains("uiapps"))
            continue;
        qDebug() << items[2];
    }
}
