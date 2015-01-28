//File: team.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "team.h"

Team::Team(std::string teamname) {
    team_name = teamname;
    wins = 0;
    loss = 0;
    ties = 0;
    goals = 0;
    penalties = 0;
    wlr = 0;
    assists = 0;
    
}
void Team::increment_wins() {
    wins += 1;
}
void Team::increment_loss() {
    loss += 1;
}
void Team::increment_ties() {
    ties += 1;
}
void Team::increment_goals(){
    goals += 1;
}

void Team::increment_penalties() {
    penalties += 1;
}
void Team::increment_wlr(double wlr2) {
    wlr = wlr2;
}
void Team::increment_assists(int assist) {
    assists += assist;
}
bool isbetterteam(Team team1, Team team2) {
    double wlr1 = (team1.get_wins() + (.5 * team1.get_ties()))/ (team1.get_wins() + team1.get_loss() + team1.get_ties());
    double wlr2 = (team2.get_wins() + (.5 * team2.get_ties()))/ (team2.get_wins() + team2.get_loss() + team2.get_ties());
    if (wlr1 > wlr2) {
        return true;
    }
    else if (wlr1 < wlr2) { 
        return false;
    }
    else {
        if (team1.get_goals() > team2.get_goals()) {
                return true;
        }
        else if (team1.get_goals() < team2.get_goals()) { 
                return false;
        }
        else {
           if (team1.get_team_name() > team2.get_team_name()) {
                return true;
           }
           else if (team1.get_team_name() < team2.get_team_name()) { 
                return false;
           }
           else {
               return false;
           }
        }
    }
}
