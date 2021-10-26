/*
 * Copyright (C) Quick Turn Studio GmbH - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <string>
#include <vector>

namespace poc::expressionCalculator
{
float calculate(const std::string& expression);
std::vector<std::string>
convertExpressionToReversePolishNotation(const std::vector<std::string>& tokens);
} // namespace poc::expressionCalculator
