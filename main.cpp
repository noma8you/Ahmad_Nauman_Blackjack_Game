#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "funs.h"
using namespace std;

int main(){
    srand(time(NULL)); //for random every time

    //initialize players and bust scores
    vector<string> players[5]; // 0 = dealer, 1 to 4 = players
    int players_bs[5] = {0}; // bust scores

    //create deck cards (Mr. Kwan's technique)
    string card[52] = {"A", "A", "A", "A", "2", "2", "2", "2", // all possible cards
                       "3", "3", "3", "3", "4", "4", "4", "4",
                       "5", "5", "5", "5", "6", "6", "6", "6",
                       "7", "7", "7", "7", "8", "8", "8", "8",
                       "9", "9", "9", "9", "10", "10", "10", "10",
                       "K", "K", "K", "K", "J", "J", "J", "J",
                       "Q", "Q", "Q", "Q"};

    // map card to value (Mr. Kwans technique)
    map<string, int> card_value = {{"A", -1}, {"2", 2}, {"3", 3}, // all card values
                                   {"4", 4}, {"5", 5}, {"6", 6},
                                   {"7", 7}, {"8", 8}, {"9", 9},
                                   {"10", 10}, {"J", 10}, {"Q", 10}, {"K", 10}};

    int players_in_game; //to know how many players in game
    cout << "Number of players (1-4): ";
    cin >> players_in_game;

    // Initial 2 cards each
    for (int i = 0; i <= players_in_game; i++) { 
        for (int j = 0; j < 2; j++) {
            hit(card, players[i]);
            players_bs[i] = bust_score(players[i], players_bs[i], card_value);
        }
    }
//GAMEPLAY
    // Players' turn
    for (int i = 1; i <= players_in_game; i++) {
        while (players_bs[i] < 21) {
            display_card_info(players[i], players_bs[i], i);
            cout << "Current score: " << players_bs[i] <<endl;
            string move = hit_or_stay();
            if (move == "HIT" || move == "hit") {
                hit(card, players[i]);
                players_bs[i] = bust_score(players[i], players_bs[i], card_value);
            } 
            else if(move=="STAY" || move=="stay") {
                display_card_info(players[i], players_bs[i], i);
                break;
            }
        }
        if (players_bs[i] > 21) {
            display_card_info(players[i], players_bs[i], i);
            cout<<"player's score: "<<players_bs[i]<<endl;
            cout << "Player " <<i<< " Goes bust" <<endl;
        }
    }

    // Dealer's turn
    while (players_bs[0]<17) {
        hit(card, players[0]);
        players_bs[0]=bust_score(players[0], players_bs[0], card_value);
    }
    display_card_info(players[0], players_bs[0], 0);
    cout <<"Dealer's final score: " <<players_bs[0] <<endl;
    if (players_bs[0] > 21) {
        cout <<"Dealer goes bust" <<endl;
    }

//RESULTS
determine_winner(players_bs, players_in_game);

    return 0;
}


