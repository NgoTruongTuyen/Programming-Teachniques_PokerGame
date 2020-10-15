#include "PokerGame.h"

int main() {
    int deck[SUITS][RANKS] = { 0 };
    const char* suits[SUITS] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* ranks[RANKS] = { "Ace", "Two", "Three", "Four", "Five",
    "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    shuffleCard(deck);
   
    cout << "The cards of deck: " << endl;
    printCardsShuffling(deck, suits, ranks);
    
    cout << "---------------------------------------------" << endl;
    cout << "=============================================" << endl;
    
    int flag = 1;
    while (flag == 1) {
        isMenu();
        int numChoose;
    
        do {
            cout << " Your option: ";
            cin >> numChoose;
            cout << "---------------------------------------------" << endl;
        
            if (numChoose < 1 || numChoose > 6) {
                cout << "Invalid option. Please choose a option from 1 to 4." << endl;
            }
        } while (numChoose < 1 || numChoose > 6);
        
        switch (numChoose) {
        case 1: {
            char select1 = 'Y';
            
            while (select1 == 'Y' || select1 == 'y') {
                system("cls");
                cout << "=============== Single Player ===============" << endl;
                //Creat a matrix 5 * 2 to store the five card of the player. 
                int** ptrHand = new int* [NUMCARDS];
                
                for (int i = 0; i < NUMCARDS; i++) {
                    ptrHand[i] = new int[NUMDESCRIP];
                }
                
                int* a = new int[NUMCARDS];
                
                cout << "Please test the deck: " << endl;
                
                for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                    cout << "Enter the " << cardIndex + 1 << "(th) card: ";
                    cin >> a[cardIndex];
                }
                
                cout << "The cards entered: ";
                printHand(createHandTest(deck, a), suits, ranks);
                cout << endl;
                
                ptrHand = dealingForHand(deck);
                cout << "The your cards: ";
                printHand(ptrHand, suits, ranks);
                cout << endl;
                
                rankHand(ptrHand);
                cout << endl;
                
                for (int i = 0; i < NUMCARDS; i++) {
                    delete ptrHand[i];
                }
                delete[]ptrHand;
                
                cout << "---------------------------------------------" << endl;
                do {
                    cout << "Are you continue? (Y/N)                     " << endl;
                    cin >> select1;
                    
                    if (select1 != 'Y' && select1 != 'y' && select1 != 'N' && select1 != 'n') {
                        cout << "Please enter the Y(Yes) or N(No)!" << endl;
                    }
                } while (select1 != 'Y' && select1 != 'y' && select1 != 'N' && select1 != 'n');
            }
            break;
        }
        case 2: {
            char select2 = 'Y';
            
            while (select2 == 'Y' || select2 == 'y') {
                system("cls");
                cout << "============== Multiple Player ==============" << endl;
                int n;
                
                do {
                cout << "Please enter the number of player(n <= 10): ";                    
                    cin >> n;
                    
                    if (n > 10) {
                        cout << "Invalid value.!" << endl;
                    }
                } while (n > 10);

                //creat a matrix
                int*** hands = new int** [n];
                for (int playerIndex = 0; playerIndex < n; playerIndex++) {
                    hands[playerIndex] = new int* [NUMCARDS];
                    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                        hands[playerIndex][cardIndex] = new int[NUMDESCRIP];
                    }
                }
                
                hands = dealingForHands(deck, n);
                //printCardsShuffling(deck, suits, ranks);
                cout << endl;
                
                int** hand2 = new int* [NUMCARDS];
                for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                    hand2[cardIndex] = new int[NUMDESCRIP];
                }
                
                cout << "The rank of 1 turn: " << endl;
                for (int peopleIndex = 0; peopleIndex < n; peopleIndex++) {    
                    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                        hand2[cardIndex][0] = hands[peopleIndex][cardIndex][0];
                        hand2[cardIndex][1] = hands[peopleIndex][cardIndex][1];
                    }

                    printHand(hand2, suits, ranks);
                    cout << endl;
                    cout << "The " << peopleIndex + 1 << "(th) player's points: " <<(int)getStatusOfHand(hand2) << endl;
                }
                
                for (int i = 0; i < NUMCARDS; i++) {
                    delete hand2[i];
                }
                delete[] hand2;
                
                int* a = rankingHands(hands, n);
                for (int i = 1; i < n + 1; i++) {
                    cout << "The index "<< i<< " (th) is "<< a[i] << endl;
                }
                cout << endl;
                
                int s;
                cout << "Please enter the number times of dealing card: " << endl;
                cin >> s;
                
                int* b = evaluateHands(deck, n, s);
                for (int i = 1; i <= n; i++) {
                    cout << "People " << i << " (th) is " << b[i] << endl;
                }

                int max = b[1];
                int indexP = 1;
                for (int i = 2; i <= n; i++) {
                    if (b[i] > max) {
                        max = b[i];
                        indexP = i;
                    }
                }
                
                cout << "the winer is " << indexP << " with " << max << " point" << endl;
                //allowcated 3D
                for (int playerIndex = 0; playerIndex < n; playerIndex++) {
                    for (int cardIndex = 0; cardIndex < NUMCARDS; cardIndex++) {
                        delete hands[playerIndex][cardIndex];
                    }
                    delete hands[playerIndex];
                }
                delete[] hands;

                cout << "---------------------------------------------" << endl;
                do {
                    cout << "Are you continue? (Y/N)                     " << endl;
                    cin >> select2;
                
                    if (select2 != 'Y' && select2 != 'y' && select2 != 'N' && select2 != 'n') {
                        cout << "Please enter the Y(Yes) or N(No)!" << endl;
                    }
                } while (select2 != 'Y' && select2 != 'y' && select2 != 'N' && select2 != 'n');
            }
            break;
        }
        case 3: {
            char select3 = 'Y';
            while (select3 == 'Y' || select3 == 'y') {
                system("cls");
                cout << "=============== Man vs Machine ===============" << endl;
                int n;
                
                do {
                cout << "Please enter the number of player(n < 10): ";                    
                    cin >> n;
                    
                    if (n > 9) {
                        cout << "Invalid value.!" << endl;
                    }
                } while (n > 9);
                machineVsPlayer(deck, suits, ranks, n);

                cout << "---------------------------------------------" << endl;
                do {
                    cout << "Are you continue? (Y/N)                     " << endl;
                    cin >> select3;

                    if (select3 != 'Y' && select3 != 'y' && select3 != 'N' && select3 != 'n') {
                        cout << "Please enter the Y(Yes) or N(No)!" << endl;
                    }
                } while (select3 != 'Y' && select3 != 'y' && select3 != 'N' && select3 != 'n');
            }
            break;
        }
        case 4: {
            char select4 = 'Y';
            while (select4 == 'Y' || select4 == 'y') {
                system("cls");
                cout << "=============== Man vs Machine ===============" << endl;
                isDealer(deck, suits, ranks);
                cout << "---------------------------------------------" << endl;

                do {
                    cout << "Are you continue? (Y/N)                     " << endl;
                    cin >> select4;

                    if (select4 != 'Y' && select4 != 'y' && select4 != 'N' && select4 != 'n') {
                        cout << "Please enter the Y(Yes) or N(No)!" << endl;
                    }
                } while (select4 != 'Y' && select4 != 'y' && select4 != 'N' && select4 != 'n');
            }
            break;
        } 
        case 5: {
            char stop;
            system("cls");
            cout << "The copyright: " << endl; 
            cout << "       Tran Duc Duy and Ngo Truong Tuyen." << endl;
            cout << "Instructor: " << endl;
            cout << "       Teacher: Bui Huy Thong." << endl;
            cout << "       Teacher: Nguyen Ngoc Thao." << endl;
            cout << "---------------------------------------------" << endl;
            cin.ignore();
            stop = getchar();
            break;
        }
        case 6: {
            system("cls");
            flag = 0;
            cout << "Thanks for using our game!" << endl;
            cout << endl;
            cout << endl;
            break;
        }
        default:
            cout << "Invalid option." << endl;
            break;
        }
		system("cls");
    }

    return 0;
}
