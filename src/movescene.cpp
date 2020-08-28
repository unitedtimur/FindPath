#include "movescene.h"
#include "configuration.h"

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>
#include <iostream>

MoveScene::MoveScene(QObject* parent) :
    QGraphicsScene(parent)
{

}

void MoveScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() & Qt::LeftButton)
    {
        QGraphicsRectItem* rect =  (QGraphicsRectItem*)itemAt(mouseEvent->scenePos(), QTransform());

        if (!rect)
            return;

        rect->setBrush(QBrush(QColor(128, 128, 128)));
        qDebug() << "Pressed";
    }
}

void MoveScene::generatedField(const qint32& w, const qint32& h)
{
    this->clear();

    for (qint32 x = 0; x < w; ++x)
    {
        for (qint32 y = 0; y < h; ++y)
        {
            this->addRect(x * Configuration::SIZE_CELL,
                          y * Configuration::SIZE_CELL,
                          Configuration::SIZE_CELL,
                          Configuration::SIZE_CELL,
                          Qt::SolidLine,
                          QBrush(QColor(221, 247, 92), Qt::SolidPattern));
        }
    }

    this->setSceneRect(this->itemsBoundingRect());
}
