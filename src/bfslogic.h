#ifndef BFSLOGIC_H
#define BFSLOGIC_H

#include <QObject>
#include <QVector>

#include "point.h"

class GraphicsCell;

class BFSLogic : public QObject
{
    Q_OBJECT

public:
    explicit BFSLogic(QVector<QVector<GraphicsCell*>>& cells, QVector<GraphicsCell*>& memorablePathCells, const qint32& w, const qint32& h);

    Q_SLOT void logic();
    Q_SIGNAL void handleError(const QString& error);
    Q_SIGNAL void finish();

private:

    QVector<QVector<GraphicsCell*>> cells;
    QVector<GraphicsCell*>& memorablePathCells;
    qint32 w;
    qint32 h;
};

#endif // BFSLOGIC_H
