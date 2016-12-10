#include "filesystem.h"

FileSystemManager::FileSystemManager(MOKernel &knl)
    :mKnl(knl)
{
    
}

bool FileSystemManager::mount(const std::string &volume,const std::string &disk, const std::string &fstype)
{
    FileSystem *fs = mFss[fstype];
    if(fs != nullptr && mMounted[volume] == nullptr)
    {
        return (mMounted[volume] = fs->newVolume(disk)) != nullptr;
    }
    return false;
}

void FileSystemManager::registerFileSystem(const std::string &fstype, FileSystem *fs)
{
    mFss[std::move(fstype)] = fs;
}

Volume* FileSystemManager::getVolume(const std::string &volume)
{
    return mMounted[volume];
}