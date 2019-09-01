// Одиночка (Singleton)

#include <iostream>

class Logger
{
public:
    Logger(const Logger &root) = delete;
    Logger &operator=(const Logger &) = delete;

    static Logger &instance() {
        static Logger instance;
        return instance;
    }

    void info(const std::string &message) {
        std::cout << "INFO:\t" << message << std::endl;
    }

    void warn(const std::string &message) {
        std::cerr << "WARN:\t" << message << std::endl;
    }

    void error(const std::string &message) {
        std::cerr << "ERR:\t" << message << std::endl;
    }

private:
    Logger() = default;
};

int main(int, char const **)
{
    Logger::instance().info("Started");
    Logger::instance().warn("Program is empty");
    Logger::instance().error("Unexpected end");
    Logger::instance().info("Stoped");

    return 0;
}
