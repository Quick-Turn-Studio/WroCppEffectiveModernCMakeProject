/*
 * Copyright (C) Quick Turn Studio GmbH - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "CalculableLineEdit.h"

#include <sstream>
#include <stdexcept>

namespace calculator::widget
{

namespace
{

float toFloat(const QString& text)
{
    auto result = false;
    const auto number = text.toFloat(&result);

    return (result) ? number : std::numeric_limits<decltype(number)>::quiet_NaN();
}

QString toString(float value)
{
    auto stringValue = QLocale{}.toString(value, 'f');
    stringValue.remove(QRegExp("0+$"));  // remove any number of trailing 0's
    stringValue.remove(QRegExp("\\.$")); // if the last character is just a '.' then remove it
    return stringValue;
}

} // namespace

CalculableLineEdit::CalculableLineEdit(QWidget* parent)
  : QLineEdit(parent)
{
    // one or more characters in set of {0-9, +, -, *, \, . , (, )}
    QRegExp rx("[0-9+\\-*\\/.()]+");
    const auto validator = new QRegExpValidator(rx, this);
    setValidator(validator);

    connect(this, &QLineEdit::textEdited, this, &CalculableLineEdit::onTextEdited);
    connect(this, &QLineEdit::editingFinished, this, &CalculableLineEdit::calculateExpression);
}

void CalculableLineEdit::onTextEdited(const QString& text)
{
    const auto value = toFloat(text);
    if (qIsNaN(value)) {
        return;
    }
    emit textEdited(value);
}

void CalculableLineEdit::calculateExpression()
{
    setBackgroundColor(CalculableLineEdit::backgroundStyle);
    const auto text = this->text();
    try {
        const auto value = poc::expressionCalculator::calculate(text.toStdString());
        setText(toString(value));
        emit textEdited(value);
    }
    catch (const std::logic_error& error) {
        setText(text);
        setBackgroundColor(CalculableLineEdit::errorBackground);
        return;
    }
}

void CalculableLineEdit::setBackgroundColor(const QString& color)
{
    background = color;
    setStyleSheet(color);
    emit backgroundColorChanged(color);
}

QString CalculableLineEdit::backgroundColor() const
{
    return background;
}

} // namespace calculator::widget
