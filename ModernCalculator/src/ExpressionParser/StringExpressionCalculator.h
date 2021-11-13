#pragma once

#include <string>
#include <vector>

namespace poc::expressionCalculator
{
float calculate(const std::string& expression);
std::vector<std::string>
convertExpressionToReversePolishNotation(const std::vector<std::string>& tokens);
} // namespace poc::expressionCalculator
