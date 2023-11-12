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
        if (chosenSpells[i] == 0 && (lastChar == '*' || spells[i][0] == lastChar)) {
            chosenSpells[i] = 1;
            int value = minimax(spells, chosenSpells, spells[i][strlen(spells[i]) - 1], 2, 0, INT_MIN, INT_MAX);
            chosenSpells[i] = 0;

            if (value >= bestValue) {
                bestValue = value;
                bestMove = i;
            }
        }
    }

    if (bestMove == -1) {
        return -1; // no valid move found
    }

    return bestMove;
}

int main() {
    char spells[MAX_SPELLS][SPELL_LENGTH], chosenSpell[SPELL_LENGTH], playerName[SPELL_LENGTH];
    int chosenSpells[MAX_SPELLS] = {0};
    srand(time(NULL));
    int currentPlayer = rand() % 2;
    int numSpells = readSpellsFromFile(spells);

    printf("Enter your name: ");
    scanf("%s", playerName);

    printSpells(spells, numSpells);
    printf("Tossing a fair coin...\n");
    printf("%s starts!\n", (currentPlayer == 1) ? playerName : BOT_NAME);

    char lastChar = '\0'; // Initialize lastChar
    int count = 0;

    while (1) {
        int otherPlayer = 1 - currentPlayer;

        if (currentPlayer == 0) { // bot's turn
            if (count == 0) { // bot's first move
                int botMove = rand() % numSpells; // choose a random spell for the first spell
                while (chosenSpells[botMove] == 1) { // this is to ensure that the spell hasn't been chosen before
                    botMove = rand() % numSpells;
                }
                strcpy(chosenSpell, spells[botMove]);
                chosenSpells[botMove] = 1;
                printf("%s chose: %s\n", BOT_NAME, chosenSpell);
            } else {
                int botMove = generateBotMoveMinimax(spells, chosenSpells, lastChar);
                if (botMove == -1) {
                    printf("%s wins! No valid move for bot.\n", playerName);
                    break;
                }
                strcpy(chosenSpell, spells[botMove]);
                chosenSpells[botMove] = 1;
                printf("%s chose: %s\n", BOT_NAME, chosenSpell);
            }
        } else { // player's turn
            printf("%s, your turn: ", playerName);
            scanf("%s", chosenSpell);
            int spellIndex = -1;
            for (int i = 0; i < numSpells; i++) {
                if (strcmp(spells[i], chosenSpell) == 0) {
                    spellIndex = i;
                    break;
                }
            }
            if (spellIndex == -1 || chosenSpells[spellIndex] == 1 || !matchesLastChar(lastChar, chosenSpell, count)) {
                printf("%s wins! Invalid move.\n", BOT_NAME);
                break;
            }
            chosenSpells[spellIndex] = 1;
        }

        lastChar = chosenSpell[strlen(chosenSpell) - 1];
        count++;
        currentPlayer = otherPlayer;

        if (count >= 2 * numSpells) {
            printf("Game over. It's a draw!\n");
            break;
        }
    }

    return 0;
}