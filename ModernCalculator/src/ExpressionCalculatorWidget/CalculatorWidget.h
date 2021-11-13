#pragma once

#include <QWidget>

class QPushButton;

namespace calculator::widget
{

class CalculableLineEdit;

class CALCULATOR_WIDGET_API CalculatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalculatorWidget(QWidget* parent);

private:
    QPushButton* createNumpadButton(const QString& text);

    CalculableLineEdit* calculableLineEdit = nullptr;
};

} // namespace calculator
