#include "bfsrunnable.h"
#include "bfslogic.h"

BFSRunnable::BFSRunnable(BFSLogic* bfsLogic) :
    bfsLogic(bfsLogic)
{
}

void BFSRunnable::run()
{
    // Build path
    bfsLogic->logic();
}
