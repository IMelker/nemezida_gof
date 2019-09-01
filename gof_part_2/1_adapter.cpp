// Адаптер (Adapter)

#include <memory>
#include <iostream>

class MysqlClientNative
{
  public:
    void mysqlConnect() {
        std::cout << "MySQL connect" << std::endl;
    }
    void mysqlExecute() {
        std::cout << "MySQL execute" << std::endl;
    }
    void mysqlClose() {
        std::cout << "MySQL close" << std::endl;
    }
};

class PostgresClientNative
{
  public:
    void postgresOpen() {
        std::cout << "PostgresSQL open" << std::endl;
    }
    void postgresQuery() {
        std::cout << "PostgresSQL query" << std::endl;
    }
};

struct IDatabase
{
    virtual ~IDatabase() = default;

    virtual void connect() = 0;
    virtual void executeQuery() = 0;
    virtual void close() = 0;
};

class MysqlDatabase : public IDatabase
{
    MysqlClientNative client;

  public:
    ~MysqlDatabase() = default;

    void connect() override {
        client.mysqlConnect();
    }

    void executeQuery() override {
        client.mysqlExecute();
    }

    void close() override {
        client.mysqlClose();
    }
};

class PostgresDatabase : public IDatabase
{
    PostgresClientNative client;

  public:
    ~PostgresDatabase() = default;

    void connect() override {
        client.postgresOpen();
    }

    void executeQuery() override {
        client.postgresQuery();
    }

    void close() override {
    }
};

int main(int, char *[]) {
    std::unique_ptr<IDatabase> db = std::make_unique<PostgresDatabase>();

    db->connect();
    db->executeQuery();
    db->close();
}
