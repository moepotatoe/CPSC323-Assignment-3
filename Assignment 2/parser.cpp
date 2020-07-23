#include "parser.h"
#include "lexical.h"

int recIndex = 0; //Keeps track of the records
bool printSw = true; //Determines if the rules are printed or not
std::vector<std::string> parseList; //Collection of all records, both lexeme and token 
std::string userLex; //Lex of what is currently being used

std::ofstream pOut;


std::string lexerCall() { //Returns the next lexeme.
    std::string tempRec;
    if (recIndex < lexVec.size())
    {
        recIndex++;
        tempRec = lexVec[recIndex];
        return tempRec;
    }
}

//R1. <Rat20SU>  ::=   $$  <Opt Declaration List>    <Statement List> $$ 
void Rat20su(std::string lexemeInput) { //Start from here.
    pOut.open("parserOutput.txt");
    if (lexemeInput == "$$")
    {
        std::cout << "\n" << parseList[recIndex] << "\n";
        pOut << "\n" << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Rat20SU>  =>   $$  <Opt Declaration List>    <Statement List> $$ \n";
        pOut << "<Rat20SU>  =>   $$  <Opt Declaration List>    <Statement List> $$ \n";}
        
        userLex = lexerCall();
        
        OptDeclarationList(userLex); //Call after incrementing
        StatementList(userLex);

        if (lexemeInput != "$$") //eof marker?
        {
            std::cout << "Error: $$ expected.\n";
            pOut << "Error: $$ expected.\n";
        }
        else;
    }
    else {std::cout << "Error: $$ expected.\n";
    pOut << "Error: $$ expected.\n";}
}

//R2. <Opt Declaration List> ::= <Declaration List>   |    <Empty>
void OptDeclarationList(std::string lexemeInput)
{
    if (lexemeInput == "integer" || lexemeInput == "boolean") //May need to fix these inside of our code, change int and bool to integer and boolean
    {
        std::cout << "\n" << parseList[recIndex] << "\n";
        pOut << "\n" << parseList[recIndex] << "\n";
        if (printSw) {std::cout <<"<Opt Declaration List> => <Declaration List>\n";
        pOut <<"<Opt Declaration List> => <Declaration List>\n";}
        //No lexer call. Not nonterminal.
        DeclarationList(userLex);
    }
    else{if (printSw) {std::cout <<"<Opt Declaration List> => <Empty>\n";
    pOut <<"<Opt Declaration List> => <Empty>\n";}} //Empty do nothing
    
}

//R3. <Declaration List> -> <Declaration> ; <Declaration List Prime>

//FIX, cant get this right?
void DeclarationList(std::string lexemeInput)
{
    std::cout << "\n" << parseList[recIndex] << "\n";
    pOut << parseList[recIndex] << "\n";
    
    if (printSw) { std::cout << "<Declaration List> -> <Declaration> ; <Declaration List Prime>\n";
    pOut << "<Declaration List> -> <Declaration> ; <Declaration List Prime>\n";}
    Declaration(lexemeInput);
    if (userLex == ";")
    {
        userLex = lexerCall(); //Get new lexeme
        std::cout << parseList[recIndex];
        pOut << parseList[recIndex];
        DeclarationListPrime(userLex);
    }
    else {
        std::cout << "Declaration List error, expected ;\n";
        pOut << "Declaration List error, expected ;\n";
        system("Pause");
    }
}

//R3a. <Declaration List Prime> -> <Declaration List> | Epsilon
void DeclarationListPrime(std::string lexemeInput)
{

    //<Declaration List>
    if (lexemeInput == "integer" || lexemeInput == "boolean")
    {
        std::cout <<parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Declaration List Prime> -> <Declaration List> \n";
        pOut << "<Declaration List Prime> -> <Declaration List> \n";}

        DeclarationList(userLex);
    }
    //Epsilon
    else
    {
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Declaration List Prime> -> Epsilon \n";
        pOut << "<Declaration List Prime> -> Epsilon \n";}
    }
}
//<Declaration> -> <Qualifier>  <identifier>
void Declaration(std::string lexemeInput)
{
    std::cout << parseList[recIndex] << "\n";
    pOut << parseList[recIndex] << "\n";

    if (printSw) { std::cout << "<Declaration> -> <Qualifier>  <Identifier>\n";
    pOut << "<Declaration> -> <Qualifier>  <Identifier>\n";}
    Qualifier(lexemeInput);
    if (tokenVec[recIndex] == "Identifier") {
    std::cout << "<Identifier>\n";
    std::cout <<"Identifier detected\n" << parseList[recIndex] << "\n";
    pOut << "<Identifier>\n";
    pOut <<"Identifier detected\n" << parseList[recIndex] << "\n";
    }
    else {
        std::cout << "Error, identifier expected\n";
        pOut << "Error, identifier expected\n";
    }
    userLex = lexerCall();
}

