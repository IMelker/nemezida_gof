// Посетитель (Visitor)

#include <iostream>
#include <vector>

class DrawPrimitive {
  public:
    virtual void saveTo(class Export *) = 0;
};

class Circle : public DrawPrimitive {
  public:
    int radius;

    explicit Circle(int radius_) : radius(radius_) {};

    void saveTo(Export *v) override;
};

class Box : public DrawPrimitive {
  public:
    int w;
    int h;

    Box(int w_, int h_) : w(w_), h(h_) {};

    void saveTo(class Export *) override;
};

class Export {
  public:
    virtual void saveTo(Circle *) = 0;

    virtual void saveTo(Box *) = 0;
};

class JsonExport : public Export {
  public:
    void saveTo(Circle *c) override {
        std::cout << "{type:circle,radius:" << c->radius << "}" << std::endl;
    }

    void saveTo(Box *b) override {
        std::cout << "{type:box,width:" << b->w << ",height:" << b->h << "}" << std::endl;
    }
};

class XmlExport : public Export {
  public:
    void saveTo(Circle *c) override {
        std::cout << "<circle radius=>" << c->radius << "</circle>" << std::endl;
    }

    void saveTo(Box *b) override {
        std::cout << "<box w=" << b->w << " height=" << b->h << "></box>" << std::endl;
    }
};

void Circle::saveTo(Export *v) {
    v->saveTo(this);
}

void Box::saveTo(struct Export *v) {
    v->saveTo(this);
}

int main(int, char *[]) {
    std::vector<DrawPrimitive *> doc = {new Circle{100}, new Box{4, 3}, new Box{16, 9}, new Circle{13}, new Circle{2}};

    JsonExport jsonExporter;
    for (auto obj : doc) {
        obj->saveTo(&jsonExporter);
    }

    std::cout << std::endl;

    XmlExport xml_exporter;
    for (auto obj : doc) {
        obj->saveTo(&xml_exporter);
    }

    return 0;
}
