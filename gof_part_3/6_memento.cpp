// Хранитель (Memento)

#include <iostream>

class Memento {
    friend class Ops;

    int value;
  public:
    explicit Memento(int value_) : value(value_) {};
};

class Ops {
    int count = 0;

  public:
    void doSomeMagic() {
        ++count;
    };
    void dump() {
        std::cout << count << std::endl;
    };

    Memento createSnapshot() {
        return Memento{count};
    }
    void restoreSnapshot(const Memento &memento) {
        count = memento.value;
    }
};

int main(int, char *[]) {
    Ops n;
    n.doSomeMagic();

    auto snap = n.createSnapshot();
    
    n.doSomeMagic();
    n.dump();

    n.restoreSnapshot(snap);
    n.dump();

    return 0;
}
