#ifndef GRAPHICSCELL_H
#define GRAPHICSCELL_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>

class GraphicsCell : public QGraphicsRectItem
{
public:
    enum Status
    {
        JustCell    = 0x01,
        StartCell   = 0x02,
        FinishCell  = 0x04,
        BarrierCell = 0x08,
        PathCell    = 0x10
    };
    explicit GraphicsCell() = default;
    explicit GraphicsCell(const Status& status);

    void setStatus(const Status& status);
    Status getStatus() const;

    void update();

    void setX(const qint32& x);
    void setY(const qint32& y);

    qint32 getX() const;
    qint32 getY() const;

private:
    qint32 x;
    qint32 y;

    Status status;
};

#endif // GRAPHICSCELL_H
