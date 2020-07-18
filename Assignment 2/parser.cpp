#include "parser.h"
#include "lexical.h"

int recIndex = 0;
bool printSw = true;

std::vector<std::string> parseList;
std::string currentToken;

std::string lexerCall() {
    std::string tempRec;
    if (recIndex < parseList.size())
    {
        if (printSw)
        {
            //std::cout << parseList[recIndex] << "\n";            
        }
        tempRec = parseList[recIndex];
        recIndex++;
        return tempRec;
    }
}

//R1. <Rat20SU>  ::=   $$  <Opt Declaration List>    <Statement List> $$ 
void Rat20su(std::string token) { //Start from here.
    std::cout << token << " is what is passed into rat20su\n";
    if (token == "$$")
    {
        currentToken = lexerCall();
        OptDeclarationList(currentToken);
        //Statement list function here
        if (token != "$$")
        {
            std::cout << "Error: $$ expected.\n";
        }
        else;
    }
    else {std::cout << "Error: $$ expected.\n";}
}

//R2. <Opt Declaration List> ::= <Declaration List>   |    <Empty>

void OptDeclarationList(std::string token)
{
    std::cout << currentToken << "\n";
}