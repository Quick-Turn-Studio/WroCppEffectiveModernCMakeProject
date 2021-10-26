#pragma once

#include <string>
#include <vector>

#include "ExpressionData.h"

namespace calculator::parsers
{
class IExpressionHistoryParser
{
public:
    virtual ~IExpressionHistoryParser() = default;

    virtual ExpressionData parseContent(const std::string& content) = 0;
    virtual std::string dataToString(const ExpressionData& data) = 0;
};

} // namespace calculator::parsers