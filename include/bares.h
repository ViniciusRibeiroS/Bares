#ifndef BARES_H
#define BARES_H

#include <string>

using value_type = long int;
using symbol = char;

bool is_operator( symbol s );                      							   //Verifica se o elemento da string é um operador matematico
bool is_operand( symbol s ); 												  //Verifica se o elemento da string é um número
bool is_opening_scope( symbol s ); 				  							 //Verifica se o elemento da string é a abertura de um parentese 
bool is_closing_scope( symbol s );				  							//Verifica se o elemento da string é o fechamento de um parentese
bool is_right_association( symbol op ); 		                           // Verifica se a associação 
short get_precedence( symbol op ); 				                          //Configura ordem das operações matemáticas
bool has_higher_or_eq_precedence( symbol op1 , symbol op2 );             //Checa se a posição daquele operador é maior ou menor que o comparado
value_type execute_operator( value_type v1, value_type v2, symbol op ); //Faz a operação matemática para aquele operador
std::string infix_to_postfix( std::string infix ); 					   //Transforma a string de infixa para posfixa
int string_int_euclidean(std::string num); 							  //Transformar uma string em um inteiro usando o teorema de euclides
value_type evaluate_postfix( std::string postfix ); 				 //Transforma a string nas operações matemáticas em busca do resultado esperado

#endif