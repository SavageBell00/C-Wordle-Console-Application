#include "../inc/wordle.h"


// Function for populating grid with the users guessed word

void populateGrid(char** gameGridArray, char* userGuessedWord, int row, int wordLength, int numOfGuesses){

    // populating the grid row with user guessed word
    for(int i=0; i<wordLength; i++){
        gameGridArray[row][i]=(char)toupper(userGuessedWord[i]);
    }

    // populating the other grid rows with underscores
    for(int i=row+1; i<numOfGuesses; i++){
        for(int j=0; j<wordLength; j++){
            gameGridArray[i][j] = '_';
        }
    }
};


// function for gameBoardDisplay

bool gameBoardDisplay(char** gameGridArray, char* correctWord, int wordLength, int numOfGuesses){

    printf("\nCurrent game state:\n");

    // int variable to hold the amount of correct characters
    int numOfCorrectGuesses = 0;

    // bool to check if game is won or not
    bool wonGame = false;

    // nested for loop to display grid based off numOfGuesses and wordLength
    for(int i=0; i<numOfGuesses; i++){
        for(int j=0; j<wordLength; j++){
            char currentChar = gameGridArray[i][j];
            if(currentChar == '_'){
                printf("%c", currentChar);
                printf(" ");
            } else {
                // bool which will return if the character is in the given word
                bool charInWord = isCharInWord(correctWord, currentChar);
                // bool which will return if char is in correct position
                bool charInPosition = indexOfWord(correctWord, currentChar, j);

                if(charInWord && charInPosition){ // if currentchar is in word and correct index Position
                    printGreen(currentChar);
                    printf(" ");
                    numOfCorrectGuesses++;
                    wonGame = numOfCorrectGuesses == wordLength ? true : false;
                } else if (charInWord){
                    printYellow(currentChar);
                    printf(" ");
                } else { // if in wrong position and not in the word
                    printf("%c",currentChar);
                    printf(" ");
                }
            }
        }
        numOfCorrectGuesses = 0; // reinitializing back to 0
        printf("\n");

    }

    return wonGame;
}



// Function to check if guessed word and its char is in the correctWord
bool isCharInWord(char* correctWord, char characterGuessed){
    if(strchr(correctWord, characterGuessed) != NULL){

        return true;

    } else {

        return false;
    }
}

// Function to check if the char index of the userGuessedWord watches the char index of the correctWord
bool indexOfWord(char* correctWord, char userGuessedChar, int indexOfCharacter){
    if(correctWord[indexOfCharacter] == userGuessedChar){

        return true;
    } else {

        return false;
    }
}

// Function to check if inputted word is the proper length
bool validateGuessedWord(char* userGuessedWord, int wordLength){
    int givenWordLength = strlen(userGuessedWord);
    if(givenWordLength == wordLength){
        for(int i=0; i<givenWordLength; i++){
            char currTempChar = (char) toupper(userGuessedWord[i]);
            if(!(currTempChar >= 'A' && currTempChar <= 'Z')){

                return false;
            }
            userGuessedWord[i] = currTempChar;
        }

        return true;
    } else {

        return false;
    }
};

    // Functions for Colors
    void printYellow(char currentChar){
        printf("\033[0;33m");
        printf("%c", currentChar);
        printf("\033[0m");
    }

    void printGreen(char currentChar){
        printf("\033[0;32m");
        printf("%c", currentChar);
        printf("\033[0m");
    }


