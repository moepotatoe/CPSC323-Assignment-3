#include "parser.h"
#include "lexical.h"

int recIndex = 0; //Keeps track of the records
bool printSw = true; //Determines if the rules are printed or not

std::vector<std::string> parseList; //Collection of all records, both lexeme and token 
std::string currentToken; //Number of what is currently being used

std::string lexerCall() {
    std::string tempRec;
    if (recIndex < lexVec.size())
    {
        if (printSw)
        {
            //std::cout << parseList[recIndex] << "\n";            
        }
        tempRec = lexVec[recIndex];
        recIndex++;
        return tempRec;
    }
}

//R1. <Rat20SU>  ::=   $$  <Opt Declaration List>    <Statement List> $$ 
void Rat20su(std::string lexemeInput) { //Start from here.
    std::cout << "Passing in " << parseList[recIndex] << "\n";
    if (lexemeInput == "$$")
    {
        currentToken = lexerCall();
        
        std::cout << "Current token: " << currentToken << "\n";
        if (printSw) { std::cout << "<Rat20SU>  =>   $$  <Opt Declaration List>    <Statement List> $$ \n";}
        OptDeclarationList(currentToken); //Call after incrementing
        //Statement list function here
        if (lexemeInput != "$$")
        {
            std::cout << "Error: $$ expected.\n";
        }
        else;
    }
    else {std::cout << "Error: $$ expected.\n";}
}

//R2. <Opt Declaration List> ::= <Declaration List>   |    <Empty>
void OptDeclarationList(std::string lexemeInput)
{
    std::cout << parseList[recIndex] << "\n";
    if (printSw) {" <Opt Declaration List> => <Declaration List>   |    <Empty> \n";}
    if (lexemeInput == "int" || lexemeInput == "bool") //May need to fix these inside of our code, change int and bool to integer and boolean
    {
        currentToken = lexerCall();
        //DeclarationList(currentToken);
    }
    else
    {
        
    }
    
}