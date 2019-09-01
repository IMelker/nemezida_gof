// Декоратор (Decorator)

#include <memory>
#include <iostream>

struct File
{
    virtual ~File() = default;
    virtual void write() = 0;
};

class RawFile : public File
{
  public:
    ~RawFile() = default;

    void write() override {
        std::cout << "Write file" << std::endl;
    }
};

class ZipFile : public File
{
    std::unique_ptr<File> file;
  public:
    explicit ZipFile(File *file) : file(file) {};
    ~ZipFile() = default;

    void write() override {
        std::cout << "Compress as Zip" << std::endl;
        file->write();
    }
};

int main(int, char *[]) {
    std::unique_ptr<File> file = std::make_unique<RawFile>();
    file->write();

    std::unique_ptr<File> zipFile = std::make_unique<ZipFile>(new RawFile);
    zipFile->write();
}
