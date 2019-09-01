// Прототип (Prototype)

#include <iostream>
#include <map>

struct Prototype {
    virtual ~Prototype() = default;

    virtual void connection() = 0;
    virtual Prototype *clone() = 0;
};

class TcpConnector : public Prototype
{
    void connection() final {
        std::cout << "TCP connection" << std::endl;
    }

    Prototype *clone() final {
        return new TcpConnector{};
    }
};

class UdpConnector : public Prototype
{
    void connection() final {
        std::cout << "UDP connection" << std::endl;
    }

    Prototype *clone() final {
        return new UdpConnector{};
    }
};

int main(int, char const **)
{
    Prototype *c = new TcpConnector{};

    //

    std::cout << "Primary" << std::endl;
    c->connection();

    Prototype* mirror = c->clone();
    std::cout << "Mirror" << std::endl;
    mirror->connection();

    delete mirror;
    delete c;

    return 0;
}