//<Qualifier> -> integer |  boolean
void Qualifier(std::string lexemeInput)
{
    if (lexemeInput == "integer")
    {
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Qualifier> -> integer\n";
        pOut << "<Qualifier> -> integer\n";} //Change to integer later?
        userLex = lexerCall();
        
        ////
        //std::cout << "\nThe userlex is " << userLex << "\n";
        
    }
    else if (lexemeInput == "boolean")
    {
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<Qualifier> -> boolean\n";
        pOut << "<Qualifier> -> boolean\n";} //Change to boolean later?
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
        if (printSw) { std::cout << "<Identifier> -> identifier\n";
        pOut << "<Identifier> -> identifier\n";}
        userLex = lexerCall();
    }
}

//<StatementList> -> <Statement> <Statement List Prime>
void StatementList(std::string lexemeInput) {

    std::cout << parseList[recIndex] << "\n";
    pOut << parseList[recIndex] << "\n";
    if (printSw) { std::cout << "<Statement List> -> <Statement> <Statement List Prime>\n";
    pOut << "<Statement List> -> <Statement> <Statement List Prime>\n";}
    Statement(lexemeInput);
    StatementListPrime(userLex);
}

//<StatementListPrime> -> <StatementList> | Epsilon
void StatementListPrime(std::string lexemeInput) {

    //<StatementList>
    if (lexemeInput == "if" || lexemeInput == "fi" || lexemeInput == "get" ||
    lexemeInput == "put" || lexemeInput == "while" || lexemeInput == "{" || lexemeInput == "}")
    {
        std::cout << "\nLexeme passed in: " << lexemeInput << "\n";
        std::cout << "Passing in: " << parseList[recIndex] << "\n";
        pOut << "\nLexeme passed in: " << lexemeInput << "\n";
        pOut << "Passing in: " << parseList[recIndex] << "\n";
        if (printSw) { std::cout << "<StatementListPrime> -> <StatementList>\n";
        pOut << "<StatementListPrime> -> <StatementList>\n";}
        StatementList(lexemeInput);
    }
    //epsilon
    else { if (printSw) { std::cout << "<Statement List Prime> -> Epsilon\n";
    pOut << "<Statement List Prime> -> Epsilon\n";}  }
}

//<Statement> -> <Compound>  |  <Assign>  |   <If>  |  <Get>   |   <Put>   |  <While> 
void Statement(std::string lexemeInput) {
    std::cout << parseList[recIndex] << "\n";
    pOut << parseList[recIndex] << "\n";
    
    if (lexemeInput == "{")
    {
        if (printSw) { std::cout << "<Statement> -> <Compound>>\n";
        pOut << "<Statement> -> <Compound>>\n";}
        Compound(lexemeInput);
    }
    else if (tokenVec[recIndex] == "Identifier")
    {
        if (printSw) { std::cout << "<Statement> -> <Assign>>\n";
        pOut << "<Statement> -> <Assign>>\n";}
        Assign(lexemeInput);
    }
    else if (lexemeInput == "if")
    {
        if (printSw) { std::cout << "<Statement> -> <if>\n";
        pOut << "<Statement> -> <if>\n";}
        If(lexemeInput);
    }
    else if (lexemeInput == "get")
    {
        if (printSw) { std::cout << "<Statement> -> <Get>\n";
        pOut << "<Statement> -> <Get>\n";}
        Get(lexemeInput);
    }
    else if (lexemeInput == "put")
    {
        if (printSw) { std::cout << "<Statement> -> <Put>\n";
        pOut << "<Statement> -> <Put>\n";}
        Put(lexemeInput);
    }
    else if (lexemeInput == "while")
    {
        if (printSw) { std::cout << "<Statement> -> <While>\n";
        pOut << "<Statement> -> <While>\n";}
        While(lexemeInput);
    }
}



