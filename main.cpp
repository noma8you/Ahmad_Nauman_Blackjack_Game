#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "funs.h"
using namespace std;

int main()
{
    string play;
    int players_in_game;

    srand(time(NULL)); //for random every time
    vector<string> players[4];
    int players_bs[4]={0,0,0,0}; //possible amount of players stored

    string card[52]={"A","A","A","A","2","2","2","2", //all possible cards
                     "3","3","3","3","4","4","4","4",
                     "5","5","5","5","6","6","6","6",
                     "7","7","7","7","8","8","8","8",
                     "9","9","9","9","10","10","10","10",
                     "K","K","K","K","J","J","J","J",
                     "Q","Q","Q","Q"};

    map<string,int>card_value={{"A",-1},{"2",2},{"3",3}, //all card values
                                {"4",4},{"5",5},{"6",6},
                                {"7",7},{"8",8},{"9",9},
                                {"10",10},{"J",10},{"Q",10},{"K",10}};

    //Getting number of players
    cout<<"Enter number of players (1-4): ";
    cin>>players_in_game;
    if(players_in_game<1||players_in_game>4){
        cout<<"Invalid number of players."<<endl;
        return 0;
    }

    int current_player=0;
    //Dealing 2 cards to start
    for(int i=0;i<players_in_game;i++){
        hit(card,players[i]);
        players_bs[i]=bust_score(players[i],players_bs[i],card_value);
        hit(card,players[i]);
        players_bs[i]=bust_score(players[i],players_bs[i],card_value);
    }

    //INITIAL DEAL: 2 cards for dealer (AI)
    hit(card,players[1]);
    players_bs[1]=bust_score(players[1],players_bs[1],card_value);
    hit(card,players[1]);
    players_bs[1]=bust_score(players[1],players_bs[1],card_value);

    cout<<"Dealer's revealed card: "<<players[1][0]<<endl;
    
    //GAMEPLAY CODE
    while(true){
        cout<<"Player "<<(current_player+1)<<"'s turn."<<endl;

        for(int j=0;j<players[current_player].size();j++){
            print_card_ascii(players[current_player][j]);
        }
        cout<<"Total: "<<players_bs[current_player]<<endl;

        play=hit_or_stay();

        if(play=="STAY"){
            current_player++;
            if(current_player>=players_in_game){
                break;
            }
            continue;
        }

        if(play=="HIT"){
            hit(card,players[current_player]);
            string last_card=players[current_player].back();
            print_card_ascii(last_card);
            // If the last card is Ace, manually handle its value
            if(last_card == "A") {
                char ace_choice;
                cout << "You got an Ace! Do you want it as 1 or 11? (Enter 1 or 11): ";
                cin >> ace_choice;
                if(ace_choice == '1') {
                    players_bs[current_player] += 1;
                } else if(ace_choice == '11') {
                    players_bs[current_player] += 11;
                } else {
                    cout << "Invalid input. Setting Ace value to 1." << endl;
                    players_bs[current_player] += 1; // default to 1 if invalid
                }
            } else {
                players_bs[current_player] = bust_score(players[current_player],players_bs[current_player],card_value);
            }
            display_card_info(players[current_player],players_bs[current_player],current_player+1);
        }

        if(players_bs[current_player]>21){
            cout<<"Player "<<(current_player+1)<<" BUST!"<<endl;
            current_player++;
            if(current_player>=players_in_game){
                break;
            }
        }
    }

    while(players_bs[1]<17){
        hit(card,players[1]);
        players_bs[1]=bust_score(players[1],players_bs[1],card_value);
    }

    for(int i=0;i<players_in_game;i++){
        display_card_info(players[i],players_bs[i],i+1);
        cout<<"Player "<<(i+1)<<"'s score: "<<players_bs[i]<<endl;
    }
    cout<<"AI's cards: ";
    display_card_info(players[1],players_bs[1],2);
    cout<<"AI's score: "<<players_bs[1]<<endl;
    //END OF GAME 
    determine_winner(players_bs,players_in_game);

    return 0;
}
