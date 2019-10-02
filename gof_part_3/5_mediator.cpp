// Посредник (Mediator)

#include <iostream>
#include <map>
#include <set>
#include <string>

enum class Role {
    User, Admin
};

struct User {
    std::string name;
    Role role;
};

class Perm {
    std::map<std::string, Role> ops = {{"drop", Role::Admin}, {"create", Role::Admin}, {"select", Role::User}};

  public:
    bool enableFor(const std::string &op, Role role) {
        auto i = ops.find(op);
        if (i != std::end(ops)) {
            return i->second == role;
        }
        return false;
    }
};

int main(int, char *[]) {
    Perm perm;

    auto v = User{"вася", Role::User};
    auto p = User{"петя", Role::Admin};

    std::cout << perm.enableFor("drop", v.role) << std::endl;
    std::cout << perm.enableFor("drop", p.role) << std::endl;

    return 0;
}
