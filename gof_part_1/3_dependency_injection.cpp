// Внедрение зависимости (Dependency Injection)

#include <memory>
#include <iostream>

struct IStorage {
    virtual ~IStorage() = default;

    virtual void executeQuery() = 0;
};

class Report
{
    std::shared_ptr<IStorage> storage;

public:
    explicit Report(std::shared_ptr<IStorage> storage) : storage(std::move(storage)) {}

    void print() {
        storage->executeQuery();
        std::cout << "Done" << std::endl;
    }
};

class TestStorage : public IStorage
{
    void executeQuery() final  {
        std::cout << "Fetching data" << std::endl;
    }
};

class RealStorage : public IStorage
{
    void executeQuery() final  {
        std::cout << "0 row(s) affected" << std::endl;
    }
};

int main(int, char *[]) {
    auto storage = std::make_shared<TestStorage>();

    Report report(std::move(storage));
    report.print();

    return 0;
}
