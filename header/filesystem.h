#ifndef MIIOS_FILESYSTEM_H
#define MIIOS_FILESYSTEM_H
#include <unordered_map>
#include <vector>
#include <string>

class MOKernel;

struct FileInfo
{
    enum FileType{File,Directory};
    std::string name;
    FileType type;
};

class Volume
{
public:
    virtual std::vector<FileInfo> listDirectory(const std::string &path) = 0;
    // TODO:Read/write methods.
};

class FileSystem
{
public:
    virtual Volume *newVolume(const std::string &disk) = 0;
};

class FileSystemManager
{
public:
    FileSystemManager(MOKernel &knl);
    void registerFileSystem(const std::string &fstype,FileSystem *fs);
    bool mount(const std::string &volume,const std::string &disk,const std::string &fstype);
    Volume *getVolume(const std::string &volume);
private:
    std::unordered_map<std::string,FileSystem*> mFss;
    std::unordered_map<std::string,Volume*> mMounted;
    MOKernel &mKnl;
};

#endif
