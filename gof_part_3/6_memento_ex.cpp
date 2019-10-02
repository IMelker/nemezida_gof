// Хранитель (Memento)

#include <iostream>
#include <vector>

class Number;

class Memento
{
    friend class Number;
  public:
    explicit Memento(int val) {
        state = val;
    }
    
  private:
    int state;
};

class Number
{
  public:
    explicit Number(int value) {
        this->value = value;
    }
    
    void dubble() {
        value = 2 * value;
    }
    
    void half() {
        value = value / 2;
    }
    
    int getValue() {
        return value;
    }
    
    Memento *createMemento() {
        return new Memento(value);
    }
    
    void reinstateMemento(Memento *mem) {
        value = mem->state;
    }
  private:
    int value;
};

class Command
{
  public:
    typedef void(Number::*Action)();
    Command(Number *receiver, Action action) : receiver(receiver), action(action) {
    }
    virtual void execute() {
        mementoList[numCommands] = receiver->createMemento();
        commandList[numCommands] = this;
        if (numCommands > highWater)
            highWater = numCommands;
        numCommands++;
        (receiver->* action)();
    }
    static void undo() {
        if (numCommands == 0) {
            std::cout << "*** Attempt to run off the end!! ***" << std::endl;
            return;
        }
        commandList[numCommands - 1]->receiver->reinstateMemento(mementoList[numCommands - 1]);
        numCommands--;
    }
    void static redo() {
        if (numCommands > highWater) {
            std::cout << "*** Attempt to run off the end!! ***" << std::endl;
            return;
        }
        (commandList[numCommands]->receiver->*(commandList[numCommands]->action))();
        numCommands++;
    }
  protected:
    Number *receiver;
    Action action;
    static Command *commandList[20];
    static Memento *mementoList[20];
    static int numCommands;
    static int highWater;
};

Command *Command::commandList[];
Memento *Command::mementoList[];
int Command::numCommands = 0;
int Command::highWater = 0;

int main() {
    int i;
    std::cout << "Integer: ";
    std::cin >> i;
    auto *object = new Number(i);
    
    std::vector<Command *> commands = {new Command(object, &Number::dubble), new Command(object, &Number::half)};

    std::cout << "Double[0], Half[1], Undo[2], Redo[3], Exit[4]: ";
    while (std::cin >> i) {
        if (i == 2)
            Command::undo();
        else if (i == 3)
            Command::redo();
        else if (i >= 0 && i  < 2)
            commands[i]->execute();
        else
            break;
        
        std::cout << "   " << object->getValue() << std::endl;
        std::cout << "Double[0], Half[1], Undo[2], Redo[3], Exit[4]: ";
    }
}