// R8. <Compound> ::=   {  <Statement List>  } 
void Compound(std::string lexemeInput) {
    if (lexemeInput == "{") {
        if (printSw) { std::cout << "<Compound> -> {  <Statement List>  }\n"; 
        pOut << "<Compound> -> {  <Statement List>  }\n";}
    
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        StatementList(userLex);
        if (userLex == "}") {        
            userLex = lexerCall(); 
            std::cout << parseList[recIndex] << "\n";
            pOut << parseList[recIndex] << "\n";}
        else {
            std::cout << "Error: '}' expected\n";
            pOut << "Error: '}' expected\n";
            system("Pause");}
        }
    else {
        std::cout << "Error: '{' expected\n";
        pOut << "Error: '{' expected\n";
        system("Pause");
    }
}

// R9. <Assign> ::=     <Identifier> = <Expression> ;
void Assign(std::string lexemeInput) {

    if (tokenVec[recIndex] == "Identifier"){
        if (printSw) { std::cout << "<Assign> -> <Identifier> = <Expression> ;\n"; 
        pOut << "<Assign> -> <Identifier> = <Expression> ;\n"; }
        //Identifier(lexemeInput);
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        if (userLex == "=") { 
            userLex = lexerCall(); 
            std::cout << parseList[recIndex] << "\n";
            pOut << parseList[recIndex] << "\n";
        }
        else {std::cout << "Error: '=' expected\n";
        pOut << "Error: '=' expected\n";}

        // userLex = lexerCall();

        //Changing...
        Expression(userLex);
        if (userLex == ";") { 
            userLex = lexerCall(); 
            std::cout << parseList[recIndex] << "\n";
            pOut << parseList[recIndex] << "\n";
        }
        else{ std::cout << "Error: ';' expected\n";
        pOut << "Error: ';' expected\n";}
        // userLex = lexerCall();
        }
}


//Fix me
// R10. <If> ::=     if  ( <Condition>  ) <Statement>   fi   |   if  ( <Condition>  ) <Statement>   otherwise  <Statement>  fi 
void If(std::string lexemeInput) {  
    if (lexemeInput == "if")
    {
        userLex = lexerCall();
        if (userLex == "(") { userLex = lexerCall(); }
        else {std::cout << "Error: '(' expected\n";
        pOut << "Error: '(' expected\n";}
        // userLex = lexerCall();
        Condition(userLex);
        if (userLex == ")") { userLex = lexerCall(); }
        else {std::cout << "Error: ')' expected\n";
        pOut << "Error: ')' expected\n";}
        // userLex = lexerCall();
        Statement(userLex);

        //Where the main differences are
        if (userLex == "fi")  {
            if (printSw) { std::cout << "<If> -> if  ( <Condition>  ) <Statement>   fi \n";
            pOut << "<If> -> if  ( <Condition>  ) <Statement>   fi \n";
            userLex = lexerCall(); 
        }
        else {std::cout << "Error: 'fi' expected\n";
        pOut << "Error: 'fi' expected\n";}

        if (userLex == "otherwise")
        {
            userLex = lexerCall();
            Statement(userLex);
            if (userLex == "fi")
            {
                std::cout << "if  ( <Condition>  ) <Statement>   otherwise  <Statement>  fi\n";
                pOut << "if  ( <Condition>  ) <Statement>   otherwise  <Statement>  fi\n";
                userLex = lexerCall();
            }
            else { std::cout << "Error: 'fi' expected";
            pOut << "Error: 'fi' expected";}
        }
        else {std::cout <<"Error: 'otherwise' expected";
        pOut <<"Error: 'otherwise' expected";}
    }
    
    if (lexemeInput == "otherwise") { Statement(lexemeInput); }
    // double check
    if (lexemeInput == "if") { userLex = lexerCall(); }
    else {std::cout << "Error: 'if' keyword expected\n";
    pOut << "Error: 'if' keyword expected\n";}
    // userLex = lexerCall();
    }
}

// R11. <Put> ::=     put ( <identifier> );
void Put(std::string lexemeInput) {
    if (printSw) { std::cout << "<Put> ::=     put ( <identifier> );\n"; }
    if (lexemeInput == "(") { userLex = lexerCall(); }
    else {std::cout << "Error: '(' expected\n";\
    pOut << "Error: '(' expected\n";}
    // userLex = lexerCall();
    Identifier(lexemeInput);
    if (lexemeInput == ")") { userLex = lexerCall(); }
     else {std::cout << "Error: ')' expected\n";\
    pOut << "Error: ')' expected\n";}
    // userLex = lexerCall();
    if (lexemeInput == ";") { userLex = lexerCall(); }
     else {std::cout << "Error: ';' expected\n";\
    pOut << "Error: ';' expected\n";}
    // userLex = lexerCall();
}

