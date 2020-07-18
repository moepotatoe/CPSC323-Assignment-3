#include "lexical.h"

std::vector<std::string> lexer(std::string input) {
    std::string token, lexeme = "";
    std::string result, temp;
    std::vector<std::string> records;
    /* Go through each character */
    for (int x = 0; x < input.size(); x++) {
        /* Store token and lexeme into a result string. Push result string onto a vector of strings called records. Lexer will return records. */
        /* Check if it is a separator. */
        if (bool separatorCheck = isSeparator(input[x])) {
            token = "Separator";
            lexeme = input[x];
            tokenVec.push_back(token);
            lexVec.push_back(lexeme);
            result = "Token: \t" + token + "\tLexeme:\t" + lexeme;
            records.push_back(result);
        }
        /* Check if it is an operator. */
        else if (bool operatorCheck = isOperator(input[x])) {
            token = "Operator";
            lexeme = input[x];
            tokenVec.push_back(token);
            lexVec.push_back(lexeme);
            result = "Token: \t" + token + "\tLexeme:\t" + lexeme;
            records.push_back(result);
        }        
        /* Check if it is an integer. */
        else if (intDFSM(input) == isdigit(input[x])) {
            int y = x;
            std::string tempInt;
            while(intDFSM(input) == isdigit(input[y])) {
                tempInt.push_back(input[y]);
                y++;
            }
            token = "Integer  ";
            lexeme = tempInt;
            tokenVec.push_back(token);
            lexVec.push_back(lexeme);
            result = "Token: \t" + token + "\tLexeme:\t" + lexeme;
            records.push_back(result);
            x = y-1;
        }
        /* Check if it is an identifier or keyword (with one FSM). */
        else if (identifierDFSM(input) == 1 || identifierDFSM(input) == 2) {
            int y = x;
            std::string tempID;
            while(isalpha(input[y]) || input[y] == '_') {
                tempID.push_back(input[y]);
                y++;
            }
            /* If it is a keyword */
            if (identifierDFSM(input) == 2) {
                token = "Keyword ";
                lexeme = tempID;
                tokenVec.push_back(token);
                lexVec.push_back(lexeme);
                result = "Token: \t" + token + "\tLexeme:\t" + lexeme;
                records.push_back(result);
                x = y-1;
            }
            /* If it is a identifier */
            else if (identifierDFSM(input) == 1) {
                token = "Identifier";
                lexeme = tempID;
                tokenVec.push_back(token);
                lexVec.push_back(lexeme);
                result = "Token: \t" + token + "\tLexeme:\t" + lexeme;
                records.push_back(result);
                x = y-1;
            }
        }

    }
    return records;
}

int char_to_col_int(const char input) {
	if (isdigit(input)) { return 1; }
    else { return 2; }
}

int char_to_col_id(const char input) {
	if (isalpha(input)) { return 1; }
    else if (input == '_') { return 2; }        
    else { return 3; }    
}

int intDFSM(const std::string str) {
    int startingState = 1;
    int stateTable[3][2] = {0, 'd', 1, 2, 2, 2};
    int acceptState[1] = { 2 };
    int size = str.size();
    for(int i = 0; i < size; i++) {
        int col = char_to_col_int(str[i]);
        startingState = stateTable[startingState][col];
    }
    if(startingState == acceptState[0]) { return 1; }
    else { return 0; }
}

int identifierDFSM(const std::string str) {
    int startingState = 1;
    int stateTable[6][3] = {0, 'l', '_', 1, 2, 5, 2, 3, 4, 3, 3, 4, 4, 3, 4, 5, 5, 5};
    int acceptState[3] = {2, 3, 4};
    int size = str.size();

    for (int i = 0; i < size; i++){
        if (isOperator(str[i]) || isSeparator(str[i])) {            
            for (int i = 0; i < 2; i++) {
                if (startingState == acceptState[i]) { return 1;}
            }
        }
        int col = char_to_col_id(str[i]);
        startingState = stateTable[startingState][col];
        /* If failure detected */
        if (startingState == 0) { return 0; } 
    }
    bool keywordCheck = isKeyword(str);
    for (int i = 0; i < 3; i++) {
        if (startingState == acceptState[i] && keywordCheck == false) { return 1; }     //If identifier, return 1. 
        else if (startingState == acceptState[i] && keywordCheck == true) { return 2; } //If keyword, return 2.
        }
}

bool isSeparator(char ch) {
    if(ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == '[' || ch == ']') { return true; }
    else { return false; }
}

bool isOperator(char ch) {
    if(ch == '<' || ch == '>' || ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == ':' || ch == '=') { return true; }
    else { return false; }
}

bool isKeyword(std::string st) {
    if(st == "if" || st == "fi" || st == "else" || st == "put" || st == "get" || st == "if" || st == "while" || 
    st == "return" || st == "bool" || st == "true" || st == "false" || st == "int" || st == "double" 
    || st == "float" ||  st == "string" || st == "char" || st == "if" || st == "break" ||st == "otherwise") { return true; }
    else { return false; }
}