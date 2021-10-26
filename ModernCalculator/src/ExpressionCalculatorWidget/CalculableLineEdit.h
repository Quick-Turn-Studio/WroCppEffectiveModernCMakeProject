/*
 * Copyright (C) Quick Turn Studio GmbH - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <QLineEdit>
#include <QRegExpValidator>
#include <QString>

#include <StringExpressionCalculator.h>

namespace calculator::widget
{
class CalculableLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY
                   backgroundColorChanged)
public:
    explicit CalculableLineEdit(QWidget* parent = nullptr);

    void setBackgroundColor(const QString& color);
    QString backgroundColor() const;

    void calculateExpression();
    
private:
    constexpr static auto errorBackground = "* { background-color: rgb(255, 0, 0); }";
    constexpr static auto backgroundStyle = "";

signals:
    void textEdited(float value);
    void backgroundColorChanged(QString);

private:
    void onTextEdited(const QString& text);
    
    QString background;
};

} // namespace poc
