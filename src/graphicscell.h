#ifndef GRAPHICSCELL_H
#define GRAPHICSCELL_H

#include <QGraphicsRectItem>

class GraphicsCell : public QGraphicsRectItem
{
public:
    explicit GraphicsCell();

private:
    int x;
    int y;
    int f;
    int w;
    int h;

    GraphicsCell* parent;
    QGraphicsRectItem* infoBox;
};

#endif // GRAPHICSCELL_H
