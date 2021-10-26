#pragma once

#include <IExpressionHistoryParser.h>

namespace calculator::parsers
{

class JsonStringExpressionHistoryParser : public IExpressionHistoryParser
{
public:
    ~JsonStringExpressionHistoryParser() override = default;
    JsonStringExpressionHistoryParser() = default;

    ExpressionData parseContent(const std::string& content) override;
    std::string dataToString(const ExpressionData& data) override;
};

} // namespace parsers
