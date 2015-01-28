
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "player.h"

Player::Player(std::string playername) {
    player_name = playername;
    player_team = "";
    p_goals = 0;
    p_penalties = 0;
    p_assists = 0;
    
}
void Player::increment_p_goals() {
    p_goals += 1;
}
void Player::increment_p_penalties() {
    p_penalties += 1;
}
void Player::increment_p_assists() {
    p_assists += 1;
}
void Player::increment_p_team(std::string playerteam) {
    player_team = playerteam;
}
void Player::set_p_penalties(int penalties) {
    p_penalties = penalties;
}
bool isbetterplayer(Player player1, Player player2) {
    if (player1.get_p_goals() + player1.get_p_assists() > player2.get_p_goals() + player2.get_p_assists()){
        return true;
    }
    else if (player1.get_p_goals() + player1.get_p_assists() < player2.get_p_goals() + player2.get_p_assists()){
        return false;
    }
    else{
        if (player1.get_p_penalties() < player2.get_p_penalties()) {
            return true;
        }
        else if (player1.get_p_penalties() > player2.get_p_penalties()) {
            return false;
        }
        else {
            if (player1.get_player_name() < player2.get_player_name()) {
                return true;
            }
            else if (player1.get_player_name() > player2.get_player_name()) {
                return false;
            }
            else {
                return false;
            }
        }
    }
}