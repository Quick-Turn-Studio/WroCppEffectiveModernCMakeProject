/*
 * Copyright (C) Quick Turn Studio GmbH - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <catch2/catch.hpp>

#include <StringExpressionCalculator.h>

using namespace std;
using namespace poc::expressionCalculator;
namespace poc::test
{
SCENARIO("Reverse Polish Notation")
{
    SECTION(" 1+2")
    {
        const vector<string> input{"1", "+", "2"};
        const std::vector<std::string> res{"1", "2", "+"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION(" 2+1")
    {
        const vector<string> input{"2", "+", "1"};
        const std::vector<std::string> res{"2", "1", "+"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION(" 1*2")
    {
        const vector<string> input{"1", "*", "2"};
        const std::vector<std::string> res{"1", "2", "*"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION(" 2-1")
    {
        const vector<string> input{{{"2"}, {"-"}, "1"}};
        const std::vector<std::string> res{{"2"}, {"1"}, "-"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION(" -2+1")
    {
        const vector<string> input{"-", "2", "+", "1"};
        const std::vector<std::string> res{"2", "-", "1", "+"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION(" 2/1")
    {
        const vector<string> input{"2", "/", "1"};
        const std::vector<std::string> res{
            "2",
            "1",
            "/",
        };
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION(" -2+1*2")
    {
        const vector<string> input{"-", "2", "+", "1", "*", "2"};
        const std::vector<std::string> res{"2", "-", "1", "2", "*", "+"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION(" (-2+1)*2")
    {
        const vector<string> input{"(", "-", "2", "+", "1", ")", "*", "2"};
        const std::vector<std::string> res{"2", "-", "1", "+", "2", "*"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION("(-2.5+1)*2")
    {
        const vector<string> input{"(", "-", "2.5", "+", "1", ")", "*", "2"};
        const std::vector<std::string> res{"2.5", "-", "1", "+", "2", "*"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }
    SECTION("-2.5+1)*2")
    {
        const vector<string> input{"-", "2.5", "+", "1", ")", "*", "2"};
        REQUIRE_THROWS_WITH(convertExpressionToReversePolishNotation(input), "missing parenthesis");
    }

    SECTION("(-2.5+1.1)*2.2")
    {
        const vector<string> input{"(", "-", "2.5", "+", "1.1", ")", "*", "2.2"};
        const std::vector<std::string> res{"2.5", "-", "1.1", "+", "2.2", "*"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }

    SECTION("-2.5+1.1*2.2")
    {
        const vector<string> input{"-", "2.5", "+", "1.1", "*", "2.2"};
        const std::vector<std::string> res{"2.5", "-", "1.1", "2.2", "*", "+"};
        REQUIRE(convertExpressionToReversePolishNotation(input) == res);
    }
}

TEST_CASE("Calculate")
{

    SECTION(" 1+2")
    {
        REQUIRE(calculate("1+2") == 3);
    }
    SECTION(" 2+1")
    {
        REQUIRE(calculate("2+1") == 3);
    }

    SECTION(" 1*2")
    {
        REQUIRE(calculate("1*2") == 2);
    }

    SECTION(" 2-1")
    {
        REQUIRE(calculate("2-1") == 1);
    }

    SECTION(" -2+1")
    {
        REQUIRE(calculate("-2+1") == -1);
    }

    SECTION(" 2/1")
    {
        REQUIRE(calculate("2/1") == 2);
    }

    SECTION(" 1/2")
    {
        REQUIRE(calculate("1/2") == 0.5F);
    }

    SECTION(" -2+1*2")
    {
        REQUIRE(calculate("-2+1*2") == 0.0F);
    }

    SECTION(" (-2+1)*2")
    {
        REQUIRE(calculate("(-2+1)*2") == -2.0F);
    }

    SECTION("(-2.5+1)*2")
    {
        REQUIRE(calculate("(-2.5+1)*2") == -3.0F);
    }

    SECTION("(-2.5+1.1)*2.2")
    {
        REQUIRE(calculate("(-2.5+1.1)*2.2") == -3.08F);
    }

    SECTION("-2.5+1.1*2.2")
    {
        REQUIRE(calculate("-2.5+1.1*2.2") == Approx(-0.08F));
    }

    SECTION("100/3 + 10 * 2")
    {
        REQUIRE(calculate("100/3 + 10 * 2") == Approx(53.3333F));
    }

    SECTION("255/3 + 2 * 1/3 + 1024/2")
    {
        REQUIRE(calculate("255/3 + 2 * 1/3 + 1024/2") == Approx(597.6666F));
    }

    SECTION("255/")
    {
        REQUIRE_THROWS(calculate("255/"));
    }

    SECTION("255*")
    {
        REQUIRE_THROWS(calculate("255*"));
    }

    SECTION("255+")
    {
        REQUIRE_THROWS(calculate("255+"));
    }

    SECTION("*255")
    {
        REQUIRE_THROWS(calculate("*255"));
    }

    SECTION("*255+")
    {
        REQUIRE_THROWS(calculate("*255+"));
    }

    SECTION("40*2.5")
    {
        REQUIRE(calculate("40*2.5") == Approx(100.0F));
    }

    SECTION("Illegal marks")
    {
        REQUIRE_THROWS(calculate("?"));
        REQUIRE_THROWS(calculate("m"));
        REQUIRE_THROWS(calculate("a"));
        REQUIRE_THROWS(calculate("x"));
        REQUIRE_THROWS(calculate("z"));
        REQUIRE_THROWS(calculate("c"));
        REQUIRE_THROWS(calculate("<"));
        REQUIRE_THROWS(calculate(">"));
        REQUIRE_THROWS(calculate("@"));
        REQUIRE_THROWS(calculate("34f+4"));
    }
}

TEST_CASE("Empty string")
{
    REQUIRE_THROWS(calculate(" "));
    REQUIRE_THROWS(calculate(""));
}

TEST_CASE(" -20")
{
    REQUIRE(calculate("-20") == Approx(-20.0F));
}

TEST_CASE("255-")
{
    REQUIRE_THROWS_WITH(calculate("255-"), "Unknown expression");
}

TEST_CASE("5853.3")
{
    REQUIRE(calculate("5853.3") == Approx(5853.3F));
}

TEST_CASE("Wrong operator")
{
    REQUIRE_THROWS(calculate("2%5"));
}

} // namespace poc::test
