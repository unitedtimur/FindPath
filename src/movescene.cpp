#include "movescene.h"
#include "configuration.h"
#include "bfslogic.h"

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QWheelEvent>
#include <QThreadPool>
#include <queue>
#include <vector>
#include <list>

#include "bfsrunnable.h"

using namespace std;

MoveScene::MoveScene(QObject* parent) :
    QGraphicsScene(parent),
    bfsLogic(nullptr)
{
}

MoveScene::~MoveScene()
{
    if (!bfsLogic)
        delete bfsLogic;

    for (auto& row : this->cells)
    {
        for (auto& column : row)
            delete column;
    }
}

void MoveScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() & Qt::LeftButton)
    {
        GraphicsCell* rect = dynamic_cast<GraphicsCell*>(itemAt(mouseEvent->scenePos(), QTransform()));

        if (!rect)
            return;

        if (rect->getStatus() & GraphicsCell::Status::JustCell)
        {
            rect->setStatus(GraphicsCell::Status::StartCell);
        }
        else if (!(rect->getStatus() & GraphicsCell::Status::BarrierCell))
        {
            const auto startCell = findCell(GraphicsCell::Status::StartCell);

            if (!startCell)
                return;

            startCell->setStatus(GraphicsCell::Status::JustCell);
            rect->setStatus(GraphicsCell::Status::StartCell);

            for (const auto& it : this->memorablePathCells)
            {
                it->setStatus(GraphicsCell::Status::JustCell);
            }

            memorablePathCells.clear();
        }
    }
}

void MoveScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    const auto startCell = this->findCell(GraphicsCell::Status::StartCell);

    if (!startCell)
        return;

    const auto finishCell = dynamic_cast<GraphicsCell*>(itemAt(event->scenePos(), QTransform()));

    if (!finishCell)
        return;

    if (startCell != finishCell && !(finishCell->getStatus() & GraphicsCell::Status::BarrierCell))
    {
        for (const auto& it : this->memorablePathCells)
        {
            it->setStatus(GraphicsCell::Status::JustCell);
        }

        memorablePathCells.clear();

        finishCell->setStatus(GraphicsCell::Status::FinishCell);

        memorablePathCells.push_back(finishCell);

        this->bfs();
    }
}

GraphicsCell *MoveScene::findCell(const GraphicsCell::Status &status)
{
    for (const auto& row : this->getCells())
    {
        for (const auto& column : row)
        {
            if (column->getStatus() & status)
                return column;
        }
    }

    return nullptr;
}

void MoveScene::bfs()
{
    emit clearHandleError();

    bfsLogic = new BFSLogic(this->cells, this->memorablePathCells, this->w, this->h);

    // Connect bfsLogic for handle error with slot by MoveScene
    connect(bfsLogic, &BFSLogic::handleError, this, &MoveScene::handledError);

    BFSRunnable bfsRunnable(bfsLogic);
    bfsRunnable.setAutoDelete(false);

    QThreadPool* threadPool = QThreadPool::globalInstance();
    threadPool->start(&bfsRunnable);

    threadPool->waitForDone();

    // Disconnect bfcLogic handle error signal with handledError slot
    disconnect(bfsLogic, &BFSLogic::handleError, this, &MoveScene::handledError);

    delete bfsLogic;
}

void MoveScene::generatedField(const qint32& w, const qint32& h)
{
    this->clear();
    this->w = w;
    this->h = h;

    memorablePathCells.clear();

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

    srand(time(0));

    this->generateBarriers();
}

void MoveScene::handledError(const QString &error)
{
    emit handleError(error);
}

void MoveScene::generateBarriers()
{
    const auto parse = this->getCells();

    for (const auto& row : parse)
    {
        for (const auto& column : row)
        {
            if (rand() % 3 == 0)
            {
                column->setStatus(GraphicsCell::Status::BarrierCell);
            }
        }
    }
}

QVector<QVector<GraphicsCell*>>& MoveScene::getCells()
{
    return cells;
}
