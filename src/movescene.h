#ifndef MOVESCENE_H
#define MOVESCENE_H

#include <QGraphicsScene>
#include "graphicscell.h"

class QObject;
class QWheelEvent;
class GraphicsCell;
class BFSLogic;

class MoveScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MoveScene(QObject* parent = nullptr);
    ~MoveScene();

    Q_SIGNAL void handleError(const QString& error);
    Q_SIGNAL void clearHandleError();
    Q_SLOT void handledError(const QString& error);

    void generatedField(const qint32& w, const qint32& h);

protected:
    QVector<QVector<GraphicsCell*>>& getCells();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    GraphicsCell* findCell(const GraphicsCell::Status& status);

    void generateBarriers();
    void bfs();

private:
    QVector<QVector<GraphicsCell*>> cells;
    QVector<GraphicsCell*> memorablePathCells;
    qint32 w;
    qint32 h;
    BFSLogic* bfsLogic;
};

#endif // MOVESCENE_H
