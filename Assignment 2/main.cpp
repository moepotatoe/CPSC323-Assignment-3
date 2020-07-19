#include "lexical.h"
#include "lexical.cpp"
#include "parser.h"
#include "parser.cpp"

void getFile(std::ifstream &file);
void scanFile(std::ifstream &file);

int main(int argc, const char** argv) {
    
    std::ifstream testFile;
    getFile(testFile);
    scanFile(testFile);
    return 0;
}

/* Checking whether file exists in local directory */
void getFile(std::ifstream &file) {
    std::string filename;
    std::cout << "Enter filename for lexical analysis: ";
    while(true) {
        std::cin >> filename;
        file.open(filename);
        if(!file) { std::cout << "File cannot be found. Enter valid filename: "; }
        else { break; }
    }
}

void scanFile(std::ifstream &file) {
    std::ofstream userOutput;
    userOutput.open("output.txt");
    int x = 0;
    std::string temp;
    std::vector<std::string> recordList;
   
    std::string lexerOutput = "";
    std::cout << "\nScanning file with words and index numbers...\n";
    userOutput << "Token \t Lexeme\n";
    while (file >> temp) {
        x++;
        recordList = lexer(temp);
        for (int x = 0; x < recordList.size(); x++) {
            std::cout << recordList[x] << "\n";
            userOutput << recordList[x] << "\n"; //output to terminal
            
            parseList.push_back(recordList[x]); //Adds to a bigger global parse list
        }
    }
    // for (int x = 0; x < lexVec.size(); x++)
    // {
    //     std::cout << "Lexers list " << x;
    //     std::cout << "\n" << lexVec[x] << "\n ";
    // }
    // for (int x = 0; x < parseList.size(); x++)
    // {
    //     std::cout << "Parse list " << x;
    //     std::cout << "\n" << parseList[x] << "\n ";
    // }
    std::cout << "\n\n\nWould you like to toggle printing? 1 - Yes 2 - No : ";
    int choice;
    std::cin >> choice;
    do {
    if (choice == 1)
        printSw = true;
    else if (choice == 2) 
        printSw = false;
    else{
        std::cout << "Invalid choice. Try again: ";
        std::cin >> choice; }
    } while (choice != 1 && choice != 2);
    
    Rat20su(lexVec[0]); 
    userOutput.close();
}