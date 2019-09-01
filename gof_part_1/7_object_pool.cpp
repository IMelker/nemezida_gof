// Объектный пул (Object pool)

#include <exception>
#include <iostream>
#include <vector>

struct PgConnection {
    void doWork() {};
};

class PgConnectionPool
{
private:
    struct PgConnectionBlock {
        PgConnection *connection;
        bool busy;
    };

    std::vector<PgConnectionBlock> m_pool;

public:
    PgConnection *get() {
        for (auto& connectionBlock: m_pool) {
            if (!connectionBlock.busy) {
                connectionBlock.busy = true;
                return connectionBlock.connection;
            }
        }

        m_pool.push_back(PgConnectionBlock{new PgConnection, true});
        return m_pool.back().connection;
    }

    void put(PgConnection *object) {
        for (auto& connectionBlock: m_pool) {
            if (connectionBlock.connection == object) {
                connectionBlock.busy = false;
                break;
            }
        }
    }

    ~PgConnectionPool() {
        for (const auto &i : m_pool) {
            std::cout << i.connection << std::endl;
            delete i.connection;
        }
    }
};

int main(int, char const **) {
    PgConnectionPool pool;

    auto report_conn = pool.get();
    report_conn->doWork();
    pool.put(report_conn);

    auto admin_conn = pool.get();
    admin_conn->doWork();
    pool.put(admin_conn);

    return 0;
}
