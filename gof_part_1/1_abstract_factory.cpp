// Абстрактная фабрика (Abstract factory)

#include <iostream>

enum class Env {
    Cloud, Local
};

// Config
struct IConfig
{
    virtual ~IConfig() = default;

    virtual void read() = 0;
};

class ConsulConfig : public IConfig
{
    void read() final {
        std::cout << "Connect to consul" << std::endl;
    }
};

class LocalConfig : public IConfig
{
    void read() final {
        std::cout << "Open Local file" << std::endl;
    }
};

// Metric
struct IMetric
{
    virtual ~IMetric() = default;

    virtual void send() = 0;
};

struct PrometheusMetric : public IMetric
{
    void send() final {
        std::cout << "Push to prometheus" << std::endl;
    }
};

struct LocalMetric : public IMetric
{
    void send() final {
        std::cout << "Write to log" << std::endl;
    }
};

//
struct EnvironmentFactory {
    virtual ~EnvironmentFactory() = default;

    virtual IConfig *CreateConfig() = 0;
    virtual IMetric *CreateMetric() = 0;
};

class CloudFactory : public EnvironmentFactory
{
    IConfig *CreateConfig() final {
        return new ConsulConfig();
    }

    IMetric *CreateMetric() final {
        return new PrometheusMetric();
    }
};

class LocalFactory : public EnvironmentFactory
{
    IConfig *CreateConfig() final {
        return new LocalConfig();
    }

    IMetric *CreateMetric() final {
        return new LocalMetric();
    }
};

int main(int, char *[]) {
    auto environment = Env::Local;

    EnvironmentFactory *factory;
    switch (environment) {
    case Env::Cloud:
        factory = new CloudFactory();
        break;
    case Env::Local:
        factory = new LocalFactory();
        break;
    default:
        return 1;
    }

    //
    auto config = factory->CreateConfig();
    auto metric = factory->CreateMetric();

    config->read();
    metric->send();

    delete config;
    delete metric;

    return 0;
}
