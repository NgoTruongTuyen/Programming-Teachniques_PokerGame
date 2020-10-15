#include "PokerGame.h"

bool checkValueOfShuffleCard(int valueArray[], int elements, int number) {
    for (int i = 0; i < elements; i++) {
        if (valueArray[i] == number) {
            return false;
        }
    }
    return true;
}

void shuffleCard(int deck[][RANKS]) {
    int tempValue[52] = { 0 };
    int index = 0;
    srand(time(NULL));

    for (int suitIndex = 0; suitIndex < SUITS; suitIndex++) {
        for (int rankIndex = 0; rankIndex < RANKS; rankIndex++) {
            deck[suitIndex][rankIndex] = rand() % 52 + 1;

            if (checkValueOfShuffleCard(tempValue, index, deck[suitIndex][rankIndex])) {
                tempValue[index] = deck[suitIndex][rankIndex];
                index++;
            }
            else {
                rankIndex--;
            }
        }
    }
}

void printCardsShuffling(int deck[][RANKS], const char* suits[], const char* ranks[]) {
    for (int i = 1; i < 53; i++) {
        for (int row = 0; row < SUITS; row++) {
            for (int column = 0; column < RANKS; column++) {
                if (deck[row][column] == i) {
                    cout << "(" << suits[row] << ", " << ranks[column] << "), ";
                }
            }
        }
    }

    cout << endl;
}