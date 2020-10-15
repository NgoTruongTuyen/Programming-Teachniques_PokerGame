#include "PokerGame.h"

void machineVsPlayer(int deck[SUITS][RANKS], const char* suits[], const char* ranks[], int n) {
    int*** machine = dealingForHands(deck, n + 1);

    int machinePoint = 0;
    int** hand2 = new int* [NUMCARDS];
    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        hand2[cardIndex] = new int[NUMDESCRIP];
    }

    int* point = new int[n]; 
    for (int peopleIndex = 0; peopleIndex <= n; peopleIndex++) {
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            hand2[cardIndex][0] = machine[peopleIndex][cardIndex][0];
            hand2[cardIndex][1] = machine[peopleIndex][cardIndex][1];
        }
        
        if (peopleIndex == 0) {
            cout << " The machine's card: ";
            printHand(hand2, suits, ranks);
            //The machine's position is 0
            point[0] = (int)getStatusOfHand(hand2);
            machinePoint = point[0];
            cout << endl;
            cout << " The machine's point: " << point[0] << endl;
        } 
        else {
            cout << " The "<< peopleIndex << "(th) player's card: ";
            printHand(hand2, suits, ranks);
            //The machine's position is 0
            point[peopleIndex] = (int)getStatusOfHand(hand2);
            cout << endl;
            cout << " The " << peopleIndex << "(th) player's point: " << point[peopleIndex] << endl;
        }
        
    }
 
    int choose1;
    cout << "----------" << endl;
    cout << "1. Random replacement." << endl;
    cout << "2. Replace to get better situation." << endl;
    cout << "3. Don't take!" << endl;
    
    do {
        cout << " Your option: ";
        cin >> choose1;
        cout << "---------------------------------------------" << endl;
        
        if (choose1 < 1 || choose1 > 3) {
            cout << "Invalid option. Please choose a option from 1 to 3." << endl;
        }
    } while (choose1 < 1 || choose1 > 3);
    
    
    //if choose1 == 3 will return point and stop
    if (choose1 == 3) {
        int max = machinePoint;
        int positionPlayer = 0;
        for (int pointIndex = 1; pointIndex <= n; pointIndex++) {
            
            if (max < point[pointIndex]) {
                max = point[pointIndex];
                positionPlayer = pointIndex;
            }
        }
        
        if (max == machinePoint) {
            cout << "The machine is win!" << endl;
        } 
        else {
            cout << "The " << positionPlayer << "(th) player is win!" << endl;
        }
    }

    // get Point
    int** playingCard1 = playingCard(deck);
    int co = 0, count = (n + 1) * NUMCARDS + 1;
    int choose2 = 0, choose3 = 0;
    // trường hợp chọn một là nào đó ngẫu nhiên
    if (choose1 == 1) {
        
        do {
            cout << "You want to discard the number of card(1-5): " << endl;
            cin >> choose2;
            cout << "You want to get the the number of card from " << count << " to " << 52 << " in deck of card" << endl;
            cin >> choose3;

            machine[0][choose2 - 1][0] = playingCard1[choose3 - 1][0];
            machine[0][choose2 - 1][1] = playingCard1[choose3 - 1][1];
            for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                hand2[cardIndex][0] = machine[0][cardIndex][0];
                hand2[cardIndex][1] = machine[0][cardIndex][1];
            }

            cout << "----------" << endl;
            cout << " The machine's card: " << endl;
            machinePoint = (int)getStatusOfHand(hand2);
            printHand(hand2, suits, ranks);
            cout << endl;

            cout << " The machine's point: " << (int)getStatusOfHand(hand2) << endl;
            for (int peopleIndex = 1; peopleIndex <= n; peopleIndex++) {
                cout << " The " << peopleIndex << "(th) player's point: " << point[peopleIndex] << endl;
            }

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
        
        int max = machinePoint;
        int positionPlayer = 0;
        for (int pointIndex = 1; pointIndex <= n; pointIndex++) {
            if (max < point[pointIndex]) {
                max = point[pointIndex];
                positionPlayer = pointIndex;
            }
        }

        if (max == machinePoint) {
            cout << "The machine is win!" << endl;
        } 
        else {
            cout << "The " << positionPlayer << "(th) player is win!" << endl;
        }   
    } 
    else if (choose1 == 2) {//The machine get better situation.
        int** playingCard2 = playingCard(deck);
        int count2 = (n + 1)* NUMCARDS + 1;
    
        for (int i = count2; i <= TOTALCARDS; i++) {
            cout << i << " (" << suits[playingCard2[i - 1][0]] << ", " << ranks[playingCard2[i - 1][1]]<<")" << endl;           
        }
        choose2 = 0;
        choose3 = 0;
        
        do {
            cout << "You want to discard the number of card(1-5): " << endl;
            cin >> choose2;
            cout << "You want to get the the number of card from " << count2 << " to " << 52 << " in deck of card" << endl;
            cin >> choose3;
        
            cout << "---------------------------------------------" << endl;
            machine[0][choose2 - 1][0] = playingCard1[choose3 - 1][0];
            machine[0][choose2 - 1][1] = playingCard1[choose3 - 1][1];
            for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                hand2[cardIndex][0] = machine[0][cardIndex][0];
                hand2[cardIndex][1] = machine[0][cardIndex][1];
            }
            
            cout << " The machine's card: " << endl;
            machinePoint = (int)getStatusOfHand(hand2);
            printHand(hand2, suits, ranks);
            cout << endl;
            
            cout << " The machine's point: " << (int)getStatusOfHand(hand2) << endl;
            for (int peopleIndex = 1; peopleIndex <= n; peopleIndex++) {
                cout << "The " << peopleIndex << "(th) player's point: " << point[peopleIndex] << endl;
            }
            
            cout << "----------" << endl;
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
        
        //Result
        int max = machinePoint;
        int positionPlayer = 0;
        for (int pointIndex = 1; pointIndex <= n; pointIndex++) {
            if (max < point[pointIndex]) {
                max = point[pointIndex];
                positionPlayer = pointIndex;
            }
        }
        
        if (max == machinePoint) {
            cout << " The machine is win!" << endl;
        } 
        else {
            cout << "The " << positionPlayer << "(th) player is win!" << endl;
        }
        
        for (int cardIndex = 0; cardIndex < TOTALCARDS; cardIndex++) {
            delete playingCard2[cardIndex];
        }
        delete[]playingCard2;
    }

    for (int cardIndex = 0; cardIndex < TOTALCARDS; cardIndex++) {
        delete playingCard1[cardIndex];
    }
    delete[]playingCard1;
    delete[] point;

    // deallocated memory
    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
        delete hand2[cardIndex];
    }
    delete[]hand2;

    // deallocated memory
    for (int playerIndex = 0; playerIndex < 2; playerIndex++) {
        for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
            delete machine[playerIndex][cardIndex];
        }
        delete machine[playerIndex];
    }
    delete[] machine;
}