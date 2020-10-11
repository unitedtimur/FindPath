#ifndef MOVESCENE_H
#define MOVESCENE_H

#include <QGraphicsScene>
#include "include/graphicscell.h"

class QObject;
class QWheelEvent;
class GraphicsCell;

class MoveScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum class Algorithm
    {
        BFS = 0x00,
        DFS,
        DIJKSTRA
    };

    explicit MoveScene(QObject* parent = nullptr);
    ~MoveScene();

    Q_SIGNAL void handleError(const QString& error);
    Q_SIGNAL void clearHandleError();
    Q_SLOT void handledError(const QString& error);

    void generatedField(const qint32& w, const qint32& h);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    GraphicsCell* findCell(const GraphicsCell::Status& status);

    void generateBarriers();
    void logicalSearch();

private:
    QVector<QVector<GraphicsCell*>> m_cells;
    QVector<GraphicsCell*> m_memorablePathCells;
    qint32 m_w;
    qint32 m_h;
    Algorithm m_alogirthm;
};

#endif // MOVESCENE_H
