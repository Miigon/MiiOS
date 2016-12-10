#include <iostream>
#include <dirent.h>
#include "kernel.h"
#include "driver.h"
#include "filesystem.h"

class RealFileSystem : public FileSystem
{
public:
    Volume *newVolume(const std::string &disk) override;
};

class RealVolume : public Volume
{
public:
    RealVolume(std::string disk);
    virtual std::vector<FileInfo> listDirectory(const std::string &path);
private:
    std::string mRealPath;
};

RealVolume::RealVolume(std::string disk)
    :mRealPath(std::move(disk))
{
};

std::vector<FileInfo> RealVolume::listDirectory(const std::string &path)
{
    DIR *d = opendir((mRealPath + '/' + path).c_str());
    if(d == nullptr) return {};
    std::vector<FileInfo> v;
    dirent *f;
    while((f = readdir(d)) != nullptr)
    {
        FileInfo::FileType ft;
        if(f->d_type == DT_DIR) ft = FileInfo::Directory;
        else if(f->d_type == DT_REG) ft = FileInfo::File;
        else continue;
        FileInfo fi;
        fi.name = std::move(std::string(f->d_name,f->d_namlen));
        fi.type = std::move(ft);
        v.push_back(std::move(fi));
    }
    return std::move(v);
}

Volume* RealFileSystem::newVolume(const std::string &disk)
{
    DIR *d = opendir(disk.c_str());
    if(d == nullptr)
    {
        return nullptr;
    }
    closedir(d);
    return new RealVolume(disk);
}

DRVAPI void DVInit(MOKernel *knl)
{
    std::cout << "RealDisk filesystem(realfs) provider initializing..." << std::endl;
    knl->fileSystemManager().registerFileSystem("realfs",new RealFileSystem());
}
