// Фасад (Facade)

#include <iostream>

struct VideoControl
{
    void info() {};
    void alert() {};
};

struct Database
{
    void create() {};
    void update() {};
};

struct Printer
{
    void print() {};
};

struct Fiscal
{
    void report() {};
};

class Register
{
    VideoControl vc;
    Database db;
    Printer printer;
    Fiscal f;

  public:
    void saleDoc() {
        db.create();
        vc.info();
        printer.print();
        f.report();
    };

    void retDoc() {
        db.update();
        vc.alert();
        printer.print();
        f.report();
    };
};

int main(int, char *[]) {
    auto r = Register();

    r.saleDoc();
    r.retDoc();
}
