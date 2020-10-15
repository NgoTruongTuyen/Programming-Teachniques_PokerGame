#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const int SUITS = 4;
const int RANKS = 13;
const int NUMCARDS = 5;
const int TOTALCARDS = 52;
const int NUMDESCRIP = 2;

using namespace std;

void isMenu();
// I.1 Card shuffling & Dealing
void shuffleCard(int deck[][RANKS]);
bool checkValueofShuffleCard(int valueArray[], int elements, int number);
void printCardsShuffling(int deck[][RANKS], const char* suits[], const char* ranks[]);

// I.2 Card game: Five-card Poker

// one player only

// a.  A PokerGame that distributes cards to a player. The resulting array stores
// five cards assigned to the player.Each card is represented by a 2 - D
// array containing the row and column indices of the matrix deck
int** dealingForHand(int deck[SUITS][RANKS]);

// b. A PokerGame that prints out five cards assigned to a player. The 2-D
// array hands stores the five cards of the player
void printHand(int** hand, const char* suits[], const char* faces[]);
// 
int** createHandTest(int deck[SUITS][RANKS], int a[]);
// d. A PokerGame that checks whether a hand contains Four of a kind

void sortByBubbleSort(int** hand);
//kiểm tra trùng
///
bool isSequentialRank(int** hand);

int isFourOfAKind(int** hand);

// e. A PokerGame that checks whether a hand contains Full house
int isFullHouse(int** hand);

//f. A PokerGame that checks whether a hand contains Flush
int isFlush(int** hand);

// g. A PokerGame that checks whether a hand contains Straight
int isStraight(int** hand);

// h. A PokerGame that checks whether a hand contains Straight flush
int isStraightFlush(int** hand);

// i. A PokerGame that checks whether a hand contains Three of a kind
int isThreeOfAKind(int** hand);

// j. A PokerGame that checks whether a hand contains Two pairs
int isTwoPairs(int** hand);

// k. A PokerGame that checks whether a hand contains Pair
int isPair(int** hand);

// l. A PokerGame that returns the value of the highest card
int getHighestCard(int** hand);
void rankHand(int** hand); 
// N player 

// a. A PokerGame that distributes cards to n players.
int*** dealingForHands(int deck[SUITS][RANKS], int n);
// b. A PokerGame that returns the hand - ranking of five cards(8 if there is straightflush and so on decreasing, 0 if they do not fall into any hand - ranking category)
int getStatusOfHand(int** hand);
// c. A PokerGame that ranks n players in one turnand returns an array of n
// elements such that the player ith is in the rank a[i]
int* rankingHands(int*** hands, int n);
// d. For s times of dealing cards, write a PokerGame that calculate the sum of
// scores of n playersand congratulate the winner.
int* evaluateHands(int deck[SUITS][RANKS],  int n, int s);
//3
int** playingCard(int deck[SUITS][RANKS]);
void machineVsPlayer(int deck[SUITS][RANKS], const char* suits[], const char* ranks[], int n);

//4
void isDealer(int deck[SUITS][RANKS], const char* suits[], const char* ranks[]); 