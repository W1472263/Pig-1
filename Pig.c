//
//  Pig.c
//  
//
//  Created by Maximilian Litteral on 4/22/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef enum {
    turnPlayer = 0,
    turnAI = 1,
} Turn;

Turn turn = turnPlayer;
int playerScore = 0;
int AIScore = 0;

int firstPlayersTurn() {
    srand(time(NULL));
    return rand()%2;
}

int shouldComputerContinue() {
    srand(time(NULL));
    return rand()%2;
}

int diceRoll() {
//    srand(time(NULL));
    return rand() % 6 + 1;
}

int main(void)
{
    char name[10];
    
    printf("Welcom to Pig!\n");
    printf("Please enter your name: ");
    scanf("%s", name);
    printf("Welcome %s\n", name);
    
    turn = firstPlayersTurn();
    
    int temporaryScore = 0;
    bool playerContinueRoll = false;
    int maximiumNumberOfTurnsInRowforComputer = 10;
    int numberOfComputerTurns = 0;
    
    for (;;) {

        if (turn == turnPlayer) {
            // Player
            char gameContinue;
            
            if (playerContinueRoll == true) {
                printf("Would you like to continue? (Y/N)\n");
                scanf(" %c", &gameContinue);
            }
            else {
                printf("----------------------------\n");
                printf("It is your turn - %i\n", playerScore);
                printf("----------------------------\n");
                gameContinue = 'Y';
            }
            
            if (gameContinue == 'Y') {
                int roll = diceRoll();
                printf("You rolled %i\n", roll);
                
                // Check if lost or not
                if (roll == 1) {
                    // You lost
                    printf("You lost %i points\n", temporaryScore);
                    temporaryScore = 0;
                    playerContinueRoll = false;
                }
                else {
                    // Add to temporary score, keep going
                    temporaryScore += roll;
                    playerContinueRoll = true;
                }
            }
            else {
                // Add temporary score to player score
                playerScore += temporaryScore;
                temporaryScore = 0;
                playerContinueRoll = false;
            }
        }
        else {
            // AI
            if (playerContinueRoll == false) {
                printf("----------------------------\n");
                printf("Computers turn - %i\n", AIScore);
                printf("----------------------------\n");
            }
            
            int roll = diceRoll();
            printf("Computer rolled %i\n", roll);
            
            // Increase computer turns
            numberOfComputerTurns++;
            
            // Check if computer lost
            if (roll == 1) {
                printf("Computer lost %i points :(\n", temporaryScore);
                temporaryScore = 0;
                playerContinueRoll = false;
                numberOfComputerTurns = 0;
            }
            else {
                // Add to temporary score, keep going
                temporaryScore += roll;
                playerContinueRoll = true;
            }
            
            int computerContinueRolling = shouldComputerContinue();
            if (computerContinueRolling == 1 ||
                numberOfComputerTurns >= maximiumNumberOfTurnsInRowforComputer) {
                // End computers turn
                AIScore += temporaryScore;
                temporaryScore = 0;
                playerContinueRoll = false;
                numberOfComputerTurns = 0;
            }
        }
        
        if (playerScore >= 100 || AIScore >= 100) {
            if (playerScore >= 100) {
                printf("%s won the game!!!🎉🎉🎉🎉🎉🎉🎉\n", name);
            }
            else {
                printf("Computer won the game!!!\n");
            }
            break;
        }
        
        if (playerContinueRoll == false) {
            turn = turn == turnPlayer ? turnAI : turnPlayer;
        }
    }
    
    return 0;
}
