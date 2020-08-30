#include "movescene.h"
#include "configuration.h"
#include "graphicscell.h"

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QWheelEvent>
#include <QDebug>
#include <iostream>
#include <QQueue>
#include <queue>

#include <vector>
#include <list>

#include "bfslogic.h"

using namespace std;

class Graph
{
    int numVertices;
    QList<int> *adjLists;
    bool *visited;

public:
    Graph(int V);
    void addEdge(int src, int dest);
    void DFS(int vertex);
};

Graph::Graph(int vertices)
{
    numVertices = vertices;
    adjLists = new QList<int>[vertices];
    visited = new bool[vertices];
}

void Graph::addEdge(int src, int dest)
{
    adjLists[src].push_front(dest);
}

void Graph::DFS(int vertex)
{

    visited[vertex] = true;
    QList<int> adjList = adjLists[vertex];

    std::cout << vertex << " ";

    QList<int>::iterator i;
    for(i = adjList.begin(); i != adjList.end(); ++i)
        if(!visited[*i])
            DFS(*i);
}

MoveScene::MoveScene(QObject* parent) :
    QGraphicsScene(parent)
{
}

void MoveScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() & Qt::LeftButton)
    {
        QVector<QVector<GraphicsCell*>> cells = this->getCells();

        GraphicsCell* rect =  dynamic_cast<GraphicsCell*>(itemAt(mouseEvent->scenePos(), QTransform()));

        if (!rect)
            return;

        switch (rect->getStatus())
        {
        case GraphicsCell::Status::JustCell:
            rect->setStatus(GraphicsCell::Status::BarrierCell);
            break;
        case GraphicsCell::Status::BarrierCell:
            rect->setStatus(GraphicsCell::Status::StartCell);
            break;
        case GraphicsCell::Status::StartCell:
            rect->setStatus(GraphicsCell::Status::FinishCell);
            bfs(this->w, this->h);
            break;
        case GraphicsCell::Status::FinishCell:
            rect->setStatus(GraphicsCell::Status::JustCell);
            break;
        }
    }
}

void MoveScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //BFSLogic bfcLogic(this->getCells(), this->w, this->h);
}

struct Point
{
public:
    explicit Point()
    {
        x = 0;
        y = 0;
        code = 0;
    }
    explicit Point(int y, int x, int code)
    {
        this->x = x;
        this->y = y;
        this->code = code;
    }

    int x;
    int y;
    int code;
};

void MoveScene::bfs(qint32 w, qint32 h)
{
    const auto parse = this->getCells();

    queue<GraphicsCell*> cells;
    vector<vector<Point>> matrixPath(h, vector<Point>(w));

    qint32 cellY;
    qint32 cellX;

    for (const auto& row : parse)
    {
        for (const auto& column : row)
        {
            if (column->getStatus() == GraphicsCell::Status::StartCell)
            {
                cells.push(column);
            }
            else if (column->getStatus() == GraphicsCell::Status::BarrierCell)
            {
                cellY = column->getY();
                cellX = column->getX();

                matrixPath[cellY][cellX] = Point(cellY, cellX, -1);
            }
        }
    }

    matrixPath[cells.front()->getY()][cells.front()->getX()] = Point(cells.front()->getY(), cells.front()->getX(), 1);

    while (!cells.empty())
    {
        GraphicsCell* cell = cells.front();

        cellY = cell->getY();
        cellX = cell->getX();

        if (cellY != 0 && matrixPath[cellY - 1][cellX].code == 0)
        {
            matrixPath[cellY - 1][cellX] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY - 1][cellX]);

            if (cells.back()->getStatus() == GraphicsCell::Status::FinishCell)
                break;
        }

        if (cellY != parse.size() - 1 && matrixPath[cellY + 1][cellX].code == 0)
        {
            matrixPath[cellY + 1][cellX] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY + 1][cellX]);

            if (cells.back()->getStatus() == GraphicsCell::Status::FinishCell)
                break;
        }

        if (cellX != 0 && matrixPath[cellY][cellX - 1].code == 0)
        {
            matrixPath[cellY][cellX - 1] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY][cellX - 1]);

            if (cells.back()->getStatus() == GraphicsCell::Status::FinishCell)
                break;
        }

        if (cellX != parse[0].size() - 1 && matrixPath[cellY][cellX + 1].code == 0)
        {
            matrixPath[cellY][cellX + 1] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY][cellX + 1]);

            if (cells.back()->getStatus() == GraphicsCell::Status::FinishCell)
                break;
        }

        cells.pop();
    }

    if (cells.empty())
    {
        emit handleError("Невозможно построить путь");
        return;
    }

    cellX = cells.back()->getX();
    cellY = cells.back()->getY();

    qint32 currentNumber = matrixPath[cellY][cellX].code;

    for (qint32 i = 0; i < currentNumber; ++i)
    {
        parse[cellY][cellX]->setStatus(GraphicsCell::Status::PathCell);

        qint32 tempX = cellX;
        qint32 tempY = cellY;

        cellY = matrixPath[tempY][tempX].y;
        cellX = matrixPath[tempY][tempX].x;
    }

}

void MoveScene::generatedField(const qint32& w, const qint32& h)
{
    this->clear();

    this->w = w;
    this->h = h;

    cells.resize(this->h);

    for (qint32 y = 0; y < this->h; ++y)
    {
        cells[y].resize(this->w);

        for (qint32 x = 0; x < this->w; ++x)
        {
            cells[y][x] = new GraphicsCell(GraphicsCell::Status::JustCell);
            cells[y][x]->setRect(QRectF(x * Configuration::SIZE_CELL,
                                        y * Configuration::SIZE_CELL,
                                        Configuration::SIZE_CELL,
                                        Configuration::SIZE_CELL));
            cells[y][x]->setX(x);
            cells[y][x]->setY(y);
            this->addItem(cells[y][x]);
        }
    }
}

QVector<QVector<GraphicsCell*>> MoveScene::getCells()
{
    return cells;
}
