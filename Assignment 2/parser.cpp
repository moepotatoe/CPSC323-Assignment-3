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
        //No lexer call. Not nonterminal.
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
    
    //<Declaration List>
    if (lexemeInput == "integer" || lexemeInput == "boolean")
    {
        std::cout << "Passing in: " << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Declaration List Prime> -> <Declaration List> \n";}

        DeclarationList(userLex);
    }
    //Epsilon
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
    if (tokenVec[recIndex] == "Identifier") {
    std::cout << "<Identifier>\n";
    std::cout <<"Identifier: " << parseList[recIndex] << "\n";
    }
    else {
        std::cout << "Error, identifier expected\n";
    }
    userLex = lexerCall();

    ////
    std::cout <<"\nAfter qualifier, userlex is " << userLex << "\n";//identifier is already used up?
}

//<Qualifier> -> integer |  boolean
void Qualifier(std::string lexemeInput)
{
    std::cout << "Lexeme passed in: " << lexemeInput << "\n";

    if (lexemeInput == "integer")
    {
        std::cout << "Passing in: " << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Qualifier> -> integer\n";} //Change to integer later?
        userLex = lexerCall();
        
        ////
        //std::cout << "\nThe userlex is " << userLex << "\n";
        
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

void Identifier(std::string lexemeInput) { //Maybe need to change this to something else, apparently doesn't need its own function
    if (tokenVec[recIndex] == "Identifier")
    {
        if (printSw) { std::cout << "<Identifier> -> identifier\n";}
        userLex = lexerCall();
    }
}

//<StatementList> -> <Statement> <Statement List Prime>
void StatementList(std::string lexemeInput) {

    std::cout << "\nLexeme passed in: " << lexemeInput << "\n";
    std::cout << "Passing in: " << parseList[recIndex] << "\n";
    if (printSw) { std::cout << "<Statement List> -> <Statement> <Statement List Prime>\n";}
    Statement(lexemeInput);
}

//<StatementListPrime> -> <StatementList> | Epsilon
void StatementListPrime(std::string lexemeInput) {

    //<StatementList>
    if (lexemeInput == "if" || lexemeInput == "fi" || lexemeInput == "get" ||
    lexemeInput == "put" || lexemeInput == "while" || lexemeInput == "{" || lexemeInput == "}")
    {
        std::cout << "\nLexeme passed in: " << lexemeInput << "\n";
        std::cout << "Passing in: " << parseList[recIndex] << "\n";
        Statement(lexemeInput);
    }
    //epsilon
    else {if (printSw) { std::cout << "<Statement List Prime> -> Epsilon\n";}

    }
}

//<Statement> -> <Compound>  |  <Assign>  |   <If>  |  <Get>   |   <Put>   |  <While> 
void Statement(std::string lexemeInput) {

    std::cout << "\nLexeme passed in: " << lexemeInput << "\n";
    std::cout << "Passing in: " << parseList[recIndex] << "\n";

    if (lexemeInput == "{")
    {
        if (printSw) { std::cout << "<Statement> -> <Compound>>\n";}
        Compound(lexemeInput);
    }
    else if (tokenVec[recIndex] == "identifier")
    {
        if (printSw) { std::cout << "<Statement> -> <Assign>>\n";}
        Assign(lexemeInput);
    }
    else if (lexemeInput == "if")
    {
        if (printSw) { std::cout << "<Statement> -> <if>\n";}
        If(lexemeInput);
    }
    else if (lexemeInput == "get")
    {
        if (printSw) { std::cout << "<Statement> -> <Get>\n";}
        Get(lexemeInput);
    }
    else if (lexemeInput == "put")
    {
        if (printSw) { std::cout << "<Statement> -> <Put>\n";}
        Put(lexemeInput);
    }
    else if (lexemeInput == "while")
    {
        if (printSw) { std::cout << "<Statement> -> <While>\n";}
        While(lexemeInput);
    }
}