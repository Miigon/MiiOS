#ifndef MIIOS_DRIVER_H
#define MIIOS_DRIVER_H
#include <string>

class MOKernel;
class Driver
{
public:
    Driver(void *dl,MOKernel *knl);
    void(*DVInit)(MOKernel *);
private:
};

class DriverManager
{
public:
    DriverManager(MOKernel &knl);
    void initDrivers();
    bool loadDriver(const std::string &path);
private:
    MOKernel &mKnl;
};

#define DRVAPI extern "C"

#endif
