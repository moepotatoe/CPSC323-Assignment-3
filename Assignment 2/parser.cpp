#include "parser.h"
#include "lexical.h"

int recIndex = 0; //Keeps track of the records
bool printSw = true; //Determines if the rules are printed or not

std::vector<std::string> parseList; //Collection of all records, both lexeme and token 
std::string userLex; //Lex of what is currently being used

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
    
    std::cout << "\nLexeme passed in: " << lexemeInput << "\n";

    if (lexemeInput == "$$")
    {
        std::cout << "Passing in " << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Rat20SU>  =>   $$  <Opt Declaration List>    <Statement List> $$ \n";}
        
        userLex = lexerCall();
        
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
   
    std::cout << "\nLexeme passed in: " << lexemeInput << "\n";
    if (lexemeInput == "integer" || lexemeInput == "boolean") //May need to fix these inside of our code, change int and bool to integer and boolean
    {
        std::cout << "Passing in: " << parseList[recIndex] << "\n";
        if (printSw) {std::cout <<"<Opt Declaration List> => <Declaration List>   |    <Empty> \n";}

        userLex = lexerCall();
        DeclarationList(userLex);
    }
    else{} //Empty do nothing
    
}

//R3. <Declaration List> -> <Declaration> ; <Declaration List Prime>

//FIX, cant get this right?
void DeclarationList(std::string lexemeInput)
{
    std::cout << "\nLexeme passed in: " << lexemeInput << "\n";
    std::cout << "Passing in: " << parseList[recIndex] << "\n";
    
    if (printSw) { std::cout << "<Declaration List> -> <Declaration> ; <Declaration List Prime>\n";}
    Declaration(lexemeInput);
    if (userLex == ";")
    {
        userLex = lexerCall(); //Get new lexeme
        std::cout << userLex;
        DeclarationListPrime(userLex);
    }
    else {
        std::cout << "Declaration List error, expected ;\n";
        system("Pause");
    }
}

//R3a. <Declaration List Prime> -> <Declaration List> | Epsilon
void DeclarationListPrime(std::string lexemeInput)
{
    std::cout << "\nLexeme passed in: " << lexemeInput << "\n";
    
    if (lexemeInput == "int" || lexemeInput == "bool")
    {
        std::cout << "Passing in: " << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Declaration List Prime> -> <Declaration List> \n";}

        DeclarationList(userLex);
    }
    else
    {
        std::cout << "\nPassing in: " << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Declaration List Prime> -> Epsilon \n";}
    }
}
//<Declaration> -> <Qualifier>  <identifier>
void Declaration(std::string lexemeInput)
{
    std::cout << "\nLexeme passed in: " << lexemeInput << "\n";
    std::cout << "Passing in: " << parseList[recIndex] << "\n";

    if (printSw) { std::cout << "<Declaration> -> <Qualifier>  <Identifier>\n";}
    Qualifier(lexemeInput);
    Identifier(lexemeInput); //Might need to store inside a temp variable? lexemeInput might be changing?
}

//<Qualifier> -> integer |  boolean
void Qualifier(std::string lexemeInput)
{
    std::cout << "\nLexeme passed in: " << lexemeInput << "\n";

    if (lexemeInput == "integer")
    {
        std::cout << "Passing in: " << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Qualifier> -> integer\n";} //Change to integer later?
        userLex = lexerCall();
    }
    else if (lexemeInput == "boolean")
    {
        std::cout << "Passing in: " << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Qualifier> -> boolean\n";} //Change to boolean later?
        userLex = lexerCall();
    }
    else
    {
        std::cout << "Error: Qualifier expected.\n";
    }
}

void Identifier(std::string lexemeInput) {
    if (tokenVec[recIndex] == "Identifier")
    {
        if (printSw) { std::cout << "<Identifier> -> identifier\n";}
        userLex = lexerCall();
    }
}

void Empty(std::string lexemeInput) //Maybe get rid of this later on?
{
    std::cout << "\nempty";
}