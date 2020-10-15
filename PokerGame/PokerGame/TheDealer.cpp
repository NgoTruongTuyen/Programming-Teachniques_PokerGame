#include "PokerGame.h"

void isDealer(int deck[SUITS][RANKS], const char* suits[], const char* ranks[]) {
    int*** dealer = dealingForHands(deck, 2);

    int playerPoint = 0, dealerPoint = 0;
    int** hand2 = new int* [NUMCARDS];
    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        hand2[cardIndex] = new int[NUMDESCRIP];
    }
    for (int peopleIndex = 0; peopleIndex < 2; peopleIndex++) {

        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            hand2[cardIndex][0] = dealer[peopleIndex][cardIndex][0];
            hand2[cardIndex][1] = dealer[peopleIndex][cardIndex][1];
        }
        if (peopleIndex == 0) {
            cout << "Dealer's card: " << endl;
            printHand(hand2, suits, ranks);
            cout << endl;
            dealerPoint = (int)getStatusOfHand(hand2);
            cout << "Dealer's point: " << (int)getStatusOfHand(hand2) << endl;

        }
        else {
            cout << "Player's card: " << endl;
            printHand(hand2, suits, ranks);
            cout << endl;
            playerPoint = (int)getStatusOfHand(hand2);
            cout << "Player's point: " << (int)getStatusOfHand(hand2) << endl;
        }
    }

    int** playingCard1 = playingCard(deck);

    int co = 0, count = 11;
    int choose2 = 0, choose3 = 0;
    // trường hợp chọn một là nào đó ngẫu nhiên
    cout << "-----------------------" << endl;
    cout << "The dealer: " << endl;

    int choose1 = 0;
    cout << "----------" << endl;
    cout << "1. Random replacement." << endl;
    cout << "2. Don't take!" << endl;

    do {
        cout << "Your option: ";
        cin >> choose1;
        cout << "---------------------------------------------" << endl;

        if (choose1 < 1 || choose1 > 2) {
            cout << "Invalid option. Please choose a option from 1 to 2." << endl;
        }
    } while (choose1 < 1 || choose1 > 2);

    if (choose1 == 2) {
        if (dealerPoint >= playerPoint) {
            cout << "The machine is win!" << endl;
        }
        else {
            cout << "The player is win!" << endl;
        }
    }
    else {
        do {
            cout << "You want to discard the number of card: " << endl;
            cin >> choose2;
            cout << "You want to get the the number of card from " << count++ << " to " << 52 << " in deck of card" << endl;
            cin >> choose3;

            dealer[0][choose2 - 1][0] = playingCard1[choose3 - 1][0];
            dealer[0][choose2 - 1][1] = playingCard1[choose3 - 1][1];
            for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                hand2[cardIndex][0] = dealer[0][cardIndex][0];
                hand2[cardIndex][1] = dealer[0][cardIndex][1];
            }

            cout << "The dealer's card: " << endl;
            printHand(hand2, suits, ranks);
            cout << endl;
            dealerPoint = (int)getStatusOfHand(hand2);

            cout << "The dealer's point: " << dealerPoint << endl;
            char select3 = 'Y';
            do {
                if (co == 2) {
                    cout << "You don't exchange card!" << endl;
                    co++;
                    break;
                }

                cout << "Are you exchange card again? (Y/N)                     " << endl;
                cin >> select3;

                if (select3 != 'Y' && select3 != 'y' && select3 != 'N' && select3 != 'n') {
                    cout << "Please enter the Y(Yes) or N(No)!" << endl;
                }

                if (select3 == 'N' || select3 == 'n') {
                    co = 10;
                }

                if (select3 == 'Y' || select3 == 'y') {
                    co++;
                }

            } while (select3 != 'Y' && select3 != 'y' && select3 != 'N' && select3 != 'n');
        } while (co < 3);
    }

    //The player 
    cout << "-----------------------" << endl;
    cout << "The player: " << endl;
    choose1 = 0;
    cout << "----------" << endl;
    cout << "1. Random replacement." << endl;
    cout << "2. Don't take!" << endl;

    do {
        cout << "Your option: ";
        cin >> choose1;
        cout << "---------------------------------------------" << endl;

        if (choose1 < 1 || choose1 > 2) {
            cout << "Invalid option. Please choose a option from 1 to 2." << endl;
        }
    } while (choose1 < 1 || choose1 > 2);

    if (choose1 == 2) {
        if (dealerPoint >= playerPoint) {
            cout << "The machine is win!" << endl;
        }
        else {
            cout << "The player is win!" << endl;
        }
    }
    else {
        choose2 = 0;
        choose3 = 0;

        do {
            cout << "You want to discard the number of card: " << endl;
            cin >> choose2;
            cout << "You want to get the the number of card from " << count++ << " to " << 52 << " in deck of card" << endl;
            cin >> choose3;

            dealer[1][choose2 - 1][0] = playingCard1[choose3 - 1][0];
            dealer[1][choose2 - 1][1] = playingCard1[choose3 - 1][1];
            for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                hand2[cardIndex][0] = dealer[1][cardIndex][0];
                hand2[cardIndex][1] = dealer[1][cardIndex][1];
            }

            cout << "The player's card: " << endl;
            printHand(hand2, suits, ranks);
            cout << endl;
            playerPoint = (int)getStatusOfHand(hand2);

            cout << "The player's point: " << playerPoint << endl;
            char select3 = 'Y';

            do {
                if (co == 2) {
                    cout << "You don't exchange card!" << endl;
                    co++;
                    break;
                }

                cout << "Are you exchange card again? (Y/N)                     " << endl;
                cin >> select3;
                if (select3 != 'Y' && select3 != 'y' && select3 != 'N' && select3 != 'n') {
                    cout << "Please enter the Y(Yes) or N(No)!" << endl;
                }
                if (select3 == 'N' || select3 == 'n') {
                    co = 10;
                }
                if (select3 == 'Y' || select3 == 'y') {
                    co++;
                }

            } while (select3 != 'Y' && select3 != 'y' && select3 != 'N' && select3 != 'n');
        } while (co < 3);
    }

    // deallocated memory
    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        delete hand2[cardIndex];
    }
    delete[]hand2;

    // deallocated memory
    for (int playerIndex = 0; playerIndex < 2; playerIndex++) {
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            delete dealer[playerIndex][cardIndex];
        }
        delete dealer[playerIndex];
    }
    delete[] dealer;
}