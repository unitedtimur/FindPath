#include <QApplication>
#include "manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Manager manager;
    manager.show();

    QApplication::exec();

    return 0;
}
