// Project done by Dala Ibrahim (202206595), Jad Hneiny (202304032), and Issa Nouh (202205724)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>


#define MAX_SPELLS 100
#define SPELL_LENGTH 50
#define BOT_NAME "VoldeBot"

int readSpellsFromFile(char spells[MAX_SPELLS][SPELL_LENGTH]);
int isValidSpell(char spell[MAX_SPELLS][SPELL_LENGTH], char chosenSpell[SPELL_LENGTH], int numSpells, int chosenSpells[MAX_SPELLS]);
int matchesLastChar(char lastChar, char chosenSpell[SPELL_LENGTH], int count);
int evaluateMove(char spells[MAX_SPELLS][SPELL_LENGTH], int chosenSpells[MAX_SPELLS], char lastChar, int move);
int minimax(char spells[MAX_SPELLS][SPELL_LENGTH], int chosenSpells[MAX_SPELLS], char lastChar, int depth, int maximizingPlayer, int alpha, int beta);
int generateBotMoveMinimax(char spells[MAX_SPELLS][SPELL_LENGTH], int chosenSpells[MAX_SPELLS], char lastChar);


void printSpells(char spells[MAX_SPELLS][SPELL_LENGTH], int numSpells)
{
    printf("Available Spells:\n");
    for (int i = 0; i < numSpells; i++)
    {
        printf("%20s", spells[i]);
        if (i % 5 == 4 || i == numSpells - 1)
            printf("\n");
        else
            printf("\t");
    }
}

// function to read spells from 'spellsname.txt' file and store them
int readSpellsFromFile(char spells[MAX_SPELLS][SPELL_LENGTH]) {
    FILE *file = fopen("spellsname.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open 'spells.txt' file.\n");
        return -1;
    }

    int numSpells;
    fscanf(file, "%d", &numSpells);
  
    for (int i = 0; i < numSpells; i++) 
        fscanf(file, "%s", spells[i]);
    
    fclose(file);
    return numSpells;
}

// check if spell has not been cast before
int isValidSpell(char spell[MAX_SPELLS][SPELL_LENGTH], char chosenSpell[SPELL_LENGTH], int numSpells, int chosenSpells[MAX_SPELLS]) {
    for (int i = 0; i < numSpells; i++) {
        if (strcmp(spell[i], chosenSpell) == 0) {
            if (chosenSpells[i] == 1)
                return 0;
            return 1;
        }
    }
    return 0;
}

// check if spell matches the last character of the previous spell
int matchesLastChar(char lastChar, char chosenSpell[SPELL_LENGTH], int count) {
    if (count == 0 || lastChar == '*' || lastChar == '\0')
        return 1;
    return chosenSpell[0] == lastChar;
}

// function to evaluate the potential of a move 
int evaluateMove(char spells[MAX_SPELLS][SPELL_LENGTH], int chosenSpells[MAX_SPELLS], char lastChar, int move)
{
    int score = 0;
    for (int i = 0; i < MAX_SPELLS; i++)
    {
        if (chosenSpells[i] == 0 && spells[i][0] == spells[move][strlen(spells[move]) - 1])
        {
            score++;
        }
    }
    return score;
}

// minimax algorithm with alpha-beta pruning
int minimax(char spells[MAX_SPELLS][SPELL_LENGTH], int chosenSpells[MAX_SPELLS], char lastChar, int depth, int maximizingPlayer, int alpha, int beta)
{
if (depth == 0)
    {
        return evaluateMove(spells, chosenSpells, lastChar, -1);
    }

    int bestValue;
    if (maximizingPlayer)
    {
        bestValue = INT_MIN;
        for (int i = 0; i < MAX_SPELLS; i++)
        {
            if (chosenSpells[i] == 0 && spells[i][0] == lastChar)
            {
                chosenSpells[i] = 1;
                int value = minimax(spells, chosenSpells, spells[i][strlen(spells[i]) - 1], depth - 1, 0, alpha, beta);
                bestValue = (value > bestValue) ? value : bestValue;
                alpha = (alpha > bestValue) ? alpha : bestValue;
                chosenSpells[i] = 0;

                if (beta <= alpha)
                    break;
            }
        }
    }
    else
    {
        bestValue = INT_MAX;
        for (int i = 0; i < MAX_SPELLS; i++)
        {
            if (chosenSpells[i] == 0 && spells[i][0] == lastChar)
            {
                chosenSpells[i] = 1;
                int value = minimax(spells, chosenSpells, spells[i][strlen(spells[i]) - 1], depth - 1, 1, alpha, beta);
                bestValue = (value < bestValue) ? value : bestValue;
                beta = (beta < bestValue) ? beta : bestValue;
                chosenSpells[i] = 0;

                if (beta <= alpha)
                    break;
            }
        }
    }

    return bestValue;

}

// function to generate a move for the bot using the minimax algorithm we previously implemented
int generateBotMoveMinimax(char spells[MAX_SPELLS][SPELL_LENGTH], int chosenSpells[MAX_SPELLS], char lastChar) {
    int bestMove = -1;
    int bestValue = INT_MIN;

    for (int i = 0; i < MAX_SPELLS; i++) {
        if (chosenSpells[i] == 0 && spells[i][0] == lastChar) {
            chosenSpells[i] = 1;
            int value = minimax(spells, chosenSpells, spells[i][strlen(spells[i]) - 1], 2, 0, INT_MIN, INT_MAX);
            chosenSpells[i] = 0;

            if (value >= bestValue) {  // Changed the condition to consider equal values
                bestValue = value;
                bestMove = i;
            }
        }
    }

    // If no optimal move is found, choose a random move
    if (bestMove == -1) {
        do {
            bestMove = rand() % MAX_SPELLS;
        } while (chosenSpells[bestMove] == 1);
    }

    return bestMove;
}

int main() {

     char spells[MAX_SPELLS][SPELL_LENGTH], chosenSpell[SPELL_LENGTH], playerName[SPELL_LENGTH], *prevSpell = NULL;
    int chosenSpells[MAX_SPELLS] = {0};
    srand(time(NULL));
    int count = 1, currentPlayer = rand() % 2; // either 0 or 1
    int numSpells = readSpellsFromFile(spells);
    
    // Enter player name
    printf("Enter your name: ");
    scanf("%s", playerName);

    // Print available spells
    printSpells(spells, numSpells);

    // Toss a fair coin to determine who starts and announce the result
    printf("Tossing a fair coin...\n");
    printf("%s starts!\n", (currentPlayer == 1) ? playerName : BOT_NAME);

    while (1)
    {
        int otherPlayer = 1 - currentPlayer;
        prevSpell = chosenSpell;
        char lastChar = (prevSpell != NULL) ? prevSpell[strlen(prevSpell) - 1] : '\0';

        if (currentPlayer == 0)
        { // Bot's turn
            int botMove = generateBotMoveMinimax(spells, chosenSpells, lastChar);
            strcpy(chosenSpell, spells[botMove]);
            printf("%s chose: %s\n", BOT_NAME, chosenSpell);
        }
        else
        { // Player's turn
            printf("%s, your turn: ", playerName);
            scanf("%s", chosenSpell);
        }

        if (!isValidSpell(spells, chosenSpell, numSpells, chosenSpells) ||
            !matchesLastChar(lastChar, chosenSpell, count))
        {
            printf("%s wins! Invalid move.\n", (otherPlayer == 1) ? playerName : BOT_NAME);
            break;
        }

        // Check if both players have played at least once
        if (count >= 2 * numSpells)
        {
            printf("Game over. It's a draw!\n");
            break;
        }

        count++;
        currentPlayer = otherPlayer;
    }

        return 0;

}