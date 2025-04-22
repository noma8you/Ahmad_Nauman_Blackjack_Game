#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include "funs.h"
using namespace std;

string hit_or_stay(){
    string play;
    cout<<"HIT or STAY: ";
    cin>>play;
    return play;
}

void hit(string card[], vector<string> &player1){
    int deal;
    while(true){
        deal=rand()%52;
        if(card[deal]=="X"){
            continue;
        }
        else{
            player1.push_back(card[deal]);
            card[deal]="X";
            break;
        }
    }
}

void display_card_info(vector<string> &player1, int player1_bs, int player_number){
    if(player1_bs<22){ //only shows if player isnt bust yet
        cout<<"Player "<<player_number<<"'s card(s): ";
        for(int i=0;i<player1.size();i++){
            cout<<player1[i]<<" ";
        }
        cout<<endl;
    }
}

int bust_score(vector<string> &player1, int player1_bs, map<string, int> &card_value){
    if(player1[player1.size()-1]=="A"){ //when player gets an ace
        int ace_value; //ace's value
        cout<<"Pick Ace value (1 or 11): ";
        cin>>ace_value;
        while(ace_value!=1&&ace_value!=11){
            cout<<"Invalid choice. Pick Ace value (1 or 11): "<<endl;
            cin>>ace_value;
        }
        player1_bs = ace_value + player1_bs; //add chosen Ace value
    } else {
        player1_bs += card_value[player1[player1.size()-1]]; //add the value of the latest card
    }
    return player1_bs;
}

// NEW WINNER FUNCTION
void determine_winner(int players_bs[], int players_in_game){
    vector<int> winners; //WHO WON
    int ai_bs = players_bs[1];

    //FIND HIGHEST SCORE NOT BUST
    int best_score = -1;
    for(int i = 0; i < players_in_game; i++){
        if(players_bs[i] <= 21 && players_bs[i] > best_score){
            best_score = players_bs[i];
        }
    }
    if(ai_bs <= 21 && ai_bs > best_score){
        best_score = ai_bs;
    }

    //WHO GOT BEST SCORE
    for(int i = 0; i < players_in_game; i++){
        if(players_bs[i] == best_score){
            winners.push_back(i + 1); //+1 because players are numbered starting from 1
        }
    }
    if(ai_bs == best_score){
        winners.push_back(0); //0 MEANS AI
    }

    //PRINT RESULTS
    if(winners.size() == 0){
        cout<<"Everyone went bust"<<endl;
    } else if(winners.size() == 1){
        if(winners[0] == 0){
            cout<<"Dealer wins!"<<endl;
        } else {
            cout<<"Player "<<winners[0]<<" wins!"<<endl;
        }
    } else {
        cout<<"Tie between ";
        for(int i = 0; i < winners.size(); i++){ //for multiple winners
            if(winners[i] == 0){
                cout<<"Dealer"; //in case of a tie with the dealer
            } else {
                cout<<"Player "<<winners[i]; //which player wins
            }
            if(i != winners.size() - 1){
                cout<<" and ";
            }
        }
    }
}

//VISUALS
void print_card_ascii(string card){
    cout<<"+-----+"<<endl;
    if(card=="10"){
        cout<<"|10   |"<<endl;
        cout<<"|     |"<<endl;
        cout<<"|   10|"<<endl;
    } else {
        cout<<"|"<<card<<"    |"<<endl;
        cout<<"|     |"<<endl;
        cout<<"|    "<<card<<"|"<<endl;
    }
    cout<<"+-----+"<<endl;
}