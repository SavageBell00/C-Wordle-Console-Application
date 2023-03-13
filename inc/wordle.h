#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#ifndef ASSIGN5_WORDLE_H
#define ASSIGN5_WORDLE_H


// Macro definitions

#define COMMAND_LINE_ARGS 5



// function prototype to display game and take in correctWord, wordLength, and numOfGuesses
bool gameBoardDisplay(char** gameGridArray, char* correctWord, int wordLength, int numOfGuesses);

void printGrid(int numOfGuesses, int wordLength);
// function prototype to input the valid word into the grad
void populateGrid(char** gameGridArray, char* userGuessedWord, int row, int wordLength, int numOfGuesses);

// function prototype to validate guessed word
bool validateGuessedWord(char* userGuessedWord, int wordLength);

// function prototype to validate if a character given is inside the correctWord
bool isCharInWord(char* correctWord, char characterGuessed);

// function prototype to check the index of a character
bool indexOfWord(char* correctWord, char userGuessedChar, int indexOfCharacter);

// methods for printing colored characters
void printGreen(char currentChar);
void printYellow(char currentChar);

#endif //ASSIGN5_WORDLE_H
