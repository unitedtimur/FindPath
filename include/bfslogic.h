#ifndef BFSLOGIC_H
#define BFSLOGIC_H

#include <QVector>

#include "include/point.h"
#include "include/ilogicalsearch.h"

class GraphicsCell;

class BFSLogic : public Ilogicalsearch
{
    Q_OBJECT

public:
    explicit BFSLogic(QVector<QVector<GraphicsCell*>>& cells, QVector<GraphicsCell*>& memorablePathCells, const qint32& w, const qint32& h);

    Q_SLOT void logic() override;
    Q_SIGNAL void handleError(const QString& error);
    Q_SIGNAL void finish();

private:

    QVector<QVector<GraphicsCell*>>& m_cells;
    QVector<GraphicsCell*>& m_memorablePathCells;
    qint32 m_w;
    qint32 m_h;
};

#endif // BFSLOGIC_H
