#include <QApplication>

#include "CalculatorMainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Calculator");

    {
        auto leakedMem = new int(4);
    }

    auto mainWindow = calculator::CalculatorMainWindow();
    mainWindow.show();

    return QApplication::exec();
}