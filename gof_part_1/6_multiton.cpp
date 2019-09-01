// Пул одиночек (Multiton)

#include <iostream>
#include <map>

enum class Tag { Main, DB, Engine };

class Logger
{
    Tag tag;

public:
    Logger& operator=(const Logger&) = delete;

    static Logger &instance(Tag t) {
        static std::map<Tag, Logger> instance;

        auto it = instance.find(t);
        if (it == instance.end()) {
            std::tie(it, std::ignore) = instance.emplace(std::make_pair(t, Logger(t)));
        }
        return it->second;
    }

    void info(const std::string &message) {
        std::cout << "INFO:\t[" << static_cast<int>(this->tag) << "] " << message << std::endl;
    }

    void warn(const std::string &message) {
        std::cerr << "WARN:\t[" << static_cast<int>(this->tag) << "] " << message << std::endl;
    }

    void error(const std::string &message) {
        std::cerr << "ERR:\t[" << static_cast<int>(this->tag) << "] " << message << std::endl;
    }

private:
    explicit Logger(Tag tag) : tag(tag) {}
};

int main(int, char const **)
{
    Logger::instance(Tag::Main).info("Started");
    Logger::instance(Tag::DB).warn("No DB");
    Logger::instance(Tag::Engine).error("Internal error");
    Logger::instance(Tag::Main).info("Finished");

    return 0;
}
