#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/wordle.h"




/*
 * NOTE: Follow this example to use ANSI colours at the terminal:
 * https://www.theurbanpenguin.com/4184-2/
 *
 * In order to get ANSI colors showing in the CLion Run Console,
 * we need to do the following routine:
 *
 * 1. Choose Help -> Edit Custom Properties from CLion menu
 * 2. Add the following line to the idea.properties file:
 *      run.processes.with.pty=false
 * 3. Restart CLion.
 *
 * Reference:
 * https://youtrack.jetbrains.com/issue/CPP-8395/Registry-setting-runprocesseswithpty-not-saved#focus=Comments-27-2499735.0-0
 *
 */



int main(int argc, char *argv[]) {

    setbuf(stdout,0);
    // Declaring inputFile pointer and outputFile pointer
    FILE* inputFile;
    FILE* outputFile;
    char firstLineRead[20]; // inputfile
    // Declaring 2d array
    char** gameGridArray;
    char solutionFound[]= "The solution was found.";
    char solutionNotFound[] = "The solution was not found.";
    bool gameWon = false;
    bool validGuess = false;
    // Logic for Command Line Arguments
    if(argc != COMMAND_LINE_ARGS){

        printf("Invalid number of command line arguments.\n", stderr);

        return 1;

    } else if (strcmp(argv[1], "-i") == 0) { // if second command is -i

        if(strcmp(argv[3], "-o") ==0){ // if third command is -o

            inputFile = fopen(argv[2], "r"); // reading the inputFile given

            if(inputFile == NULL){ // if input file is null

                printf("Cannot open %s for reading.\n",argv[2],stderr);

                return 1;
            }

            outputFile = fopen(argv[4],"w"); // write to outputFile given

            if(outputFile == NULL){  // if output file is null

                printf("Cannot open %s for writing.\n", argv[4], stderr);

                return 1;
            }
        } else {

            printf("Invalid command line argument usage.\n", stderr);

            return 1;
        }
    } else if (strcmp(argv[1], "-o") == 0) { // if second command is -o

        if(strcmp(argv[3], "-i") ==0){ // if fourth command is -i

            outputFile = fopen(argv[2],"w"); // write to outputFile given

            if(outputFile == NULL){ // if outputfile is null

                printf("Cannot open %s for writing.\n", argv[2], stderr);

                return 1;
            }

            inputFile = fopen(argv[4], "r"); // reading the inputFile given

            if(inputFile == NULL){ // if inputfile is null

                printf("Cannot open %s for reading.\n",argv[4],stderr);

                return 1;
            }
        } else {

            printf("Invalid command line argument usage.\n", stderr);

            return 1;
        }
    } else{

        printf("Invalid command line argument usage.\n", stderr);

        return 1;
    }

    // Printing out Header
    printf("Welcome to C-Wordle!!\n");

    // Reading in input file to store word count, num of guesses, and correct word

    // reading in entire line from inputFile into firstLineRead
    fgets(firstLineRead,sizeof(firstLineRead),inputFile);
    int wordLength = atoi(&firstLineRead[0]); // storing word count and converting to int
    int numOfGuesses = atoi(&firstLineRead[2]); // storing num of guesses and converting to int

    char correctWord[wordLength+1]; // for correctWord and null term

    fgets(correctWord,sizeof(correctWord),inputFile); // reading in second line into correctWord char[]

    // Allocating memory to char 2d array
    gameGridArray = (char**) calloc(numOfGuesses,sizeof (char*));

    // allocating memory for each pointer inside of gameGridArray
    for (int i=0; i<=numOfGuesses; i++){ //
        gameGridArray[i] = (char*) calloc(numOfGuesses,sizeof (char)); // points to single pointer that points to our word guess
    }

    // nested for loop to populate grid
    for (int i=0;i<=numOfGuesses;i++){
        for (int j=0;j<=wordLength; j++){
            gameGridArray[i][j] = '_';
        }
    }

    // Displaying Grid
    gameBoardDisplay(gameGridArray,correctWord,wordLength,numOfGuesses);



    // Main game loop
    for(int i=0; i<numOfGuesses;i++){

        char userGuessedWord[wordLength+1];
        char tempGuessedWord[25];



        // validating user input length
        while(!validGuess){
            printf("Please enter %i -letter word:",wordLength);
            scanf("%s",tempGuessedWord);

            if(strlen(tempGuessedWord) > wordLength || strlen(tempGuessedWord) < wordLength){
                printf("Sorry, but you can only enter %i -letter words", wordLength);
                continue;

            } else {
                strcpy(userGuessedWord,tempGuessedWord);
                validGuess = true;
            }
        }


        validateGuessedWord(userGuessedWord,wordLength);
        populateGrid(gameGridArray,userGuessedWord,i,wordLength,numOfGuesses);
        gameWon = gameBoardDisplay(gameGridArray,correctWord,wordLength,numOfGuesses);
        if(gameWon){
            printf("You WIN!!!\n");
        }
    }
    // if user does not guess correctly

    if (gameWon == false){
        printf("You LOSE!!!\n");
        fputs(solutionNotFound, outputFile); // writing to output file
    } else {
        fputs(solutionFound, outputFile); // if won, writing to output file
    }

    // writing gamegrid to output file
    for(int i=0; i<numOfGuesses; i++){
        fputs(gameGridArray[i],outputFile);
        putc('\n', outputFile); // printing a new line after each gamegrid line
    }
     // Closing files
    fclose(inputFile);
    fclose(outputFile);

    // deallocate memory
    for(int i=0; i<numOfGuesses; i++){
        free(gameGridArray[i]); // freeing memory for each row in gameGrid
    }
    // freeing the entire gameGridArray that held the rows.
    free(gameGridArray);

    return 0;
}
