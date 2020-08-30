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

void MoveScene::bfs(qint32 w, qint32 h)
{
    const auto parse = this->getCells();

    queue<GraphicsCell*> cells;
    vector<vector<int>> matrixPath(h, vector<int>(w, 0));

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
                matrixPath[column->getY()][column->getX()] = -1;
            }
        }
    }

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            std::cout << matrixPath[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::flush;

    matrixPath[cells.front()->getY()][cells.front()->getX()] = 1;


    while (!cells.empty())
    {
        GraphicsCell* cell = cells.front();

        if (cell->getY() != 0 && matrixPath[cell->getY() - 1][cell->getX()] == 0)
        {
            matrixPath[cell->getY() - 1][cell->getX()] = matrixPath[cell->getY()][cell->getX()] + 1;
            cells.push(parse[cell->getY() - 1][cell->getX()]);

            if (cells.back()->getStatus() == GraphicsCell::Status::FinishCell)
                break;
        }

        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                std::cout << matrixPath[i][j] << " ";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl << std::flush;

        if (cell->getY() != parse.size() - 1 && matrixPath[cell->getY() + 1][cell->getX()] == 0)
        {
            matrixPath[cell->getY() + 1][cell->getX()] = matrixPath[cell->getY()][cell->getX()] + 1;
            cells.push(parse[cell->getY() + 1][cell->getX()]);

            if (cells.back()->getStatus() == GraphicsCell::Status::FinishCell)
                break;
        }

        if (cell->getX() != 0 && matrixPath[cell->getY()][cell->getX() - 1] == 0)
        {
            matrixPath[cell->getY()][cell->getX() - 1] = matrixPath[cell->getY()][cell->getX()] + 1;
            cells.push(parse[cell->getY()][cell->getX() - 1]);

            if (cells.back()->getStatus() == GraphicsCell::Status::FinishCell)
                break;
        }

        if (cell->getX() != parse[0].size() - 1 && matrixPath[cell->getY()][cell->getX() + 1] == 0)
        {
            matrixPath[cell->getY()][cell->getX() + 1] = matrixPath[cell->getY()][cell->getX()] + 1;
            cells.push(parse[cell->getY()][cell->getX() + 1]);

            if (cells.back()->getStatus() == GraphicsCell::Status::FinishCell)
                break;
        }


        cells.pop();


        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                std::cout << matrixPath[i][j] << " ";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl << std::flush;

    }

    if (cells.empty())
    {
        emit handleError("Невозможно построить путь");
        return;
    }

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            std::cout << matrixPath[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::flush;

    qint32 x = cells.back()->getX();
    qint32 y = cells.back()->getY();

    qint32 currentNumber = matrixPath[y][x];

    while (currentNumber != 0)
    {
        parse[y][x]->setStatus(GraphicsCell::Status::PathCell);

        if (y != 0 && matrixPath[y - 1][x] == currentNumber - 1)
        {
            --y;
        }
        else if (y != parse.size() - 1 && matrixPath[y + 1][x] == currentNumber - 1)
        {
            ++y;
        }
        else if (x != 0 && matrixPath[y][x - 1] == currentNumber - 1)
        {
            --x;
        }
        else if (x != parse[0].size() - 1 && matrixPath[y][x + 1] == currentNumber - 1)
        {
            ++x;
        }

        --currentNumber;
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
