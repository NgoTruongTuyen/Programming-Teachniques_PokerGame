//-------------------Single player---------------
// lấy năm lá bài đầu tiên phát cho người chơi.
#include "PokerGame.h"

//Check the same value
//tra ve mang int **hand
int** dealingForHand(int deck[SUITS][RANKS]) {
    int** hand = new int* [NUMCARDS];

    for (int i = 0; i < NUMCARDS; i++) {
        hand[i] = new int[NUMDESCRIP];
    }

    //Find the top card of the deck in deck matrix and get suit index, rank index of it to assign for hand matrix, which stored the cards in hand of player  
    int select;
    cout << "1. Get the five cards by yourself." << endl;
    cout << "2. Get the five cards by the way random." << endl;

    do {
        cout << "Your choose: ";
        cin >> select;
        if (select <= 0 || select > 2) {
            cout << "Invalid option!" << endl;
        }
    } while (select <= 0 || select > 2);

    int* pPosCard = new int[NUMCARDS];
    switch (select) {
    case 1: {
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            cout << "The " << cardIndex + 1 << "(th) card: ";
            cin >> pPosCard[cardIndex];
        }
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            for (int suitIndex = 0; suitIndex < SUITS; suitIndex++) {
                for (int rankIndex = 0; rankIndex < RANKS; rankIndex++) {
                    if (deck[suitIndex][rankIndex] == pPosCard[cardIndex]) {
                        hand[cardIndex][0] = suitIndex;
                        hand[cardIndex][1] = rankIndex;
                    }
                }
            }
        }
        break;
    }

    default: {
        int* tempValue = new int[NUMCARDS];
        tempValue[0] = rand() % 10 + 1;
        tempValue[1] = rand() % 10 + 11;
        tempValue[2] = rand() % 10 + 21;
        tempValue[3] = rand() % 10 + 31;
        tempValue[4] = rand() % 12 + 41;
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            for (int suitIndex = 0; suitIndex < SUITS; suitIndex++) {
                for (int rankIndex = 0; rankIndex < RANKS; rankIndex++) {
                    if (deck[suitIndex][rankIndex] == (tempValue[cardIndex])) {
                        hand[cardIndex][0] = suitIndex;
                        hand[cardIndex][1] = rankIndex;
                    }
                }
            }
        }
        delete[] tempValue;
        break;
    }
    }
    delete[] pPosCard;
    return hand;
}

//in ra các lá bài đang cầm trên tay.
void printHand(int** hand, const char* suits[], const char* ranks[]) {
    for (int i = 0; i < NUMCARDS; i++) {
        cout << "(" << suits[hand[i][0]] << ", " << ranks[hand[i][1]] << ")";
    }
}

int** createHandTest(int deck[SUITS][RANKS], int a[]) {
    int** hand = new int* [NUMCARDS];
    for (int i = 0; i < NUMCARDS; i++) {
        hand[i] = new int[NUMDESCRIP];
    }

    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        for (int suitIndex = 0; suitIndex < SUITS; suitIndex++) {
            for (int rankIndex = 0; rankIndex < RANKS; rankIndex++) {
                if (deck[suitIndex][rankIndex] == (a[cardIndex])) {
                    hand[cardIndex][0] = suitIndex;
                    hand[cardIndex][1] = rankIndex;
                }
            }
        }
    }

    return hand;
}

// hàm này sử dụng riêng cho file này
void sortByBubbleSort(int** hand) {
    for (int i = 1; i < NUMCARDS; i++) {
        for (int j = NUMCARDS - 1; j >= i; j--) {
            if (hand[j][1] < hand[j - 1][1]) {
                swap(hand[j][0], hand[j - 1][0]);//use algorithm Library
                swap(hand[j][1], hand[j - 1][1]);
            }
        }
    }
}

//check the same rank 
bool isSequentialRank(int** hand) {
    for (int cardIndex = 0; cardIndex < NUMCARDS - 1; cardIndex++) {
        if ((hand[cardIndex][1] + 1) != hand[cardIndex + 1][1]) {
            return false;
        }
    }
    return true;
}

//A function that checks whether a hand contains Straight flush
int isStraightFlush(int** hand) {
    for (int cardsIndex = 1; cardsIndex < NUMCARDS; cardsIndex++) {
        if (hand[0][0] != hand[cardsIndex][0]) {
            return 0;
        }
    }

    if (!isSequentialRank(hand)) {
        return 0;
    }
    return 1;
}

//A function that checks whether a hand contains Four of a kind
int isFourOfAKind(int** hand) {
    //initialize counter variable for sameRankCards 
    int sameRankCards = 1;

    //iterate card in player's hand
    for (int cardIndex = 0; cardIndex < NUMCARDS - 3; cardIndex++) {
        //with each card, we compare it with the remaining cards
        for (int comparisonIndex = cardIndex + 1; comparisonIndex < NUMCARDS; comparisonIndex++) {
            if (hand[cardIndex][1] == hand[comparisonIndex][1]) {
                sameRankCards++;
            }
        }

        if (sameRankCards == 4) {
            return 1;
        }

        sameRankCards = 1;
    }

    return 0;
}

