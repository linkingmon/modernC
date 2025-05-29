#include <iostream>
#include <memory>
using namespace std;


class Resource {
public:
    Resource(string name = "Resource") {
        this->name = name;
        cout << "Resource acquired." << name << endl;
    }
    
    ~Resource() {
        cout << "Resource released." << name << endl;
    }
    string name;
};

int main () {
    std::unique_ptr<Resource> resPtrOutside = std::make_unique<Resource>("Obj1");
    {
    cout << "{" << endl;
    {
    cout << "{" << endl;
    std::unique_ptr<Resource> resPtr = std::make_unique<Resource>("Obj2");
    cout << "}" << endl;
    }
    cout << "}" << endl;
    }
    return 0;
}