// R12. <Get> ::=    get ( <Identifier> );
void Get(std::string lexemeInput) {
    if (printSw) { std::cout << "<Get> ::=     get ( <Identifier> );\n"; }
    if (lexemeInput == "(") { userLex = lexerCall(); }
    else {std::cout << "Error: '(' expected\n";
    pOut << "Error: '(' expected\n";}
    // userLex = lexerCall();
    Identifier(lexemeInput);
    if (lexemeInput == ")") { userLex = lexerCall(); }
    else {std::cout << "Error: ')' expected\n";
    pOut << "Error: ')' expected\n";}
    // userLex = lexerCall();
    if (lexemeInput == ";") { userLex = lexerCall(); }
    else {std::cout << "Error: ';' expected\n";
    pOut << "Error: ';' expected\n";}
    // userLex = lexerCall();
}

// R13. <While> ::=  while ( <Condition>  )  <Statement>  
void While(std::string lexemeInput) {
    if (printSw) { std::cout << "<While> ::=  while ( <Condition>  )  <Statement>\n"; }
    if (lexemeInput == "(") { userLex = lexerCall(); }
    else {std::cout << "Error: '(' expected\n";
    pOut << "Error: '(' expected\n";}
    // userLex = lexerCall();
    Condition(lexemeInput);
    if (lexemeInput == ")") { userLex = lexerCall(); }
    else {std::cout << "Error: ')' expected\n";
    pOut << "Error: ')' expected\n";}
    // userLex = lexerCall();
    Statement(lexemeInput);
    // Error check here? 
    // userLex = lexerCall();
}

// R14. <Condition> ::=     <Expression>  <Relop>   <Expression>
void Condition(std::string lexemeInput) {
    if (printSw) { std::cout << "<Condition> ::=     <Expression>  <Relop>   <Expression>\n";
    pOut << "<Condition> ::=     <Expression>  <Relop>   <Expression>\n"; }
    Expression(lexemeInput);
    Relop(userLex);
    Expression(userLex);
}

// R15. <Relop> ::=        ==     |    >     |   <          
void Relop(std::string lexemeInput) {
    if (lexemeInput == "==") {
        if (printSw) { std::cout << "<Relop> -> ==" << "\n";
        pOut << "<Relop> -> ==" << "\n"; } 
        userLex = lexerCall();       
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
    }
    else if (lexemeInput == ">") {
        if (printSw) { std::cout << "<Relop> -> >" << "\n";
        pOut << "<Relop> -> >" << "\n"; } 
        userLex = lexerCall();       
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
    }  
    else if (lexemeInput == "<") {
        if (printSw) { std::cout << "<Relop> -> <" << "\n"; 
        pOut << "<Relop> -> <" << "\n"; } 
        userLex = lexerCall();    
        std::cout << parseList[recIndex] << "\n";   
        pOut << parseList[recIndex] << "\n";   
    }  
    else {
        std::cout << "Error, expected an operator '==', '>', or '<'\n";
        pOut << "Error, expected an operator '==', '>', or '<'\n";
        system("Pause");
    }
}


//<Expression> -> <Term> <Expression Prime>
void Expression(std::string lexemeInput)
{
    std::cout << parseList[recIndex] << "\n";
    pOut << parseList[recIndex] << "\n";

    if (printSw) { std::cout << "<Expression> -> <Term> <Expression Prime>\n";
    pOut << "<Expression> -> <Term> <Expression Prime>\n";}
    Term(lexemeInput);
    //Having trouble here.
    ExpressionPrime(userLex);

}
//<Expression Prime>-> + <Term> <Expression Prime> | - <Term> <Expression Prime> | Epsilon
void ExpressionPrime(std::string lexemeInput) {
    std::cout << parseList[recIndex] << "\n";
    pOut << parseList[recIndex] << "\n";

    if (lexemeInput == "+")
    {
        if (printSw) {std::cout << "<Expression Prime>-> + <Term> <Expression Prime>\n";
        pOut << "<Expression Prime>-> + <Term> <Expression Prime>\n";}
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        Term(userLex);
        ExpressionPrime(userLex);
    }
    else if (lexemeInput == "-")
    {
        if (printSw) {std::cout << "<Expression Prime> -> - <Term> <Expression Prime>\n";
        pOut << "<Expression Prime> -> - <Term> <Expression Prime>\n";}
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        Term(userLex);
        ExpressionPrime(userLex);
    }
    else {
         if (printSw) {std::cout << "<Expression Prime> -> Epsilon\n";
         pOut << "<Expression Prime> -> Epsilon\n";}
    }
}

