#ifndef BFSLOGIC_H
#define BFSLOGIC_H

#include <QVector>

class GraphicsCell;

class BFSLogic
{
public:
    explicit BFSLogic(QVector<QVector<GraphicsCell*>> cells, const qint32& w, const qint32& h);
};

#endif // BFSLOGIC_H
