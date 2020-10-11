#ifndef ILOGICALSEARCH_H
#define ILOGICALSEARCH_H

#include <QObject>
#include <QString>

class Ilogicalsearch : public QObject
{
    Q_OBJECT

public:
    virtual ~Ilogicalsearch() = default;
    Q_SLOT virtual void logic() = 0;
};

#endif // ILOGICALSEARCH_H
