#ifndef MIIOS_KERNEL_H
#define MIIOS_KERNEL_H
#include "driver.h"
#include "filesystem.h"

class MOKernel
{
public:
    MOKernel();
    int boot();
    FileSystemManager &fileSystemManager(){return mFileSystems;};
    DriverManager &driverManager(){return mDrivers;};
private:
    DriverManager mDrivers;
    FileSystemManager mFileSystems;
};

#endif
