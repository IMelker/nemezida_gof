// Мост (Bridge)

#include <iostream>

struct ClockSignal
{
    virtual const char *now() = 0;
};

class InternetClockSignal : public ClockSignal
{
  public:
    const char *now() override {
        std::cout << "Internet clock" << std::endl;
        return __TIME__;
    }
};

class LocalClockSignal : public ClockSignal
{
  public:
    const char *now() override {
        std::cout << "Local clock" << std::endl;
        return __TIME__;
    }
};

class Clock
{
    ClockSignal *signal;
  protected:
    const char *time;

  public:
    Clock() : signal(nullptr), time(nullptr)  {};

    void setSignal(ClockSignal * signal) {
        this->signal = signal;
    };

    void refresh() {
        if (!this->signal)
            return;

        this->time = this->signal->now();
        display();
    }
    virtual void display() = 0;
};

class DigitalClock : public Clock
{
    void display() {
        std::cout << "Digital: " << this->time << std::endl;
    }
};

class AnalogClock : public Clock
{
    void display() {
        std::cout << "Analog: " << this->time << std::endl;
    }
};

int main(int, char *[]) {
    Clock *clock = new DigitalClock;
    clock->setSignal(new InternetClockSignal);

    clock->refresh();
}
