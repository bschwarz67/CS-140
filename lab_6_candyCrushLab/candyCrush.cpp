#include <fstream>
#include <cstdlib>
#include <iostream>
#include "candyCrush.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;


/* This constructor reads and stores information from a file that designates the row length or amount of candy in candy crush,
the different types of candy, and the point values and probabilities for each sequence length of candy. It then
constructs a list of candy to be played with and displayed made up of randomly generated sequences of the enumerated candies. */

candyCrush::candyCrush(string inputFile) {
    int seed, sequenceProbability, sequenceValue, sequenceProbabilityTotal = 0;
    string inputLine, flavor;
    fstream f;
    stringstream ss;

    f.open(inputFile.c_str());
    
    /* read in and check for valid seed value and rowLength */ 
    
    getline(f, inputLine);
    ss.str(inputLine);
    
    if(ss >> seed) {
        if(seed < 0) {
            printf("seed should be positive\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        printf("Seed value should be a positive integer\n");
        exit(EXIT_FAILURE);
    }

    if(ss >> rowLength) {
        if(rowLength < 0) {
            printf("Row length should be positive\n");
            exit(EXIT_FAILURE);
        }
    }

    else {
        printf("row length should be a positive integer\n");
        exit(EXIT_FAILURE);
    }




    /* read in the row with candy flavor values, add values flavors vector */

    ss.clear();
    getline(f, inputLine);
    ss.str(inputLine);
    while(ss >> flavor) {
        flavors.push_back(flavor);
    }
    
    
    /* Until the end of file is reached, read lines containing sequence length probability, sequence length value pairs.
    Checks for the validity of these values and stores a running total of probability in the probabilities array, as well as
    store the sequence length value in the points array. Program ended if probabilities dont add to 100*/

    while(getline(f, inputLine)) {
        ss.clear();
        ss.str(inputLine);
        if(ss >> sequenceProbability) {
            sequenceProbabilityTotal += sequenceProbability;
            probabilities.push_back(sequenceProbabilityTotal);
        }
        else {
            printf("ERROR: All candy sequence length probabilities should be positive integers\n");
            exit(EXIT_FAILURE);
        }
        if (ss >> sequenceValue) {
            points.push_back(sequenceValue);
        }
        else {
            printf(" ERROR: All candy sequence length values should be positive integers\n");
            exit(EXIT_FAILURE);
        }
    }

    if(sequenceProbabilityTotal != 100) {
        printf("ERROR: Total of all sequence length probabilities should equal 100\n");
        exit(EXIT_FAILURE);
    }



    srand (time(NULL));
    
    /* randomly generate a sequence length based on the weights given to sequence lengths in the inputFile. Randomly generate
    a flavor for the sequence. Add a sequence of the generated flavor,length to the candy list. Repeat this until the list is
    filled, if final sequence length exceeds the remaining size of the candy list, truncate the final sequence at the end
    of the list */
    
    while(candy.size() < rowLength) {
        string sequenceFlavor = flavors[rand() % flavors.size()];
        int randomChoice = rand() % 100;
        int sequenceLength;
        for(int i = 0; i < rowLength; i++) {
            if(randomChoice < probabilities[i]) {
                sequenceLength = i;
                i = rowLength;
            }
        }
        
        sequenceLength += 1;
        
        while(sequenceLength > 0 && candy.size() < rowLength) {
            candy.push_back(sequenceFlavor);
            sequenceLength--;
        }

    }


}

/*prints the candy list for the user to see */

void candyCrush::printCandy() {
    list <string>::iterator lit;
    int ind = 0;
    
    /* Prints each element in candy with a maximum of 8 words on each line of output */
    
    for(lit = candy.begin(); lit != candy.end(); lit++) {
        if(ind > 0 && ind % 8 == 0) {
            cout << endl;
        }
        printf("%-10s", lit->c_str());
        ind++;
    }
    cout << endl;
}

/* take the players choice of which candy from the list to remove in the form of a list index.
removes the value at that index as well as any left/right adjacent sequence of similar values.
Returns point value assigned the length of the sequence deleted */

int candyCrush::play(int choice) {
    list <string>::iterator current;
    list <string>::iterator next;
    int selectedSequenceLength = 0;
    string flavorAtPosition;
    

    current = candy.begin();
    
    for(int i = 0; i < choice; i++) {
        current++;
    }

    flavorAtPosition = *current;

    while(*current == flavorAtPosition) {
        selectedSequenceLength++;
        next = current;
        next++;
        candy.erase(current);
        current = next;
    }
    
    current--;

    while(*current == flavorAtPosition) {
        selectedSequenceLength++;
        next = current;
        next--;
        candy.erase(current);
        current = next;
    }
    
    printf("You scored %d points\n", points[selectedSequenceLength - 1]); 
    return points[selectedSequenceLength - 1];

}


/* client method that reads in user chosen list index, checks for index validity, and uses
this index in play(int choice) method to increment score, and refills the list with fillCandyList() */

void candyCrush::play() {
    int index;

    if(cin >> index && index >= 0 && index < rowLength) {
        score += play(index);
        fillCandyList();
    }
    
    else {
        printf("ERROR: Chosen index should be a positive integer between 0 and %d\n", rowLength - 1);
        cin.clear();
    }

}

/* fills the candy list with new flavor sequences until the size of the candy list is equal rowLength */

void candyCrush::fillCandyList() {

    /* randomly generate a sequence length based on the weights given to sequence lengths in the inputFile. Randomly generate
    a flavor for the sequence. Add a sequence of the generated flavor,length to the candy list. Repeat this until the list is
    filled, if final sequence length exceeds the remaining size of the candy list, truncate the final sequence at the end
    of the list */
    
    srand (time(NULL));
    while(candy.size() < rowLength) {
        string sequenceFlavor = flavors[rand() % flavors.size()];
        int randomChoice = rand() % 100;
        int sequenceLength;
        for(int i = 0; i < rowLength; i++) {
            if(randomChoice < probabilities[i]) {
                sequenceLength = i;
                i = rowLength;
            }
        }
        
        sequenceLength += 1;

        
        while(sequenceLength > 0 && candy.size() < rowLength) {
            candy.push_back(sequenceFlavor);
            sequenceLength--;
        }
        
    }

}

/* returns the player's current score */

int candyCrush::getScore() {
    return score;
}

/* returns the row length, or the number of elements in the candy list */

int candyCrush::getRowLength() {
    return rowLength;
}


