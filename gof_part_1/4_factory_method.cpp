// Фабричный метод (Factory method)

#include <memory>
#include <iostream>

enum class Storage { MySQL, PostgreSQL };

struct IStorage {
    virtual ~IStorage() = default;

    virtual void open() = 0;
    virtual void executeQuery() = 0;
    virtual void close() = 0;
};

class MysqlStorage : public IStorage
{
    void open() final {
        std::cout << "Connect to MySQL" << std::endl;
    }

    void executeQuery() final {
        std::cout << "Fetch MySQL result" << std::endl;
    }

    void close() final {
        std::cout << "Disconnect from MySQL" << std::endl;
    }
};

class PostgresStorage : public IStorage
{
    void open() final {
        std::cout << "Connect to pg" << std::endl;
    }

    void executeQuery() final {
        std::cout << "Fetch pg result" << std::endl;
    }

    void close() final {
        std::cout << "Disconnect from pg" << std::endl;
    }
};

int main(int, char *[]) {
    auto environment = Storage::PostgreSQL;

    std::unique_ptr<IStorage> storage;
    switch (environment) {
    case Storage::MySQL:
        storage = std::make_unique<MysqlStorage>();
        break;
    case Storage::PostgreSQL:
        storage = std::make_unique<PostgresStorage>();
        break;
    }

    //
    storage->open();
    storage->executeQuery();
    storage->close();

    return 0;
}
