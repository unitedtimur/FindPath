#ifndef BFSRUNNABLE_H
#define BFSRUNNABLE_H

#include <QRunnable>

class BFSLogic;

class BFSRunnable : public QRunnable
{
public:
    explicit BFSRunnable(BFSLogic* bfsLogic);

    void run() override;

private:
    BFSLogic* bfsLogic;
};

#endif // BFSRUNNABLE_H
