#ifndef MOVESCENE_H
#define MOVESCENE_H

#include <QGraphicsScene>

class QObject;
class QWheelEvent;
class GraphicsCell;

class MoveScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MoveScene(QObject* parent = nullptr);

    Q_SLOT void generatedField(const qint32& w, const qint32& h);

    Q_SIGNAL void handleError(const QString& error);

protected:
    QVector<QVector<GraphicsCell*>> getCells();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;


    Q_SIGNAL void startBFS(qint32 w, qint32 h);
    Q_SLOT void bfs(qint32 w, qint32 h);

private:
    QVector<QVector<GraphicsCell*>> cells;
    qint32 w;
    qint32 h;
};

#endif // MOVESCENE_H
