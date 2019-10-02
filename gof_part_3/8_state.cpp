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
    void doSomeMagic();
    void logout();
};

class CommandHandler {
  public:
    virtual void login(Application *) = 0;
    virtual void doSomeMagic(Application *) = 0;
    virtual void logout(Application *) = 0;
};

void Application::login() {
    cmdHandler->login(this);
}

void Application::doSomeMagic() {
    cmdHandler->doSomeMagic(this);
}

void Application::logout() {
    cmdHandler->logout(this);
}

class LogginedHandler : public CommandHandler {
  public:
    void login(Application *) override {
        std::cout << "Error: Already login" << std::endl;
    }
    void doSomeMagic(Application *) override {
        std::cout << "Info: Do some magic" << std::endl;
    }
    void logout(Application *m) override;
};

class Anonymous : public CommandHandler {
  public:
    void login(Application *m) override {
        std::cout << "Info: Successful login" << std::endl;
        m->setCurrent(new LogginedHandler());
    }
    void doSomeMagic(Application *) override {
        std::cout << "Error: Need to login" << std::endl;
    }
    void logout(Application *) override {
        std::cout << "Error: Already logout" << std::endl;
    }
};

void LogginedHandler::logout(Application *m) {
    std::cout << "Info: Successful logout" << std::endl;
    m->setCurrent(new Anonymous());
}

Application::Application() {
    cmdHandler = new Anonymous();
    std::cout << std::endl;
}

int main(int, char *[]) {
    Application app;
    
    app.doSomeMagic();
    app.logout();
    app.login();
    app.doSomeMagic();
    app.login();
    app.logout();

    return 0;
}
