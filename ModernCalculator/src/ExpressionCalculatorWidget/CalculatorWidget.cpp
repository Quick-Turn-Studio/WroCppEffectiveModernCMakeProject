#include "CalculatorWidget.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>

#include "CalculableLineEdit.h"

namespace calculator::widget
{

CalculatorWidget::CalculatorWidget(QWidget* parent)
  : QWidget(parent)
  , calculableLineEdit(new CalculableLineEdit(this))
{
    auto numpadLayout = new QGridLayout;
    numpadLayout->addWidget(createNumpadButton("1"), 1, 0);
    numpadLayout->addWidget(createNumpadButton("2"), 1, 1);
    numpadLayout->addWidget(createNumpadButton("3"), 1, 2);
    numpadLayout->addWidget(createNumpadButton("4"), 2, 0);
    numpadLayout->addWidget(createNumpadButton("5"), 2, 1);
    numpadLayout->addWidget(createNumpadButton("6"), 2, 2);
    numpadLayout->addWidget(createNumpadButton("7"), 3, 0);
    numpadLayout->addWidget(createNumpadButton("8"), 3, 1);
    numpadLayout->addWidget(createNumpadButton("9"), 3, 2);
    numpadLayout->addWidget(createNumpadButton("0"), 4, 0, 2, 1, Qt::AlignCenter);
    numpadLayout->addWidget(createNumpadButton(","), 4, 2);

    numpadLayout->addWidget(createNumpadButton("+"), 0, 0);
    numpadLayout->addWidget(createNumpadButton("-"), 0, 1);
    numpadLayout->addWidget(createNumpadButton("*"), 0, 2);
    numpadLayout->addWidget(createNumpadButton("/"), 0, 3);

    auto calculateButton = new QPushButton("=");
    connect(calculateButton, &QPushButton::clicked, [=] {
        calculableLineEdit->calculateExpression();
    });

    numpadLayout->addWidget(calculateButton, 1, 3, 4, 1, Qt::AlignCenter);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(calculableLineEdit);
    mainLayout->addLayout(numpadLayout, 1);

    setLayout(mainLayout);
}

QPushButton* CalculatorWidget::createNumpadButton(const QString& text)
{
    auto button = new QPushButton(text);

    connect(button, &QPushButton::clicked, [=] {
        calculableLineEdit->setText(calculableLineEdit->text() + button->text());
    });

    return button;
}

} // namespace calculator::widget