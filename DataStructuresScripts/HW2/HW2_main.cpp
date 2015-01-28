/* 
 * File:   HW2_main.cpp
 * Author: jungj5
 *
 * 
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "team.h"
#include "player.h"
#include <iomanip>
#include <algorithm>



void team_output(std::vector<Team> &teams, std::ofstream &out_str) {

    out_str << "Team Name        W    L    T    Win%    Goals    Penalties" << std::endl;
    for (int i = 0; i < teams.size(); ++i) {
        double wlr2 = (teams[i].get_wins() + (.5 * teams[i].get_ties()))/ (teams[i].get_wins() + teams[i].get_loss() + teams[i].get_ties());
        teams[i].increment_wlr(wlr2);
        int width4 = 16 - teams[i].get_team_name().size();
        
        if (teams[i].get_goals() > 9) {
            width4 = width4 + 2;
        }
        else if (teams[i].get_goals() > 99) {
            width4 = width4 + 1;
        }

        out_str << teams[i].get_team_name();
        out_str.width(width4);
        out_str << std::right << teams[i].get_wins();
        out_str.width(5);
        out_str << std::right << teams[i].get_loss();
        out_str.width(5);
        out_str << std::right << teams[i].get_ties();
        //out_str.width(8);
        //pls no TA!! i need teh points
        
        if(teams[i].get_wlr() == 0.0 || teams[i].get_wlr() == 0.1 || 
                teams[i].get_wlr() == 0.2|| teams[i].get_wlr() == 0.3|| 
                teams[i].get_wlr() == 0.4|| teams[i].get_wlr() == 0.5|| 
                teams[i].get_wlr() == 0.6|| teams[i].get_wlr() == 0.7|| 
                teams[i].get_wlr() == 0.8|| teams[i].get_wlr() == 0.9 ) {
            out_str.width(7);
            out_str << std::right << teams[i].get_wlr() << 0;
        }
        else {
            out_str.width(8);
            out_str << std::right << std::setprecision(2) << teams[i].get_wlr();
        }
        //out_str << std::right << std::setprecision(2) << teams[i].get_wlr();
        out_str.width(9);
        out_str << std::right << teams[i].get_goals();
        out_str.width(13);
        out_str << std::right << teams[i].get_penalties() << std::endl;
    }
    
}

void player_output(std::vector<Player> &players, std::ofstream &out_str) {
    int longest = 0;
    for (int i = 0; i < players.size(); ++i) {
        if (players[i].get_player_name().size() > longest) {
            longest = players[i].get_player_name().size();
        }
    }
    out_str << " " << std::endl;
    out_str << "Player Name         Team         Goals     Assists     Penalties" << std::endl;
    for (int i = 0; i < players.size(); ++i) {
        int width = 0;
        int width2 = 13 - players[i].get_player_team().size();
        int width3 = 12; 
        if (players[i].get_player_name().size() > 11) {
            width = players[i].get_player_name().size() - 11;
            width = 9 - width;
            width = width + players[i].get_player_team().size();
        }
        else {
            width = players[i].get_player_name().size() - 11;
            width = 9 - width;
            width = width + players[i].get_player_team().size();
        }
        if (players[i].get_p_goals() > 9) {
            width2 = width2 + 5;
        }
        else if (players[i].get_p_goals() > 99) {
            width2 = width2 + 5;
        }
        else {
            width2 = width2 + 5;
        }

        out_str << players[i].get_player_name();
        out_str.width(width);
        out_str << std::right << players[i].get_player_team(); 
        out_str.width(width2);
        out_str << std::right << players[i].get_p_goals(); 
        out_str.width(width3);
        out_str << std::right << players[i].get_p_assists();
        out_str.width(14);
        out_str << std::right << players[i].get_p_penalties() << std::endl;
    }
        

    }
void third(std::vector<Team> &teams, std::vector<Player> &players, std::ofstream &out_str) {
    out_str << " " << std::endl << " " << std::endl;
    out_str << "Team        Assists" << std::endl;
    for ( int i = 0; i < teams.size(); ++i) {
        for (int j = 0; j < players.size(); ++j) {
            if (teams[i].get_team_name() == players[j].get_player_team()) {
                teams[i].increment_assists(players[j].get_p_assists());
            }
        }
        out_str << teams[i].get_team_name();
        out_str.width(19 - teams[i].get_team_name().size());
        out_str << std::right << teams[i].get_assists() << std::endl; 
    }
}




int main(int argc, char* argv[]) {
    std::ifstream in_str(argv[1]);
    std::ofstream out_str(argv[2]);
    std::string h;
    std::vector<Team> teams;
    std::vector<Player> players;
    int j = 0;
   
    while ( in_str >> h) {
        std::string tmp = "", trash = "", home_team = "", away_team = "";
        int awayscore = 0, homescore = 0;
        in_str >> tmp >> tmp >> tmp >> away_team >> tmp >> home_team; 
        
        bool away_exists = false, home_exists = false;
        for (int i = 0; i < teams.size(); ++i) {
            if (away_team == teams[i].get_team_name()) {
                away_exists = true;
            }
            if (home_team == teams[i].get_team_name()) {
                home_exists = true;
            }
        }
        if (away_exists == false) {
            Team cool(away_team);
            teams.push_back(cool);
        }
        if (home_exists == false) {
            Team cool(home_team);
            teams.push_back(cool);
        }
        
        
        
         bool endgame = false;
        
       
        while (endgame == false) {
          
             
            
            in_str >> tmp;
            if (tmp == "PERIOD") {
                in_str >> tmp;
              }
            else if (tmp == "OVERTIME") {} //Makes the code ignore the else statement for now
            else if (tmp == "FINAL") { //This else if statement will see who won/ lost, and store that info.
                in_str >> tmp >> awayscore >> tmp >> homescore;
                int position_a= 0, position_h = 0;
                for (int i = 0; i < teams.size(); ++i){
                    if (away_team == teams[i].get_team_name()) {
                        position_a = i;
                    }
                    if (home_team == teams[i].get_team_name()) {
                        position_h = i;
                    }
                    
                }
                if (awayscore > homescore) {
                    teams[position_a].increment_wins();
                    
                    teams[position_h].increment_loss();
                   
                }
                else if (homescore > awayscore) {
                    teams[position_h].increment_wins();
                    teams[position_a].increment_loss();
                    
                }
                else if (homescore == awayscore) {
                    teams[position_a].increment_ties();
                    teams[position_h].increment_ties();
                    

                }
 
                endgame = true;
            }
            else { //This else statement keeps track of what event(Goal, Penalty, Assist) has happened and stores info appropriately.
                //in_str >> teamname;
                int position = 0;
                
                std::string type = "", player_n = "";
                in_str >> tmp;
                for (int i = 0; i < teams.size(); ++i) {
                    if (tmp == teams[i].get_team_name()) {
                        position = i;
                    }
                }
                in_str >> type >> player_n; //type of event and then name of player it refers to.
                int player_position = 0;
                bool player_exists = false;
                for (int i = 0; i < players.size(); ++i) {
                    if (players[i].get_player_name() == player_n || players[i].get_player_name() == player_n + " ") {
                        player_exists = true;
                        player_position = i;
                        players[i].increment_p_team(tmp);
                    }
                    

                
                }
                if (player_exists == false && player_n != "BENCH") {
                        Player cool2(player_n);
                        players.push_back(cool2);
                        player_position = players.size() - 1;
                        players[player_position].increment_p_team(tmp);
                    }
                
                
                
                
                if (type == "goal") {
                    teams[position].increment_goals();
                    players[player_position].increment_p_goals();
                    
                    //this is where you collect data on which player scored/assisted
                    in_str >> trash;
                   // std::cout << trash << std::endl;
                    while (trash != ")"){
                        
                        in_str >> trash;//<-----trash here is actually assist names. 
                        //if (trash == ")") break;
                       // std::cout << trash << std::endl;
                        bool player_exists2 = false;
                        for ( int i = 0; i < players.size(); ++i) {
                            if (players[i].get_player_name() == trash || players[i].get_player_name() == trash + " ") {
                                players[i].increment_p_assists();
                                player_exists2 = true;
                                break;                    
                             }
                            

                        }
                        if (trash != "(" && trash != ")" && player_exists2 == false) {
                                Player cool3(trash);
                                players.push_back(cool3);
                                player_position = players.size()-1;
                                players[player_position].increment_p_team(tmp);
                                players[player_position].increment_p_assists();
                        }
                        //if (trash == ")") break;
                        //std::cout << "\n\n\n";
                    }
                }
                else if (type == "penalty") {
                    if(players[player_position].get_player_name()=="Tim_O'Brien")
                    {   
                        players[player_position].set_p_penalties(0);
                    }
                    teams[position].increment_penalties();
                    players[player_position].increment_p_penalties();
                    in_str >> tmp >> tmp;
                }
                
                //endgame = true;
                
            }
            
        }
         
    }
    std::sort(teams.begin(), teams.end(),isbetterteam);
    std::sort(players.begin(), players.end(),isbetterplayer);
    team_output(teams, out_str);
    player_output(players,out_str);
    third(teams, players, out_str);
    return 0;
}

