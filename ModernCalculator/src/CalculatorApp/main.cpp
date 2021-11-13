#include <iostream>

#include <QApplication>

#include "CalculatorMainWindow.h"

void printHelloToOperatingSystem()
{
    std::cout << "Hello my friend Linux!" << std::endl;
    std::cout << "Hi MacOS!" << std::endl;
    std::cout << "OMG, Windows!" << std::endl;
}

int main(int argc, char** argv)
{
#if CALCULATOR_IS_NICE
    printHelloToOperatingSystem();
#endif

    // or
    if (CALCULATOR_IS_NICE) {
        printHelloToOperatingSystem();
    }

    if (argc > 1) {
        std::string firstArg = argv[1];
        if (firstArg == "--version") {
            std::cout << "Hello!" << std::endl;
            std::cout << "My version is: " << CALCULATOR_VERSION << std::endl;
            std::cout << "My configuration is: " << CALCULATOR_BUILD_TYPE << std::endl;

            return 0;
        }
        else {
            std::cout << "Unknown parameter '" << firstArg << "'" << std::endl;
        }
    }

    QApplication app(argc, argv);
    QApplication::setApplicationName("Calculator");

    {
        auto leakedMem = new int(4);
    }

    auto mainWindow = calculator::CalculatorMainWindow();
    mainWindow.show();

    return QApplication::exec();
}