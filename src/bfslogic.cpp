#include "bfslogic.h"
#include "graphicscell.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;


BFSLogic::BFSLogic(QVector<QVector<GraphicsCell *> > cellss, const qint32 &w, const qint32 &h)
{
    const auto parse = cellss;

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
