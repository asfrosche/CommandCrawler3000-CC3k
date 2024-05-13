#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include "board.h"
using namespace std;
 
 bool isNumber(string s) {
    for (auto& n : s) {
        if (!isdigit(n)) return false;
    } 
    return true;
 }

int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    bool fileIncluded = false;
    bool dlc = false;
    string theFile = "";
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (isNumber(argv[i])) { 
                srand(atoi(argv[i])); 
            } else if (strcmp(argv[i], "dlc") == 0) {
                dlc = true;
            } else {
                ifstream file;
                file.open(argv[i]);
                if (!file) {
                    cout << "Invalid command line arguments" << endl;
                    return 0;
                } else {
                    fileIncluded = true;
                    theFile = argv[i];
                }
            }
        }
    }
    Board b{fileIncluded, theFile, dlc};
    bool done = false;
    while (!done) {
        done = b.playGame();
    }
}
