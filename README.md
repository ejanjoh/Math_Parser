# Calculate an Mathematical Expression – A Math Parser

This is an implementation of a simple math parser that operate on integers and handle the four basic binary operations ('+','-','/','*') including the use of parenthesis (the unary operator '-' is not part of the parser). However, it can easily be extended to handle other operators and functions. The parser is based on a context-free gramma defined by the following production rules (described in Extended Backus–Naur form (EBNF)):

_**Digit** = "0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9";_  
_**Number** = {Digit};_  
_**Phrase** = "(" Expression ")";_  
_**Term** = Number | Phrase;_  
_**Operator** = "+"|"-"|"*"|"/";_  
_**Expression** = Term [, {Operator, Term}];_  


The parser transform a mathematical string, given on infix notation, to a postfix notation (or reverse polish notation) and calculate the result. It removes potential white characters in the string and then tokenize it to its mathematical tokens or parts. The parser perform a syntax check based on the gramma production rules above and cast an exception if any syntax errors is found. The postfix notation is provided by the Shutting-Yard algorithm. Finally, not part of the parser, the result is calculated.


1. Remove white from the input string
2. Tokenize the input string
3. Check the gramma (syntax)
4. Shutting yard (convert the infix notation to reverse polish notation or postfix notation)
5. Calculate the result


The operators used and its precedence is given by:

Operator | Precedence | Associativity | # arguments
:------: | :--------: | :-----------: | :---------:
"*"      |  2         |     Left      |         2
"/"      |  2         |     Left      |         2
"+"      |  1         |     Left      |         2
"-"      |  1         |     Left      |         2

     
     

***
**Reference:**  
**Shunting-yard algorithm:** https://en.m.wikipedia.org/wiki/Shunting-yard_algorithm  
**Reverse Polish notation:** https://en.m.wikipedia.org/wiki/Reverse_Polish_notation  
**Extended Backus–Naur form:** https://en.m.wikipedia.org/wiki/Extended_Backus-Naur_form  
***

