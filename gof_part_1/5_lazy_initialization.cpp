// Ленивая инициализация (Lazy initialization)

#include <iostream>

class File
{
    std::string name;

public:
    explicit File(std::string &&name) : name(name) {
        std::cout << "Create " << name << std::endl;
    }
    ~File()  {
        std::cout << "Close " << name << std::endl;
    }
    void write(const std::string &line_) {
        std::cout << "Write " << line_ << " into " << name << std::endl;
    }
};

class FileOnDemand
{
    std::string name;
    File *file;

public:
    explicit FileOnDemand(std::string name) : name(std::move(name)), file(nullptr) {
        std::cout << "Create FileOnDemand for " << this->name << std::endl;
    }
    ~FileOnDemand() {
        delete file;
    }

    File *operator->() {
        if (!file) {
            file = new File(std::move(name));
        }
        return file;
    }
};

int main(int, char *[])
{
    FileOnDemand file("test.txt");

    std::cerr << "FileOnDemand created, but File not" << std::endl;

    size_t n = 2;
    for (size_t i = 0; i < n; ++i) {
        file->write(std::to_string(i));
    }

    return 0;
}
