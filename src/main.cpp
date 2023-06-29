#include "Interface/UserInterface.h"
#include <iostream>
#include <memory>
#include "Logic/Calculator.h"



int main() {

    Calculator calculator;
    UserInterface userInterface(calculator);
    userInterface.run();

    return 0;
}




