#ifndef _LEXICAL_H_
#define _LEXICAL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> lexer(std::string input);
int intDFSM(const std::string str);
int identifierDFSM(std::string str);
int char_to_col_int(const char input);
int char_to_col_id(const char input);
bool isSeparator(char ch);
bool isOperator(char ch);
bool isKeyword(std::string st);


std::vector<std::string> tokenVec;
std::vector<std::string> lexVec;

#endif