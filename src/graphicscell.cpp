#include "graphicscell.h"
#include "configuration.h"

GraphicsCell::GraphicsCell(const QRectF &rect, const Status& status):
    QGraphicsRectItem(rect)
{
    this->status = status;
    this->update();
}

void GraphicsCell::setStatus(const GraphicsCell::Status &status)
{
    this->status = status;
    this->update();
}

const GraphicsCell::Status &GraphicsCell::getStatus() const
{
    return status;
}

void GraphicsCell::update()
{
    switch (status)
    {
    case Status::JustCell:
        this->setBrush(QBrush(QColor(221, 247, 92), Qt::SolidPattern));
        break;
    case Status::StartCell:
        this->setBrush(QBrush(QColor(97, 252, 86), Qt::SolidPattern));
        break;
    case Status::FinishCell:
        this->setBrush(QBrush(QColor(255, 66, 56), Qt::SolidPattern));
        break;
    case Status::BarrierCell:
        this->setBrush(QBrush(QColor(61, 61, 61), Qt::SolidPattern));
        break;
    }

    this->setPen(QPen(Qt::SolidPattern));
}
