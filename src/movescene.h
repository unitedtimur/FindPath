#ifndef MOVESCENE_H
#define MOVESCENE_H

#include <QGraphicsScene>

class QObject;
class QWheelEvent;

class MoveScene : public QGraphicsScene
{
public:
    explicit MoveScene(QObject* parent = nullptr);

    Q_SLOT void generatedField(const qint32& w, const qint32& h);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
};

#endif // MOVESCENE_H
