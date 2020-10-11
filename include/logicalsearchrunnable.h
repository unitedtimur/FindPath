#ifndef LOGICALSEARCHRUNNABLE_H
#define LOGICALSEARCHRUNNABLE_H

#include <QRunnable>
#include <QSharedPointer>

#include "include/ilogicalsearch.h"

class LogicalSearchRunnable : public QRunnable
{
public:
    explicit LogicalSearchRunnable(const QSharedPointer<Ilogicalsearch>& logicalSearch);

    void run() override;

private:
    QSharedPointer<Ilogicalsearch> m_logicalSearch;
};

#endif // LOGICALSEARCHRUNNABLE_H