int isFullHouse(int** hand) {
    int count = 1, count1 = 1, temp = 0;
    int rowOfHand = 5;

    for (int i = 0; i < rowOfHand - 2; i++) {
        for (int j = i + 1; j < rowOfHand; j++) {
            if (hand[i][1] == hand[j][1]) {
                count++;
                temp = hand[i][1];
            }
        }

        if (count == 3) {
            for (int m = 0; m < rowOfHand - 1; m++) {
                if (hand[m][1] != temp) {
                    for (int n = m + 1; n < rowOfHand; n++) {
                        if (hand[m][1] == hand[n][1]) {
                            count1++;
                        }

                        if (count1 == 2) {
                            return 1;
                        }

                        count1 = 1;
                    }
                }
            }
        }

        if (count > 3) {
            return 0;
        }

        count = 1;
    }

    return 0;
}

int isFlush(int** hand) {
    for (int cardIndex = 1; cardIndex < NUMCARDS; cardIndex++) {
        if (hand[0][0] != hand[cardIndex][0]) {
            return 0;
        }
    }

    if (isSequentialRank(hand)) {
        return 0;
    }

    return 1;
}

int isStraight(int** hand) {
    if (!isSequentialRank(hand)) {
        return 0;
    }

    for (int cardsIndex = 1; cardsIndex < NUMCARDS; cardsIndex++) {
        if (hand[0][0] != hand[cardsIndex][0]) {
            return 1;
        }
    }

    return 0;
}

int isThreeOfAKind(int** hand) {
    int count = 1, count1 = 1, temp = 0;
    int rowOfHand = 5;

    for (int i = 0; i < rowOfHand - 2; i++) {
        for (int j = i + 1; j < rowOfHand; j++) {
            if (hand[i][1] == hand[j][1]) {
                count++;
                temp = hand[i][1];
            }
        }

        if (count == 3) {
            for (int m = 0; m < rowOfHand - 1; m++) {
                if (hand[m][1] != temp) {
                    for (int n = m + 1; n < rowOfHand; n++) {
                        if (hand[m][1] == hand[n][1])
                            count1++;

                        if (count1 == 1)
                            return 1;

                        if (count1 > 1)
                            return 0;

                        count1 = 1;
                    }
                }
            }
        }

        if (count > 3) {
            return 0;
        }

        count = 1;
    }

    return 0;
}

//A function that checks whether a hand contains Flush
int isTwoPairs(int** hand) {
    //initialize counter variable for sameRanksCards
    int sameRanksCards = 0;

    //iterate card in player's hand
    for (int cardsIndex = 0; cardsIndex < NUMCARDS; cardsIndex++) {
        //with each card, we compare it with the remaining cards
        for (int comparisonIndex = cardsIndex + 1; comparisonIndex < NUMCARDS; comparisonIndex++) {
            if (hand[cardsIndex][1] == hand[comparisonIndex][1]) {
                sameRanksCards++;
            }
        }
    }

    if (sameRanksCards == 2) {
        return 1;
    }

    return 0;
}

//A function that checks whether a hand contains Pair
int isPair(int** hand) {
    int count = 1, count1 = 1, temp = 0;
    int rowOfHand = 5;

    for (int i = 0; i < rowOfHand - 2; i++) {
        for (int j = i + 1; j < rowOfHand; j++) {
            if (hand[i][1] == hand[j][1]) {
                count++;
                temp = hand[i][1];
            }
        }

        if (count == 2) {
            for (int m = 0; m < rowOfHand - 1; m++) {
                if (hand[m][1] != temp) {
                    for (int n = m + 1; n < rowOfHand; n++) {
                        if (hand[m][1] == hand[n][1])
                            count1++;

                        if (count1 > 1)
                            return 0;

                        count1 = 1;
                    }
                }
            }

            return 1;
        }

        if (count > 2) {
            return 0;
        }

        count = 1;
    }

    return 0;
}

int getHighestCard(int** hand) {
    return hand[NUMCARDS - 1][1] + 1;
}

void rankHand(int** hand) {
    sortByBubbleSort(hand);
    if (isStraightFlush(hand)) {
        cout << "Your card is straight flush and 8 point" << endl;
        return;
    }

    if (isFourOfAKind(hand)) {
        cout << "Your card is four of a kind and 7 point" << endl;
        return;
    }

    if (isFullHouse(hand)) {
        cout << "Your card is full house and 6 point" << endl;
        return;
    }

    if (isFlush(hand)) {
        cout << "Your card is flush and 5 point" << endl;
        return;
    }

    if (isStraight(hand)) {
        cout << "Your card is straight and 4 point" << endl;
        return;
    }

    if (isThreeOfAKind(hand)) {
        cout << "Your card is three of a kind and 3 point" << endl;
        return;
    }

    if (isTwoPairs(hand)) {
        cout << "Your card is two pairs and 2 point" << endl;
        return;
    }

    if (isPair(hand)) {
        cout << "Your card is pair and 1 point" << endl;
        return;
    }

    cout << "The card is non of hand-ranking categories!" << endl;
}