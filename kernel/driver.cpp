#include <iostream>
#include <dirent.h>
#include "driver.h"
#include "dlfcn.h"

DriverManager::DriverManager(MOKernel &knl)
    :mKnl(knl)
{
    
}

void DriverManager::initDrivers()
{
    std::cout << "Searching drivers..." << std::endl;
    const char *driverpath = "./drivers/";
    DIR *driverdir = opendir(driverpath);
    if(driverdir == nullptr)
    {
        throw std::runtime_error("Failed to open drivers' directory");
    }
    dirent *f;
    while((f = readdir(driverdir)) != nullptr)
    {
        if((strcmp(f->d_name,".") == 0) || (strcmp(f->d_name,"..") == 0))
            continue;
        if(f -> d_type == DT_REG)
        {
            std::string filename(f->d_name,f->d_namlen);
            if(filename.substr(filename.length() - 4,filename.length()) == ".drv")
            {
                std::cout << "Loading " << filename << std::endl;
                if(!loadDriver(driverpath + filename))
                {
                    std::cout << "Invaild driver:" << filename << std::endl;
                }
            }
        }
    }
}

bool DriverManager::loadDriver(const std::string &path)
{
    void *dl = dlopen(path.c_str(),0);
    if(dl == nullptr) return false;
    Driver *drv = new Driver(dl,&mKnl);
    return true;
}

#define GETDRVAPI(dl,name,symbol) name = (typeof(name))dlsym(dl,symbol)
Driver::Driver(void *dl,MOKernel* knl)
{
    GETDRVAPI(dl,DVInit,"DVInit");
    DVInit(knl);
}

