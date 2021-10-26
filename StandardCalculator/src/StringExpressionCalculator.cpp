/*
 * Copyright (C) Quick Turn Studio GmbH - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "StringExpressionCalculator.h"

#include <sstream>
#include <stack>
#include <unordered_map>

#include <queue>

namespace poc::expressionCalculator
{

enum class Assiociative
{
    Left,
    Right
};

enum class Precedence
{
    Low,
    High
};

struct Operator
{
    Precedence precedence;
    Assiociative assiociative;
};

const std::unordered_map<std::string, Operator> operators{
    {"+", Operator{Precedence::Low, Assiociative::Left}},
    {"-", Operator{Precedence::Low, Assiociative::Left}},
    {"*", Operator{Precedence::High, Assiociative::Left}},
    {"/", Operator{Precedence::High, Assiociative::Left}}};

bool isOperator(const std::string& token)
{
    return operators.find(token) != operators.end();
}

bool isParenthesis(const std::string& token)
{
    return token == "(" || token == ")";
}

bool cmpPrecedence(const std::string& token, Precedence precedence)
{
    if (operators.find(token) == operators.end()) {
        throw std::logic_error{"Unknown operator"};
    }
    return operators.at(token).precedence == precedence;
}

bool isAcceptableCharacter(const std::string& text)
{
    const std::string acceptableCharacters{"0123456789.-+*/()"};

    return text.find_first_not_of(acceptableCharacters) == std::string::npos;
}

bool isAssociative(const std::string& token, Assiociative assiociative)
{
    if (!isOperator(token)) {
        throw;
    }
    return operators.at(token).assiociative == assiociative;
}

void readExpInParenthesis(std::stack<std::string>& stack, std::queue<std::string>& out)
{
    while (!stack.empty() && stack.top() != "(") {
        out.push(stack.top());
        stack.pop();
    }
    if (stack.empty()) {
        throw std::logic_error{"missing parenthesis"};
    }
    stack.pop();
}

void moveToQueueFromStack(std::stack<std::string>& stack, std::queue<std::string>& out)
{
    while (!stack.empty()) {
        out.push(stack.top());
        stack.pop();
    }
}

std::vector<std::string> toVector(std::queue<std::string>& out)
{
    std::vector<std::string> result;
    while (!out.empty()) {
        result.push_back(out.front());
        out.pop();
    }
    return result;
}

std::vector<std::string> getTokens(const std::string& expression)
{
    std::vector<std::string> tokens;
    std::string str;

    for (const auto& character : expression) {
        const std::string token{character};

        if (isOperator(token) || isParenthesis(token)) {
            if (!str.empty()) {
                tokens.push_back(str);
            }
            str = "";
            tokens.push_back(token);
        }
        else if (!token.empty() && token != " ") {
            str.append(token);
        }
        else if (!str.empty()) {
            tokens.push_back(str);
            str = "";
        }
    }
    if (!str.empty()) {
        tokens.push_back(str);
    }

    return tokens;
}

std::vector<std::string>
convertExpressionToReversePolishNotation(const std::vector<std::string>& tokens)
{
    // https://www.dcode.fr/reverse-polish-notation
    // https://www.technical-recipes.com/2011/a-mathematical-expression-parser-in-java-and-cpp/
    std::queue<std::string> out;
    std::stack<std::string> stack;
    for (const auto& token : tokens) {
        if (!isAcceptableCharacter(token)) {
            throw std::logic_error{"Not acceptable character"};
        }
        if (isOperator(token)) {
            while (!stack.empty() && isOperator(stack.top())) {
                if (isAssociative(token, Assiociative::Left)
                    && cmpPrecedence(token, Precedence::Low)) {
                    out.push(stack.top());
                    stack.pop();
                    continue;
                }
                break;
            }
            stack.push(token);
        }
        else if (token == "(") {
            stack.push(token);
        }
        else if (token == ")") {
            readExpInParenthesis(stack, out);
        }
        else {
            out.push(token);
        }
    }
    moveToQueueFromStack(stack, out);

    return toVector(out);
}

float calculateTwoComponentExpression(float a, float b, const std::string& operatorToken)
{
    if ("+" == operatorToken) {
        return a + b;
    }
    if ("-" == operatorToken) {
        return a - b;
    }
    if ("*" == operatorToken) {
        return a * b;
    }
    return a / b;
}

std::stack<std::string> processTokens(const std::vector<std::string>& tokens)
{
    std::stack<std::string> stack;
    for (const auto& token : tokens) {

        if (!isOperator(token)) {
            stack.push(token);
        }
        else {
            auto result = 0.0F;
            const auto val2 = stack.top();
            stack.pop();
            const auto f2 = std::stof(val2);
            if (!stack.empty()) {
                const auto val = stack.top();
                stack.pop();
                const auto f1 = std::stof(val);

                result = calculateTwoComponentExpression(f1, f2, token);
            }
            else {
                if (token == "-") {
                    result = f2 * -1.0F;
                }
                else if (isOperator(token)) {
                    throw std::logic_error{"Expression is not correct"};
                }
                else {
                    result = f2;
                }
            }
            stack.push(std::to_string(result));
        }
    }
    return stack;
}

float calculate(const std::string& expression)
{
    const auto expressionTokens = getTokens(expression);
    const auto tokens = convertExpressionToReversePolishNotation(expressionTokens);

    if (tokens.size() == 2 && tokens[1] == "-" && expressionTokens.size() == 2
        && expressionTokens[1] == "-") {
        throw std::logic_error{"Unknown expression"};
    }

    const auto stack = processTokens(tokens);
    if (stack.empty()) {
        throw std::logic_error{"Empty expression"};
    }
    return std::stof(stack.top());
}

} // namespace poc::expressionCalculator
