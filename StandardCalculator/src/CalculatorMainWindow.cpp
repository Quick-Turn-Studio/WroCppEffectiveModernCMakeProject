//
// Created by grabusrqts on 23.10.2021.
//

#include "CalculatorMainWindow.h"

#include "CalculatorWidget.h"

namespace calculator
{

CalculatorMainWindow::CalculatorMainWindow()
  : QMainWindow(nullptr)
{
    setCentralWidget(new widget::CalculatorWidget(this));
}

} // namespace calculator