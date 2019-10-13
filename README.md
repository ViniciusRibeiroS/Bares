# BARES

Este programa tem com objetivo retornar o resultado de expressões matemáticas válidas ou o erro que as torna inválidas.

## Compilação
Para gerar o executável utilize o seguinte comando:

> $ g++ -Wall -std=c++11 src/driver_parser.cpp src/sbares.cpp src/parser.cpp -I include/ -o a

## Uso

Para utilizar o BARES é necessário ter um arquivo de texto, referencia-lo na execução juntamente com o arquivo onde serão geradas as saídas na pasta onde o executável foi gerado.

> $ ./bares < entrada.txt > saida.txt

### Exemplo de entrada e saída

Entrada:

	3 + 5
	7 * 3
	5 * (3 + 2)

Saída:

	8
	21
	25

## Parseamento e Tokenização

Um processo muito importante para resolver as expressões é o "parseamento", nele é feita a validação da expressão, verificando se as operações são válidas, seguindo a seguinte gramática: 

	<expr> := <term>,{ ("+"|"-"|"*"|"/"|"%"|"^"),<term> };
	<term> := "(",<expr>,")" | <integer>;
	<integer> := "0" | {["-"]},<natural_number>;
	<natural_number> := <digit_excl_zero>,{<digit>};
	<digit_excl_zero> := "1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9";
	<digit> := "0"| <digit_excl_zero>;

Depois de validada de acordo com a gramática a expressão é tokenizada, de forma que os elementos que a compoẽ são separados e classificados. Ex:
	
	3 + 2 * 5
	<"3", OPERANDO>, <"+", OPERADOR>, <"2", OPERANDO>, <"*", OPERADOR>, <"5", OPERANDO>																

## Infixo e Posfixo

De acordo com as regras matemáticas alguns operadores tem maior prioridade em cima de outros e isso quebra a linearidade na hora de resolver a expressão. Para facilitar a leitura e resulução da equação o formato posfixo foi adotado, tornando possível resolver a equação de forma linear.

### Exemplo de conversão infixo-posfixo

	Infixo:                     Posfixo:
	A + B 						AB+
	A + B − C 					AB + C−
	A + B ∗ C − D 				ABC ∗ +D−
	(A + B) ∗ (C − D) 			AB + CD − ∗

## Limitações

O nosso bares não reconhece menos unário, por isso o sinal negativo só pode ser usado como operador.

## Componentes

André Luiz Cordeiro Silva Filho - Turma LP02
Vinícius Ribeiro da Silva       - Turma LP01 