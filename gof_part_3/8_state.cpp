// Состояние (State)

#include <iostream>

class Application {
    class CommandHandler *cmdHandler;

  public:
    Application();

    void setCurrent(CommandHandler *h) {
        cmdHandler = h;
    }

    void login();

    void doIt();

    void logout();
};

class CommandHandler {
  public:
    virtual void login(Application *) = 0;
    virtual void doIt(Application *) = 0;
    virtual void logout(Application *) = 0;
};

void Application::login() {
    cmdHandler->login(this);
}

void Application::doIt() {
    cmdHandler->doIt(this);
}

void Application::logout() {
    cmdHandler->logout(this);
}

class LogginedHandler : public CommandHandler {
  public:
    void login(Application *) override {
        std::cout << "already login" << std::endl;
    }
    void doIt(Application *) override {
        std::cout << "success" << std::endl;
    }
    void logout(Application *m) override;
};

class Anonymous : public CommandHandler {
  public:
    void login(Application *m) override {
        std::cout << "work as loggined" << std::endl;
        m->setCurrent(new LogginedHandler());
    }
    void doIt(Application *) override {
        std::cout << "error" << std::endl;
    }
    void logout(Application *) override {
        std::cout << "already logout" << std::endl;
    }
};

void LogginedHandler::logout(Application *m) {
    std::cout << "work as anonymous" << std::endl;
    m->setCurrent(new Anonymous());
}

Application::Application() {
    cmdHandler = new Anonymous();
    std::cout << std::endl;
}

int main(int, char *[]) {
    Application app;

    app.doIt();
    app.logout();
    app.login();
    app.doIt();
    app.login();
    app.logout();

    return 0;
}
