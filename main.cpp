#include <iostream>
#include "kernel.h"

int main(int argc,char **argv)
{
    MOKernel knl;
    knl.boot();
    if(!knl.fileSystemManager().mount("sys","disk0","realfs"))
    {
        std::cerr << "Failed to mount 'sys' as 'disk0' with 'realfs'" << std::endl;
        return 1;
    };
    Volume *v = knl.fileSystemManager().getVolume("sys");
    auto dir = v -> listDirectory(".");
    std::cout << "Files in 'sys':" << std::endl;
    for(const auto &file : dir)
    {
        std::cout << '\t' << file.name << std::endl;
    }
    return 0;
}
