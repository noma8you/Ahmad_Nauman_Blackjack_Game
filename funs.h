#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>  // FOR rand() AND srand()
#include <ctime>    // FOR time()

using namespace std;
string hit_or_stay();
void hit(string card[], vector<string> &player1);
void display_card_info(vector<string> &player1, int player1_bs, int player_number); //updated for player number
int bust_score(vector<string> &player1, int player1_bs, map<string, int> &card_value);
void determine_winner(int players_bs[], int players_in_game); //check winner
void print_card_ascii(string card); //for visuals ascii art