// Команда (Command)

#include<iostream>
#include<vector>
#include<string>

class Game
{
  public:
    void create() {
        std::cout << "Create game " << std::endl;
    }
    void open(const std::string &file) {
        std::cout << "Open game from " << file << std::endl;
    }
    void save(const std::string &file) {
        std::cout << "Save game in " << file << std::endl;
    }
    void make_move(const std::string &move) {
        std::cout << "Make move " << move << std::endl;
    }
};

std::string getPlayerInput(const std::string &prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

// Базовый класс
class Command
{
  public:
    virtual ~Command() = default;
    virtual void execute() = 0;
  protected:
    explicit Command(Game *p) : pgame(p) {}
    Game *pgame;
};

class CreateGameCommand : public Command
{
  public:
    explicit CreateGameCommand(Game *p) : Command(p) {}
    void execute() final {
        pgame->create();
    }
};

class OpenGameCommand : public Command
{
  public:
    explicit OpenGameCommand(Game *p) : Command(p) {}
    void execute() final {
        std::string file_name;
        file_name = getPlayerInput("Enter file name:");
        pgame->open(file_name);
    }
};

class SaveGameCommand : public Command
{
  public:
    explicit SaveGameCommand(Game *p) : Command(p) {}
    void execute() final {
        std::string file_name;
        file_name = getPlayerInput("Enter file name:");
        pgame->save(file_name);
    }
};

class MakeMoveCommand : public Command
{
  public:
    explicit MakeMoveCommand(Game *p) : Command(p) {}
    void execute() final {
        // Сохраним игру для возможного последующего отката
        pgame->save("TEMP_FILE");
        std::string move;
        move = getPlayerInput("Enter your move:");
        pgame->make_move(move);
    }
};

class UndoCommand : public Command
{
  public:
    explicit UndoCommand(Game *p) : Command(p) {}
    void execute() final {
        // Восстановим игру из временного файла
        pgame->open("TEMP_FILE");
    }
};

int main() {
    Game game;
    
    // Имитация действий игрока
    std::vector<Command *> replay;
    // Создаем новую игру
    replay.push_back(new CreateGameCommand(&game));
    // Делаем несколько ходов
    replay.push_back(new MakeMoveCommand(&game));
    replay.push_back(new MakeMoveCommand(&game));
    replay.push_back(new MakeMoveCommand(&game));
    // Последний ход отменяем
    replay.push_back(new UndoCommand(&game));
    // Сохраняем игру
    replay.push_back(new SaveGameCommand(&game));
    
    for (auto &move: replay) {
        move->execute();
    }
    
    for (auto *move: replay) {
        delete move;
    }
    
    return 0;
}