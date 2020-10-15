#include "PokerGame.h"
//Con bien trong 

int** playingCard(int deck[SUITS][RANKS]) {
    int** ptr = new int*[TOTALCARDS];
    for (int totalIndex = 0; totalIndex < TOTALCARDS; totalIndex++) {
        ptr[totalIndex] = new int[NUMDESCRIP];
    }

    int rowPtr = 0;
    for (int totalIndex = 1; totalIndex <= TOTALCARDS; totalIndex++) {
        for (int suitIndex = 0; suitIndex < SUITS; suitIndex++) {
            for (int rankIndex = 0; rankIndex < RANKS; rankIndex++) {
                if (deck[suitIndex][rankIndex] == totalIndex) {
                    ptr[rowPtr][0] = suitIndex;
                    ptr[rowPtr][1] = rankIndex;
                    rowPtr++;
                }
            }
        }
    }
    return ptr;
}

int*** dealingForHands(int deck[SUITS][RANKS], int n) {
    int** ptrPlayingCard = new int*[TOTALCARDS];
    for (int totalIndex = 0; totalIndex < TOTALCARDS; totalIndex++) {
        ptrPlayingCard[totalIndex] = new int[NUMDESCRIP];
    }
    
    ptrPlayingCard = playingCard(deck);

    int*** ptr = new int**[n];
    for (int playerIndex = 0; playerIndex < n; playerIndex++) {
        ptr[playerIndex] = new int* [NUMCARDS];
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            ptr[playerIndex][cardIndex] = new int[NUMDESCRIP];
        }
    }

    int m = 0, temp; 
    for (int playerIndex = 0; playerIndex < n; playerIndex++) {
        temp = m;
        for (int i = 0; i < NUMCARDS; i++) {
            ptr[playerIndex][i][0] = ptrPlayingCard[m][0];
            ptr[playerIndex][i][1] = ptrPlayingCard[m][1];
            m += n;
        }
        m = temp + 1;
    }

    for (int i = 0; i < TOTALCARDS; i++) {
        delete ptrPlayingCard[i];
    }
    delete[]ptrPlayingCard;
    return ptr;
}

//update 5:28, 22/04/2020
int getStatusOfHand(int** hand) {
	if (isStraightFlush(hand)) 
		return 8;
	if (isFourOfAKind(hand)) 
		return 7;
	if (isFullHouse(hand)) 
		return 6;
	if (isFlush(hand)) 
		return 5;
	if (isStraight(hand)) 
		return 4;
	if (isThreeOfAKind(hand)) 
		return 3;
	if (isTwoPairs(hand)) 
		return 2;
	if (isPair(hand)) 
		return 1;
	return 0;
} 

// sử dụng một mảng hai chiều kích thước 5x2 để lưu bài của một người để tính điểm, khởi tạo một mảng 1D để lưu kết quả, trong đó vị trí 0 trả về -1, lí do thứ hạng i thì ở ô a[i];
int* rankingHands(int*** hands, int n) {
    //creat a 1D-array to point rank of n player
    int* ptrPoint = new int[n + 1];
    ptrPoint[0] = -1;

    //creat a 1D-array to point rank of n player
    int* ptrRank = new int[n + 1];
    ptrRank[0] = -1;

    int** tempHand = new int* [NUMCARDS];
    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        tempHand[cardIndex] = new int[NUMDESCRIP];
    }

    for (int peopleIndex = 0; peopleIndex < n; peopleIndex++) {
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            tempHand[cardIndex][0] = hands[peopleIndex][cardIndex][0];
            tempHand[cardIndex][1] = hands[peopleIndex][cardIndex][1];
        }
        ptrPoint[peopleIndex + 1] = (int)getStatusOfHand(tempHand);
        ptrRank[peopleIndex + 1] = peopleIndex + 1;
    }

    for (int i = 2; i < n + 1; i++) {
        for (int j = n; j >= i; j--) {
            if (ptrPoint[j] > ptrPoint[j - 1]) {
                swap(ptrPoint[j], ptrPoint[j - 1]);
                swap(ptrRank[j], ptrRank[j - 1]);
            }
        }
    }

    delete[] ptrPoint;
    //delete allocation dynamic array
    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        delete tempHand[cardIndex];
    }
    delete[] tempHand;
    return ptrRank;
}
// 
int* sumOfS(int*** hands, int n) {
    //creat a 1D-array to point rank of n player
    int* ptrPoint1 = new int[n + 1];
    ptrPoint1[0] = 0;

    int** tempHand1 = new int* [NUMCARDS];
    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        tempHand1[cardIndex] = new int[NUMDESCRIP];
    }

    for (int peopleIndex = 0; peopleIndex < n; peopleIndex++) {
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            tempHand1[cardIndex][0] = hands[peopleIndex][cardIndex][0];
            tempHand1[cardIndex][1] = hands[peopleIndex][cardIndex][1];
        }
        ptrPoint1[peopleIndex + 1] = (int)getStatusOfHand(tempHand1);
    }

    //delete allocation dynamic array
    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        delete tempHand1[cardIndex];
    }
    delete[] tempHand1;
    return ptrPoint1;
}

int* evaluateHands(int deck[SUITS][RANKS], int n, int s) {    
    int*** ptr1 = new int** [n];
    for (int playerIndex = 0; playerIndex < n; playerIndex++) {
        ptr1[playerIndex] = new int* [NUMCARDS];
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            ptr1[playerIndex][cardIndex] = new int[NUMDESCRIP];
        }
    }

    int* ptrResult = new int[n + 1];
    for (int peopleIndex = 0; peopleIndex <= n; peopleIndex++) {
        ptrResult[peopleIndex] = 0;
    }

    for (int timesLoop = 0; timesLoop < s; timesLoop++) {
        shuffleCard(deck);
        ptr1 = dealingForHands(deck, n);
        int* ptrRank1 = sumOfS(ptr1, n);
        for (int peopleIndex = 1; peopleIndex <= n; peopleIndex++) {
            ptrResult[peopleIndex] += ptrRank1[peopleIndex]; 
        }
        delete[]ptrRank1;
    }
    cout << endl;

    //
    for (int playerIndex = 0; playerIndex < n; playerIndex++) {
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            delete ptr1[playerIndex][cardIndex];
        }
        delete ptr1[playerIndex];
    }
    delete[] ptr1;
    return ptrResult;
}