#include "include/gameview.h"

#include <QWheelEvent>

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void GameView::wheelEvent(QWheelEvent *event)
{
    const double scaleFactor = 1.17;
    const QPoint angleDate = event->angleDelta();

    // For scale to under mouse cursor with one or two wheels
    if (angleDate.y() > 0 || angleDate.x() > 0)
    {
        this->scale(scaleFactor, scaleFactor);
    }
    else
    {
        this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    event->accept();
}
