#include <iostream>
#include "scanner.h"

using namespace std;

int main(int argc, char** argv)
{
    Scanner scanner("input_data.c");
    // Scanner scanner("scanner.cpp");
    scanner.Init();
    while (!scanner.eof()) {
        scanner.getNextToken();
        scanner.currentToken().dump();
    }
    return 0;
}
