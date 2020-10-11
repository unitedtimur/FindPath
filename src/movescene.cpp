#include "include/movescene.h"
#include "include/configuration.h"
#include "include/ilogicalsearch.h"
#include "include/bfslogic.h"
#include "include/logicalsearchrunnable.h"

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QWheelEvent>
#include <QThreadPool>
#include <queue>
#include <vector>
#include <list>

using namespace std;

MoveScene::MoveScene(QObject* parent) :
    QGraphicsScene(parent),
    m_alogirthm(Algorithm::BFS)
{
}

MoveScene::~MoveScene()
{
    for (auto& row : m_cells)
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

            for (const auto& it : m_memorablePathCells)
            {
                it->setStatus(GraphicsCell::Status::JustCell);
            }

            m_memorablePathCells.clear();
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
        for (const auto& it : m_memorablePathCells)
        {
            it->setStatus(GraphicsCell::Status::JustCell);
        }

        m_memorablePathCells.clear();

        finishCell->setStatus(GraphicsCell::Status::FinishCell);

        m_memorablePathCells.push_back(finishCell);

        this->logicalSearch();
    }
}

GraphicsCell *MoveScene::findCell(const GraphicsCell::Status &status)
{
    for (const auto& row : m_cells)
    {
        for (const auto& column : row)
        {
            if (column->getStatus() & status)
                return column;
        }
    }

    return nullptr;
}

void MoveScene::logicalSearch()
{
    emit clearHandleError();

    QSharedPointer<Ilogicalsearch> search;

    switch (m_alogirthm)
    {
    case Algorithm::BFS:
        search = QSharedPointer<Ilogicalsearch>(new BFSLogic(m_cells, m_memorablePathCells, m_w, m_h));
        // Connect bfsLogic for handle error with slot by MoveScene
        connect(static_cast<BFSLogic*>(search.data()), &BFSLogic::handleError, this, &MoveScene::handledError);
        break;

    case Algorithm::DFS:
        // TODO here
        break;

    case Algorithm::DIJKSTRA:
        // TODO here
        break;

    default:
        search = QSharedPointer<Ilogicalsearch>(new BFSLogic(m_cells, m_memorablePathCells, m_w, m_h));
        // Connect bfsLogic for handle error with slot by MoveScene
        connect(static_cast<BFSLogic*>(search.data()), &BFSLogic::handleError, this, &MoveScene::handledError);
        break;
    }

    LogicalSearchRunnable bfsRunnable(search);
    bfsRunnable.setAutoDelete(false);

    QThreadPool* threadPool = QThreadPool::globalInstance();
    threadPool->start(&bfsRunnable);
    threadPool->waitForDone();
}

void MoveScene::generatedField(const qint32& w, const qint32& h)
{
    this->clear();
    m_w = w;
    m_h = h;

    m_memorablePathCells.clear();

    m_cells.resize(m_h);

    for (qint32 y = 0; y < m_h; ++y)
    {
        m_cells[y].resize(m_w);

        for (qint32 x = 0; x < m_w; ++x)
        {
            m_cells[y][x] = new GraphicsCell(GraphicsCell::Status::JustCell);
            m_cells[y][x]->setRect(QRectF(x * configuration::SIZE_CELL,
                                        y * configuration::SIZE_CELL,
                                        configuration::SIZE_CELL,
                                        configuration::SIZE_CELL));
            m_cells[y][x]->setX(x);
            m_cells[y][x]->setY(y);
            this->addItem(m_cells[y][x]);
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
    for (const auto& row : m_cells)
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
