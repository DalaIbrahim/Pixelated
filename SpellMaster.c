// Project done by Dala Ibrahim (202206595), Jad Hneiny (202304032), and Issa Nouh (202205724)
// Phase 1 Submission

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SPELLS 100
#define SPELL_LENGTH 50
#define BOT_NAME "BOT_NAME"

// function to read spells from 'spellsname.txt' file and store them
int readSpellsFromFile(char spells[MAX_SPELLS][SPELL_LENGTH]) {
    FILE *file = fopen("spellsname.txt", "r");
    if (file == NULL) 
        printf("Error: Could not open 'spells.txt' file.\n");

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
        if (strcmp(spell[i], chosenSpell) == 0) { // chosen spell is found in spells array
            if (chosenSpells[i] == 1) // already chosen before
                return 0; 
            else {
                chosenSpells[i] = 1;
                return 1;
            }
        }
    }
    return 0; 
}

// check if spell matches the last character of the previous spell
int matchesLastChar(char lastChar, char chosenSpell[SPELL_LENGTH], int count) {
    if (count = 1)
        return 1;
    return chosenSpell[0] == lastChar;
}

int generateBotMove(char spells[MAX_SPELLS][SPELL_LENGTH], int chosenSpells[MAX_SPELLS], char lastChar) {
    
}

int main() {

    char spells[MAX_SPELLS][SPELL_LENGTH], chosenSpell[SPELL_LENGTH], playerName[SPELL_LENGTH], *prevSpell = NULL;
    srand(time(NULL));
    int count = 1, currentPlayer = rand() % 2; // either 0 or 1
    int numSpells = readSpellsFromFile(spells), chosenSpells[numSpells];

    // enter player names
    printf("Enter your name: ");
    scanf("%s", playerName);

    // print available spells
    printf("Available Spells:\n");
    for (int i = 0; i < numSpells; i++) {
        printf("%20s", spells[i]);
        if (i % 5 == 4 || i == numSpells - 1) 
            printf("\n");
        else 
            printf("\t");
    }

    printf("%s starts!\nEnter your spell: ", (currentPlayer == 1) ? playerName : BOT_NAME);
    scanf("%s", chosenSpell);

    while (1) {

        int otherPlayer = 1 - currentPlayer; 
        prevSpell = strdup(chosenSpell);
        char lastChar = prevSpell[strlen(prevSpell)-1];

        if (!isValidSpell(spells, chosenSpell, numSpells, chosenSpells)) {
            printf("%s wins! The spell was already chosen.\n", (otherPlayer == 1) ? playerName : BOT_NAME);
            break;
        }

        if (!matchesLastChar(lastChar, chosenSpell, count)) {
            printf("%s wins! Invalid spell1 The first letter doesn't match the last character of the previous spell.\n", (otherPlayer == 1) ? playerName : BOT_NAME);
            break;
        }

        printf("%s, your turn: ", (currentPlayer == 0) ? playerName : BOT_NAME);
        scanf("%s", chosenSpell);

        if (count == numSpells) {
            printf("%s wins! No more spells left.\n", (currentPlayer == 0) ? playerName : BOT_NAME);
            break;
        }

        count++;
        currentPlayer = otherPlayer;
        free(prevSpell);
    }

}