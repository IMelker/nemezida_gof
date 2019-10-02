// Посредник (Mediator)

#include <iostream>
#include <map>
#include <set>
#include <string>

enum class UserRole {
    User, Admin
};

struct User {
    std::string name;
    UserRole role;
};

class Permissions {
    std::map<std::string, UserRole> ops = {{"drop", UserRole::Admin},
                                           {"create", UserRole::Admin},
                                           {"select", UserRole::User}};
  public:
    bool enableFor(const std::string &op, UserRole role) {
        auto i = ops.find(op);
        if (i != std::end(ops)) {
            return i->second == role;
        }
        return false;
    }
};

int main(int, char *[]) {
    Permissions perm;

    auto vasya = User{"Вася", UserRole::User};
    auto petya = User{"Петя", UserRole::Admin};

    std::cout << perm.enableFor("drop", vasya.role) << std::endl;
    std::cout << perm.enableFor("drop", petya.role) << std::endl;

    return 0;
}
