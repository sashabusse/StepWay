#include "expression_evaluation.h"
#include "exprtk.hpp"

namespace ExprEval
{
    double Evaluate(std::string& expression_string)
    {
        typedef exprtk::symbol_table<double> symbol_table_t;
        typedef exprtk::expression<double>     expression_t;
        typedef exprtk::parser<double>             parser_t;


        symbol_table_t symbol_table;
        symbol_table.add_constants();

        expression_t expression;
        expression.register_symbol_table(symbol_table);

        parser_t parser;
        parser.compile(expression_string, expression);

        return expression.value();
    }
}