#include <iostream>
#include "common.h"
#include "kernel.h"

MOKernel::MOKernel()
    :mDrivers(*this),mFileSystems(*this)
{
}

int MOKernel::boot()
{
    std::cout << "Booting MiiOS " << Version << std::endl;
    mDrivers.initDrivers();
    return 0;
}