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
        JustCell    = 0b0001,
        StartCell   = 0b0010,
        FinishCell  = 0b0100,
        BarrierCell = 0b1000
    };

    explicit GraphicsCell(const QRectF& rect, const Status& status);



    void setStatus(const Status& status);
    const Status& getStatus() const;

    void update();

private:
    int x;
    int y;
    int f;
    int w;
    int h;

    Status status;
};

#endif // GRAPHICSCELL_H
