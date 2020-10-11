#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>

namespace configuration
{
    static const qreal GRAPHIC_VIEW_WIDTH = 300;
    static const qreal GRAPHIC_VIEW_HEIGHT = 300;
    static const qint32 SIZE_CELL = 20;

    static const QString ORGANIZATION = "UnitedTimurCompany (c)";
    static const QString APPLICATION = "FindPath";

    static const QString ERROR_NO_PATH = "Нет такого пути!";

    namespace images
    {
        static const QString ICON = ":/images/icon.png";
    }

}

#endif // CONFIGURATION_H
