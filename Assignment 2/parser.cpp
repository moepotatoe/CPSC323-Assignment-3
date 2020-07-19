#include "parser.h"
#include "lexical.h"

int recIndex = 0; //Keeps track of the records
bool printSw = true; //Determines if the rules are printed or not

std::vector<std::string> parseList; //Collection of all records, both lexeme and token 
std::string userLex; //Number of what is currently being used

std::string lexerCall() { //Returns the next lexeme.
    std::string tempRec;
    if (recIndex < lexVec.size())
    {
        if (printSw)
        {
            //std::cout << parseList[recIndex] << "\n";            
        }
        recIndex++;
        tempRec = lexVec[recIndex];
        return tempRec;
    }
}

//R1. <Rat20SU>  ::=   $$  <Opt Declaration List>    <Statement List> $$ 
void Rat20su(std::string lexemeInput) { //Start from here.
    std::cout << "\nPassing in " << parseList[recIndex] << "\n";
    std::cout << "Lexeme passed in: " << lexemeInput << "\n";

    if (lexemeInput == "$$")
    {
        userLex = lexerCall();
        if (printSw) { std::cout << "<Rat20SU>  =>   $$  <Opt Declaration List>    <Statement List> $$ \n";}
        OptDeclarationList(userLex); //Call after incrementing
        //Statement list function here
        if (lexemeInput != "$$") //eof marker?
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
    std::cout << "\nPassing in: " << parseList[recIndex] << "\n";
    std::cout << "Lexeme passed in: " << lexemeInput << "\n";
    if (lexemeInput == "int" || lexemeInput == "bool") //May need to fix these inside of our code, change int and bool to integer and boolean
    {
        if (printSw) {std::cout <<" <Opt Declaration List> => <Declaration List>   |    <Empty> \n";}

        userLex = lexerCall();
        DeclarationList(userLex);
    }
    else
    {
        Empty(userLex);
    }
    
}

//R3. <Declaration List> => <Declaration> <Declaration List Prime>
void DeclarationList(std::string lexemeInput)
{
    std::cout << "\nPassing in: " << parseList[recIndex] << "\n";
    std::cout << "Lexeme passed in: " << lexemeInput << "\n";
    if (printSw) { std::cout << "<Declaration List> => <Declaration> <DeclarationList Prime> \n";}
    Declaration(lexemeInput);
    DeclarationListPrime(lexemeInput);
}

void DeclarationListPrime(std::string lexemeInput)
{
    std::cout << "\nPassing in: " << parseList[recIndex] << "\n";
    std::cout << "Lexeme passed in: " << lexemeInput << "\n";

    if (printSw) { std::cout << "<Declaration List Prime> => <DeclarationList> <DeclarationList Prime> | Empty \n";}
    
    if (lexemeInput == "int" || lexemeInput == "bool")
    {
        userLex = lexerCall();
        Declaration(lexemeInput);
        DeclarationListPrime(lexemeInput);
    }

}

void Declaration(std::string lexemeInput)
{
    std::cout << "\nempty";
}

void Empty(std::string lexemeInput)
{
    std::cout << "\nempty";
}