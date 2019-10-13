#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

#include "../include/parser.h"
#include "../include/bares.h"

std::vector<std::string> get_expr()
{
    std::vector<std::string> expressions;
    std::string str;

    while(std::getline(std::cin, str))
        expressions.push_back(str);

    return expressions;
}

void print_error_msg( const Parser::ResultType & result, std::string str )
{
    std::string error_indicator( str.size()+1, ' ');

    // Have we got a parsing error?
    error_indicator[result.at_col] = '^';
    switch ( result.type )
    {
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            std::cout << "Unexpected end of input at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::ILL_FORMED_INTEGER:
            std::cout << "Ill formed integer at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::MISSING_TERM:
            std::cout << "Missing <term> at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            std::cout << "Extraneous symbol after valid expression found at column (" << result.at_col + 1 << ")!\n";
            break;
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            std::cout << "Integer constant out of range beginning at column (" << result.at_col + 1 << ")!\n";
            break;
        case Parser::ResultType::MISSING_CLOSING_PARENTHESIS:
            std::cout << "Missing closing ) at column (" << result.at_col << ")!\n";
            break;
        default:
            std::cout << "Unhandled error found!\n";
            break;
    }
}


int main()
{
    std::vector <std::string> expressions = get_expr();
    std::string exps; 

    Parser my_parser; // Instancia um parser.
    // Tentar analisar cada expressão da lista.
    for( const auto & expr : expressions )
    {
        // Fazer o parsing desta expressão.
        auto result = my_parser.parse( expr );
        // Preparar cabeçalho da saida.
        // Se deu pau, imprimir a mensagem adequada.
        if ( result.type != Parser::ResultType::OK )
            print_error_msg( result, expr );
        else
        {
          auto postfix = infix_to_postfix( expr );      //Transforma a expressão de infixa para posfixa
          int result = evaluate_postfix( postfix );//Result recebe o resultado daquelas expressões matematicas
          std::cout << result << std::endl;       //Print do Resultado seja em um arquivo ou no terminal
          exps.clear(); 
        }              
    }



    std::cout << "\n>>> Normal exiting...\n";

    return EXIT_SUCCESS;
}
