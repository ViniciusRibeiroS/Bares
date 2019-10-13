#include <iostream>  // cout, endl
#include <fstream>   // leit
#include <sstream>   //
#include <stack>     // stack
#include <string>    // string
#include <cassert>   // assert
#include <cmath>     // pow
#include <stdexcept> // std::runtime_error
#include <vector>    // std::vector
#include "bares.h"   

using value_type = long int; 
using symbol = char;

///Essa função verifica se o caractere corresponde a um operador.
/*!
 * Comparando um symbol com uma string contendo as operações suportadas e gera um retorno binário.
 */
bool is_operator( symbol s )
{
    return std::string("*^/%+-").find( s ) != std::string::npos;
}

///Essa função verifica se o caractere corresponde a um numero.
/*!
 * Comparando um char com os valores correspontes das operações válidas na tabela ascii e gera um retorno binário.
 */
bool is_operand( symbol s )
{  
    return s >= '0' and s <= '9';   
}

///Essa função verifica se o caractere corresponde a um parentesis abrindo.
/*!
 * Comparando um char com o valor corresponte a um parentesis abrindo na tabela ascii e gera um retorno binário.
 */
bool is_opening_scope( symbol s )
{ 
    return s == '('; 
}

///Essa função verifica se o caractere corresponde a um parentesis fechando.
/*!
 * Comparando um char com o valor corresponte a um parentesis fechando na tabela ascii e gera um retorno binário.
 */
bool is_closing_scope( symbol s )
{ 
    return s == ')'; 
}

///Essa função verifica se o caractere corresponde a o caractere correspondente a operação de potencia.
/*!
 * Comparando um char com o valor corresponte a ^ na tabela ascii e gera um retorno binário.
 */
bool is_right_association( symbol op )
{ 
    return op == '^'; 
}

///Essa função retorna um valor de precedencia de acordo com a prioridade de cada operação.
/*!
 * Comparando um char com os valores correspontes das operações válidas na tabela ascii e um retorno inteiro.
 */
short get_precedence( symbol op )
{
    switch( op )
    {
        case '^' : return 3;
        case '*' :
        case '/' :
        case '%' : return 2;
        case '+' :
        case '-' : return 1;
        case '(' : return 0;
        default  : assert( false );  return -1;
    }
}

///Essa função compara a precedencia dos dois symbols inseridos.
/*!
 * Comparando a precedencia, essa função retorna true se o symbol da esquerda for maior, false se for menor e no caso de igualdade verifica se é simbolo de potencia.
 */
bool has_higher_or_eq_precedence( symbol op1 , symbol op2 )
{
    // pega os valores numericos correspondentes aas precedencias.
    int p_op1 = get_precedence( op1 );
    int p_op2 = get_precedence( op2 );

    if ( p_op1 > p_op2 )
    {
        return true;
    }
    else if ( p_op1 < p_op2 )
    {
        return false;
    }
    else // p_op1 == p_op2 
    {
        // exceção a regra, que acontece com associacao direita-esquerda.
        if ( is_right_association( op1 ) ) return false;
        // regra normal.
        return true;
    }
}

///Essa função realiza as operações de acordo com o symbol inserido.
/*!
 * Através do recebimento de um char, essa função se encarregar de identificar e realizar a operação com os dois numeros recebidos.
 */
value_type execute_operator( value_type v1, value_type v2, symbol op )
{
    switch( op )
    {
        case '^':  return pow( v1,v2 );
        case '*':  return v1*v2;
        case '/':  if ( v2 == 0 ) return 0;
                   return v1/v2;
        case '%':  if ( v2 == 0 ) return 0;
                   return v1%v2;
        case '+': return v1+v2;
        case '-': return v1-v2;
        default: throw std::runtime_error( "undefined operator" );
    }
}

///Essa função converte uma expressão infixa em posfíxa.
/*!
 * Para facilitar o empilhamento essa função traduz a expressão recebida para um formato mais amigável.
 */
std::string infix_to_postfix( std::string infix )
{
    std::string postfix(""); // resultado da conversao.
    std::stack< symbol > s; // pilha de ajuda na conversao.

    // Percorrer a entrada, para processar cada item/token/caractere
    for( auto c : infix )
    {
        //std::cout << "\n>>> Infix: \"" << infix << "\"\n";
        //std::cout << ">>> Processando o \'" << c << "\'\n";
        // Operando vai direto pra saida.
        if( is_operand( c ))
        {
            postfix += c;
        }
        
        else if( is_opening_scope(c) )
            s.push( c ); // '(' entra na pilha de espera em cima de quem estiver por la.
        else if( is_closing_scope(c) )
        {
            // desempilhe ateh achar o escopo de abertura correspondente.
            while( not is_opening_scope( s.top() ) )
            {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // Lembre de descartar o '(' que estah no topo da pilha.
        }

        else if ( is_operator( c ) ) // + - ^ *...
        {
            postfix += ' ';
            // Desempilhar as operaçoes em espera que são iguais ou superiores
            // em prioridade (com excecao da associacao direita-esquerda).
            while( not s.empty() and has_higher_or_eq_precedence( s.top(), c ) ) // s.top() >= c
            {
                postfix += s.top();
                s.pop();
            }

            // A operacao que chegar, sempre tem que esperar.
            s.push( c );
        }
        else // qualquer coisa que não seja o que eu quero. Ex.: espaço em branco.
        {
            // ignoro, não faço nada.
        }
        //std::cout << ">>> Posfix: \"" << postfix << "\"\n";
    }

    // Lembre-se de descarregar as operacoes pendentes da pilha.
    while( not s.empty() )
    {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

///Essa função converte uma string para um valor inteiro.
/*!
 * Através do algoritmo de euclides uma string é convertida para intero e seu valor é retornado.
 */
int string_int_euclidean(std::string num)
{
    int numero = 0;
    int i, j;

    j = 0;
    for(i = num.length()-1; i >= 0; i--)
    {
        numero += (num[i]-'0')*pow(10,j);
        j++;
    }

    return numero;
}

///Essa função retorna o valor correspondente a uma expressão posfíxa.
/*!
 * Realiza as operações respeitando a prioridade através da leitura de uma expressão posfíxa.
 */
value_type evaluate_postfix( std::string postfix )
{
    std::stack < value_type > s;
    std::string numero;
    
    int i;

    for(i = 0; i < (int)postfix.length(); i++)
    {
        if ( is_operand( postfix[i]))
        {   
            while(is_operand( postfix[i]))
            {
             //std::cout << "Achou " << std::endl;
             numero += postfix[i];
             //std::cout <<  "Numero " << numero << std::endl;
             i++;
            }
            
            s.push(string_int_euclidean(numero));
            //std::cout << "Topo da pilha "<< s.top() << std::endl;    
        }
        
        numero.clear();

        //if ( is_operand( postfix[i]) && postfix[i-1] == '-' && )


        if ( is_operator(postfix[i]))
        {
            value_type op2 = s.top(); s.pop();
            value_type op1 = s.top(); s.pop();
            auto result = execute_operator( op1, op2, postfix[i] ); // ( 2, 9, '*' )
            s.push( result );
        }

        //else assert( false );
    }

    return s.top();
}
