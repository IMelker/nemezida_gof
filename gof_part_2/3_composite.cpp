// Компоновщик (Composite)

#include <memory>
#include <iostream>
#include <vector>

#define DEFAULT_FILE_SIZE 1024

struct FileSystemObject
{
    virtual ~FileSystemObject() = default;

    virtual int size() = 0;
    virtual void addObject(FileSystemObject *) {};
};

class File : public FileSystemObject
{
  public:
    ~File() = default;

    int size() override {
        return DEFAULT_FILE_SIZE;
    }
};

class Directory : public FileSystemObject
{
  public:
    ~Directory() {
        for (auto *dir: objects) {
            delete dir;
        }
    };

    int size() override {
        int total = 0;
        for (auto fo : objects) {
            total += fo->size();
        }
        return total;
    }

    void addObject(FileSystemObject *fso) override {
        objects.push_back(fso);
    }
  private:
    std::vector<FileSystemObject *> objects;
};

Directory *subdir(int count = 0) {
    auto *dir = new Directory;
    for (int i = 0; i < count; ++i) {
        dir->addObject(new File());
    }
    return dir;
}

int main(int, char *[]) {
    auto root = std::make_unique<Directory>();

    root->addObject(subdir(2));
    root->addObject(subdir());
    root->addObject(new File());
    root->addObject(subdir(4));
    root->addObject(new File());

    std::cout << root->size() << std::endl;
}
