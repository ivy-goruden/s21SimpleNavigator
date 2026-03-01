#include "../s21_containers.h"

int main() {

    S21::stack<int> a;

    a.push(1);
    a.pop();
    a.push(2);
    a.pop();
    a.push(3);
    a.pop();
   
    
    int sa = a.size();
    std::cout << sa << "\n";
    for (int i = 0; i < sa; i++) {
        std::cout << "top:" << a.top() << "\n";
        a.pop();
    }
    std::cout << "\n";


    S21::queue<int> b;
    b.push(1);
    b.pop();
    b.push(2);

    int sb = b.size();
    std::cout << sb << "\n";
    for (int i = 0; i < sb; i++) {
        std::cout << "front:" << b.front() << "\n";
        b.pop();
    }
    std::cout << "\n";

    return 0;
}
