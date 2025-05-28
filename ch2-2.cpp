#include <iostream>
#include <memory>
using namespace std;

class User {
public:
    std::string name;
    std::shared_ptr<User> friend_link; // 先用 shared_ptr

    User(const std::string& n) : name(n) {
        std::cout << "User " << name << " created\n";
    }

    ~User() {
        std::cout << "User " << name << " destroyed\n";
    }
};


class UserWeak {
public:
    std::string name;
    std::weak_ptr<UserWeak> friend_link; // 使用 weak_ptr

    UserWeak(const std::string& n) : name(n) {
        std::cout << "UserWeak " << name << " created\n";
    }

    ~UserWeak() {
        std::cout << "UserWeak " << name << " destroyed\n";
    }
};

void test_cycle() {
    auto u1 = std::make_shared<User>("Alice");
    auto u2 = std::make_shared<User>("Bob");

    u1->friend_link = u2;
    u2->friend_link = u1;

    // 兩者離開作用域，但無法釋放，~User() 不會執行！
}

void test_cycle_weak() {
    auto u1 = std::make_shared<UserWeak>("Alice");
    auto u2 = std::make_shared<UserWeak>("Bob");

    u1->friend_link = u2; // 使用 weak_ptr
    u2->friend_link = u1; // 使用 weak_ptr
    // 離開作用域後，~UserWeak() 會執行，因為 weak_ptr 不會增加引用計數
}

int main() {
    cout << "Testing shared_ptr with cycle:\n";
    cout << "--------------------------------\n";
    test_cycle();
    cout << "\nTesting weak_ptr to break cycle:\n";
    cout << "--------------------------------\n";
    test_cycle_weak();
}
