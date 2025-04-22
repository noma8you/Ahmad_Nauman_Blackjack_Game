#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include "funs.h"
using namespace std;

string hit_or_stay(){
    string play;
    cout<<"HIT or STAY: "; //asks for player input
    cin>>play;
    while(play!="HIT"&&play!="STAY"){
        cout<<"Invalid input. Please type HIT or STAY: ";
        cin>>play;
    }
    return play;
}

void hit(string card[], vector<string> &player1){
    int deal;
    while(true){
        deal=rand()%52; //for random card dealing
        if(card[deal]=="X"){ //that card on the map will be marked with X, so it will not be picked again (removed from deck)
            continue;
        } else {
            player1.push_back(card[deal]);
            card[deal]="X";
            break;
        }
    }
}

void display_card_info(vector<string> &player1, int player1_bs, int player_number){
    if(player_number==0){
        cout<<"Dealer's cards reveal: "<<endl; //at the end, the dealers cards are revealed
    } else {
        cout<<"Player "<<player_number<<"'s card(s): "<<endl; //the player who's playing's cards
    }
    for(int i=0;i<player1.size();i++){
        print_card_ascii(player1[i]);
    }
    cout<<endl;
}

int bust_score(vector<string> &player1, int player1_bs, map<string, int> &card_value){
    string last_card = player1[player1.size()-1];
    if(last_card=="A"){ //if someone gets an Ace, they can manually pick the value
        int ace_value;
        if(player1.size()<=2){
            ace_value = 11;
        } else {
            cout<<"Pick Ace value (1 or 11): ";
            cin>>ace_value;
            while(ace_value!=1&&ace_value!=11){ //if the player inputs something other than 11 or 1
                cout<<"Invalid choice. Pick Ace value (1 or 11): ";
                cin>>ace_value;
            }
        }
        player1_bs+=ace_value; //adds ace value to the player's score
    } else {
        player1_bs+=card_value[last_card];
    }
    return player1_bs;
}

void determine_winner(int players_bs[], int players_in_game){
    vector<int> winners; //varaible for winner
    int ai_bs = players_bs[0];

    int best_score=-1;
    for(int i=1;i<=players_in_game;i++){
        if(players_bs[i]<=21&&players_bs[i]>best_score){
            best_score=players_bs[i];
        }
    }
    if(ai_bs<=21&&ai_bs>best_score){
        best_score=ai_bs;
    }

    for(int i=1;i<=players_in_game;i++){
        if(players_bs[i]==best_score){
            winners.push_back(i);
        }
    }
    if(ai_bs==best_score){
        winners.push_back(0);
    }

    if(winners.size()==0){ //if the game finds no one to win
        cout<<"Everyone went bust"<<endl;
    } else if(winners.size()==1){ 
        if(winners[0]==0){ //the Dealer is marked as player[0]
            cout<<"Dealer wins!"<<endl;
        } else {
            cout<<"Player "<<winners[0]<<" Wins"<<endl; //depending on which []. the player is determined
        }
    } else {
        cout<<"Tie between "; //if there are mmultiple winners (tie)
        for(int i=0;i<winners.size();i++){
            if(winners[i]==0){
                cout<<"Dealer";
            } else {
                cout<<"Player "<<winners[i];
            }
            if(i!=winners.size()-1){
                cout<<" and ";
            }
        }
        cout<<endl;
    }
}

void print_card_ascii(string card){
        cout<<"+-----+"<<endl; //top of the card     //SHOULD PRINT a card
    if(card=="10"){
        cout<<"|10   |"<<endl; //top number            
        cout<<"|     |"<<endl;
        cout<<"|   10|"<<endl; //bottom number
    } else {
        cout<<"|"<<card<<"    |"<<endl; //card lines
        cout<<"|     |"<<endl;
        cout<<"|    "<<card<<"|"<<endl;
    }
    cout<<"+-----+"<<endl; //bottom of card
}
