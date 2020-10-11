#include <QApplication>

#include "include/manager.h"
#include "include/configuration.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName(configuration::APPLICATION);
    QApplication::setOrganizationName(configuration::ORGANIZATION);

    Manager manager;
    manager.show();

    QApplication::exec();

    return 0;
}
