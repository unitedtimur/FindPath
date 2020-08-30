#include "bfslogic.h"
#include "graphicscell.h"
#include "configuration.h"

#include <queue>
#include <vector>

using namespace std;


BFSLogic::BFSLogic(QVector<QVector<GraphicsCell*>>& cells, QVector<GraphicsCell*>& memorablePathCells, const qint32 &w, const qint32 &h) :
    cells(cells),
    memorablePathCells(memorablePathCells),
    w(w),
    h(h)
{
}

void BFSLogic::logic()
{
    const QVector<QVector<GraphicsCell*>> parse = this->cells;

    queue<GraphicsCell*> cells;
    vector<vector<Point>> matrixPath(h, vector<Point>(w));

    qint32 cellY;
    qint32 cellX;

    // MatrixPath is store the coordinates by parent and his code number
    for (const auto& row : parse)
    {
        for (const auto& column : row)
        {
            if (column->getStatus() == GraphicsCell::Status::StartCell)
            {
                // The start cell
                cells.push(column);
            }
            else if (column->getStatus() == GraphicsCell::Status::BarrierCell)
            {
                // Set -1 in matrixPath where is barrier
                cellY = column->getY();
                cellX = column->getX();

                matrixPath[cellY][cellX] = Point(cellY, cellX, -1);
            }
        }
    }

    // Get the start cell coordinates
    cellY = cells.front()->getY();
    cellX = cells.front()->getX();

    // Set for start cell code number like 1
    matrixPath[cellY][cellX] = Point(cellY, cellX, 1);

    // Work while cells not is empty
    while (!cells.empty())
    {
        // Get the first elemnt in queue
        GraphicsCell* cell = cells.front();

        cellY = cell->getY();
        cellX = cell->getX();

        // Look at top
        if (cellY != 0 && matrixPath[cellY - 1][cellX].code == 0)
        {
            if (parse[cellY - 1][cellX]->getStatus() & GraphicsCell::Status::FinishCell)
            {
                break;
            }

            matrixPath[cellY - 1][cellX] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY - 1][cellX]);
        }

        // Look at bottom
        if (cellY != parse.size() - 1 && matrixPath[cellY + 1][cellX].code == 0)
        {
            if (parse[cellY + 1][cellX]->getStatus() & GraphicsCell::Status::FinishCell)
            {
                break;
            }

            matrixPath[cellY + 1][cellX] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY + 1][cellX]);
        }

        // Look at left
        if (cellX != 0 && matrixPath[cellY][cellX - 1].code == 0)
        {
            if (parse[cellY][cellX - 1]->getStatus() & GraphicsCell::Status::FinishCell)
            {
                break;
            }

            matrixPath[cellY][cellX - 1] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY][cellX - 1]);
        }

        // Look at right
        if (cellX != parse[0].size() - 1 && matrixPath[cellY][cellX + 1].code == 0)
        {
            if (parse[cellY][cellX + 1]->getStatus() & GraphicsCell::Status::FinishCell)
            {
                break;
            }

            matrixPath[cellY][cellX + 1] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY][cellX + 1]);
        }

        cells.pop();
    }

    // If not path from start cell to finish cell
    if (cells.empty())
    {
        emit handleError(Configuration::ERROR_NO_PATH);
        return;
    }

    cellX = cells.front()->getX();
    cellY = cells.front()->getY();

    // Get the code number finish cell
    qint32 currentNumber = matrixPath[cellY][cellX].code - 1;

    // Make the back path to start cell
    for (qint32 i = 0; i < currentNumber; ++i)
    {
        memorablePathCells.push_back(parse[cellY][cellX]);

        parse[cellY][cellX]->setStatus(GraphicsCell::Status::PathCell);

        qint32 tempX = cellX;
        qint32 tempY = cellY;

        cellY = matrixPath[tempY][tempX].y;
        cellX = matrixPath[tempY][tempX].x;
    }

    emit finish();
}
