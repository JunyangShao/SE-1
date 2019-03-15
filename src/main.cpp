//
// Creaed by jxq96 on 2019/3/10.
//
#include <iostream>
// unistd.h and getopt.h for parser command line parameters
#include <unistd.h>
#include <getopt.h>
#include <string>
using std::string;
int main(int argc,char* argv[]){
    const char* optstring = "w:c:h:t:n:";
    bool choice = true; // most word or most character, true:word,false:character
    bool head = false;
    bool tail = false;
    // if constraint head character or tail character
    char headChar,tailChar;
    string inputFileName;
}
