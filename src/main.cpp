//
// Creaed by jxq96 on 2019/3/10.
//
#include <iostream>
// unistd.h and getopt.h for parser command line parameters
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <string.h>
using std::string;
using std::cout;
using std::endl;
int main(int argc,char* argv[]){
    const char* optstring = "wch:t:n:";
    bool choice = true; // most word or most character, true:word,false:character
    bool head = false;
    bool tail = false;
    bool fixedlength = false;
    bool conflictflag = false; // is -c and -w both used in the parameter
    // if constraint head character or tail character
    char headChar,tailChar;
    string inputFileName;
    int c;
    opterr = 0;
    int length; // the length of the word chain assigned
    while((c=getopt(argc,argv,optstring))!=-1){
        switch (c){
            case 'w':{
                if(conflictflag){
                    cout << "ERROR:You can't choose both most words and most character both"<<endl;
                    exit(0);
                }
                else {
                        choice = true;
                        conflictflag = true;
                        break;
                }
            }
            case 'c':{
                if(conflictflag){
                    cout << "ERROR:You can't choose both most words and most character both"<<endl;
                    exit(0);
                }
                else {
                        choice = false;
                        //inputFileName = optarg;
                        conflictflag = true;
                        break;
                }
            }
            case 'h':{
                if(strlen(optarg)>1||opterr){
                    cout<< "ERROR:You can only assign one character as head character"<<endl;
                    exit(0);
                }
                else{
                    head = true;
                    headChar = optarg[0];
                    break;
                }
            }
            case 't':{
                if(strlen(optarg)>1 || opterr){
                    cout<< "ERROR:You can only assign one character as tail character"<<endl;
                    exit(0);
                }
                else{
                    tail = true;
                    tailChar = optarg[0];
                    break;
                }
            }
            case 'n':{
                if(opterr){
                    cout << "ERROR:You must assign a number of the -n parameter,line -n number";
                    exit(0);
                }
                else{
                    length = atoi(optarg);
                    fixedlength = true;
                    break;
                }
            }
            default:
                cout<<"ERROR:unrecognized parameter!"<<endl;
                break;
        }
    }
    if(!conflictflag){
        cout << "ERROR:You must have -w or -c parameter"<<endl;
        exit(0);
    }
    if(argc == optind){
        cout << "ERROR:You must have a file to input"<<endl;
        exit(0);
    }
    else{
        inputFileName = argv[argc-1];
    }
    cout << inputFileName<<endl;
}
