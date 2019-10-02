// Наблюдатель (Observer)

#include <iostream>
#include <vector>

enum class Lang {
    ru, en
};

class Observer {
  public:
    virtual void update(Lang lang) = 0;
};

class Language {
    Lang lang{Lang::ru};
    std::vector<Observer *> subs;
  public:
    void subscribe(Observer *obs) {
        subs.push_back(obs);
    }

    void setLanguage(Lang lang_) {
        lang = lang_;
        notify();
    }

    void notify() {
        for (auto s : subs) {
            s->update(lang);
        }
    }
};

class ReportObserver : public Observer {
  public:
    explicit ReportObserver(Language *lang) {
        lang->subscribe(this);
    }

    void update(Lang lang) override {
        std::cout << "switch report template to lang " << int(lang) << std::endl;
    }
};

class UiObserver : public Observer {
  public:
    explicit UiObserver(Language *lang) {
        lang->subscribe(this);
    }

    void update(Lang lang) override {
        std::cout << "refresh ui for lang " << int(lang) << std::endl;
    }
};

int main(int, char *[]) {
    Language lang;

    ReportObserver rpt(&lang);
    UiObserver ui(&lang);

    lang.setLanguage(Lang::ru);
    lang.setLanguage(Lang::en);

    return 0;
}
