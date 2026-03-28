#include "frontend/type_checker.hh"
#include <iostream>
int main() {
    std::cout << "CHECKER_NS: " << typeid(LM::Frontend::TypeChecker).name() << std::endl;
    return 0;
}
