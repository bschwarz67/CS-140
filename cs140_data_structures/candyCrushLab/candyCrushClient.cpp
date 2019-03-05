#include <cstdlib>
#include <iostream>
#include "candyCrush.h"
#include <string>

using namespace std;

int main() {
    
    candyCrush test = candyCrush("testfile.txt");
    string command;
    int index;
    
    while(true) {
        printf("Enter a command from list:\n PRINT\n CHOOSE index\n SCORE\n QUIT\n");
        cin >> command;
        if(command == "PRINT") {
            test.printCandy();
        }
        else if(command == "SCORE") {
            printf("Your current score:  %d  \n", test.getScore());
        }
        else if(command == "CHOOSE") {
            test.play();
        }
        else if (command == "QUIT") {
            printf("Game ended. Final score: %d\n", test.getScore());
            return 0;
        }
        else {
            printf("ERROR: Improper command, please re-enter\n");
        }
    }
    return 0;

}
