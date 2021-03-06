#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

class QWheelEvent;

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GameView(QWidget* parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent* event) override;
};

#endif // GAMEVIEW_H