//<Term> -> <Factor> <Term Prime>
void Term(std::string lexemeInput) {
    if (printSw) {std::cout << "<Term> -> <Factor> <Term Prime>\n";
    pOut << "<Term> -> <Factor> <Term Prime>\n";}
    Factor(lexemeInput);
    TermPrime(lexemeInput);
}


//<Term Prime> -> * <Factor> <TermPrime> | / <Factor> <Term Prime> | Epsilon
void TermPrime(std::string lexemeInput)
{
    if (lexemeInput == "*")
    {
        if (printSw) {std::cout << "<Term Prime> -> * <Factor> <Term Prime>\n";
        pOut << "<Term Prime> -> * <Factor> <Term Prime>\n";}
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        Factor(userLex);
        TermPrime(userLex);
    }
    else if (lexemeInput == "/")
    {
        if (printSw) {std::cout << "<Term Prime> -> * <Factor> <Term Prime>\n";
        pOut << "<Term Prime> -> * <Factor> <Term Prime>\n";}
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        Factor(userLex);
        TermPrime(userLex);
    }
    else
    {
       if (printSw) {std::cout << "<Term Prime> -> Epsilon\n";
       pOut << "<Term Prime> -> Epsilon\n";}
    }
}


//<Factor> -> -  <Primary>    |    <Primary>
void Factor(std::string lexemeInput) {
    if (lexemeInput == "-")
    {
        if (printSw) {std::cout << "<Factor> -> - <Primary>\n";
        pOut << "<Factor> -> - <Primary>\n";}
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        Primary(userLex);
    }
    else
    {
        if (printSw) {std::cout << "<Factor> -> <Primary>\n";
        pOut << "<Factor> -> <Primary>\n";}
        Primary(userLex);
    }   
}

//<Primary> -> <Identifier>  |  <Integer>  |  ( <Expression> )   |  true   |  false
void Primary(std::string lexemeInput) {

    if (tokenVec[recIndex] == "Identifier")
    {
        if (printSw) {std::cout << "<Primary> -> <Identifier>\n";
        pOut << "<Primary> -> <Identifier>\n";}
        userLex = lexerCall();
        std::cout <<"Identifier\n" << parseList[recIndex] << "\n";
        pOut <<"Identifier\n" << parseList[recIndex] << "\n";
    }
    else if (tokenVec[recIndex] == "Integer")
    {
        if (printSw) {std::cout << "<Primary> -> <Integer>\n";
        pOut << "<Primary> -> <Integer>\n";}
        userLex = lexerCall();
        std::cout <<"Integer detected\n" << parseList[recIndex] << "\n";
        pOut <<"Integer detected\n" << parseList[recIndex] << "\n";
    }
    else if (lexemeInput == "(")
    {
        if (printSw) {std::cout << "<Primary> -> (<Expression>)\n";
        pOut << "<Primary> -> (<Expression>)\n";}
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
        Expression(userLex);
        if (userLex == ")")
        {
            userLex = lexerCall();
            std::cout << parseList[recIndex] << "\n";
            pOut << parseList[recIndex] << "\n";
        }
        else {
            std::cout << "Error, expected a )" << "\n";
            pOut << "Error, expected a )" << "\n";
            system("pause");
        }
    }
    else if (lexemeInput == "true") {
        if (printSw) {std::cout << "<Primary> -> true\n";
        pOut << "<Primary> -> true\n";}
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
    }
    else if (lexemeInput == "false") {
        if (printSw) {std::cout << "<Primary> -> false\n";
        pOut << "<Primary> -> false\n";}
        userLex = lexerCall();
        std::cout << parseList[recIndex] << "\n";
        pOut << parseList[recIndex] << "\n";
    }
    else {
        std::cout <<"Error, expected either identifier, integer, expression, true or false \n";
        pOut <<"Error, expected either identifier, integer, expression, true or false \n";
        system("pause");
    }
}
