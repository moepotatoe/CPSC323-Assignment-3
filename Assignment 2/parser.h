#define PARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Rat20su (std::string token);
void OptDeclarationList(std::string token);
void DeclarationList(std::string token);
void DeclarationListPrime(std::string lexemeInput);
void Declaration(std::string lexemeInput);
void Qualifier(std::string lexemeInput);
void Identifier(std::string lexemeInput);
void StatementList(std::string lexemeInput);
void StatementListPrime(std::string lexemeInput);
void Statement(std::string lexemeInput);
void Compound(std::string lexemeInput);
void Empty(std::string lexemeInput);
void Assign(std::string lexemeInput);
void If(std::string lexemeInput);
void Put(std::string lexemeInput);
void Get(std::string lexemeInput);
void While(std::string lexemeInput);
void Condition(std::string lexemeInput);
void Relop(std::string lexemeInput);

/*Rat20SU rewrite

R1. <Rat20SU>  ::=   $$  <Opt Declaration List>    <Statement List> $$ 
R2. <Opt Declaration List> ::= <Declaration List>   |    <Empty>
R3. <Declaration List>  := <Declaration> ;     |      <Declaration> ; <Declaration List> ===== BACKTRACKING ====
R4. <Declaration> ::=   <Qualifier >  <identifier>   
R5: <Qualifier> ::=  integer |  boolean                
R6. <Statement List> ::=   <Statement>   | <Statement> <Statement List> ===== BACKTRACKING ====
R7. <Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Get>   |   <Put>   |  <While> 
R8. <Compound> ::=   {  <Statement List>  } 
R9. <Assign> ::=     <Identifier> = <Expression> ;
R10. <If> ::=     if  ( <Condition>  ) <Statement>   fi   |   
                          if  ( <Condition>  ) <Statement>   otherwise  <Statement>  fi 
R11. <Put> ::=     put ( <identifier> );
R12. <Get> ::=    get ( <Identifier> );
R13. <While> ::=  while ( <Condition>  )  <Statement>  
R14. <Condition> ::=     <Expression>  <Relop>   <Expression>
R15. <Relop> ::=        ==     |    >     |   <          
R16. <Expression>  ::=    <Expression> + <Term>    | <Expression>  - <Term>    |    <Term> ===== LEFT RECURSION ====
R17. <Term>    ::=       <Term>  *  <Factor>     |   <Term>  /  <Factor>     |     <Factor> ===== LEFT RECURSION ====
R18. <Factor> ::=      -  <Primary>    |    <Primary>
R19. <Primary> ::=      <Identifier>  |  <Integer>  |  ( <Expression> )   |  true   |  false                        
R20. <Empty>   ::= epsilon
*/

//R1. <Rat20SU>  ::=   $$  <Opt Declaration List>    <Statement List> $$ 




//R3. <Declaration List> -> <Declaration> ; <Declaration List Prime>
//<Declaration List Prime> -> <Declaration List> | Epsilon