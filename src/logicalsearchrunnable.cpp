#include "include/logicalsearchrunnable.h"

LogicalSearchRunnable::LogicalSearchRunnable(const QSharedPointer<Ilogicalsearch>& logicalSearch) :
    m_logicalSearch(logicalSearch)
{
}

void LogicalSearchRunnable::run()
{
    // Build path
    m_logicalSearch->logic();
}
