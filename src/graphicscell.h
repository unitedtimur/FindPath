#ifndef GRAPHICSCELL_H
#define GRAPHICSCELL_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>

class GraphicsCell : public QGraphicsRectItem
{
public:
    enum class Status : quint16
    {
        JustCell    = 0b00001,
        StartCell   = 0b00010,
        FinishCell  = 0b00100,
        BarrierCell = 0b01000,
        PathCell    = 0b10000
    };
    explicit GraphicsCell() = default;
    explicit GraphicsCell(const Status& status);

    void setStatus(const Status& status);
    Status getStatus() const;
    qint32 code();

    void update();
    qint32 cod;

    void setX(const qreal& x);
    void setY(const qreal& y);

    qreal getX() const;
    qreal getY() const;

private:
    qreal x;
    qreal y;

    Status status;
};

#endif // GRAPHICSCELL_H
