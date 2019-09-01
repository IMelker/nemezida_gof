// Заместитель (Proxy)

#include <memory>
#include <iostream>

struct ILogger
{
    virtual ~ILogger() = default;

    virtual void info() = 0;
    virtual void error() = 0;
};

class Logger : public ILogger
{
  public:
    ~Logger() = default;

    void info() override {
        std::cout << "Info" << std::endl;
    }

    void error() override {
        std::cout << "Error" << std::endl;
    }
};

class LevelLogger : public ILogger
{
  public:
    enum Level {
        Debug = 0,
        Warning = 1,
        Error = 2,
        Info = 3
    };

    LevelLogger(Level level, ILogger *logger) : level(level), logger(logger) {};

    void info() override {
        if (level >= Level::Info)
            logger->info();
    }

    void error() override {
        if (level >= Level::Error)
            logger->error();
    }

  private:
    Level level;
    std::unique_ptr<ILogger> logger;
};

int main(int, char *[]) {
    std::unique_ptr<ILogger> logger = std::make_unique<LevelLogger>(LevelLogger::Info, new Logger);

    logger->info();
    logger->error();
}
