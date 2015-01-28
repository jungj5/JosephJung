/* 
 * File:   player.h
 * Author: jungj5
 *
 * Created on February 4, 2014, 7:36 PM
 */

#ifndef __player_h_
#define	__player_h_

#include <iostream>
#include <vector>
#include <string>

class Player {
public:
    Player(std::string playername);
        //Accessors
    const std::string& get_player_name() const { return player_name; }
    int& get_p_goals() {return p_goals;}
    int& get_p_assists() {return p_assists;}
    int& get_p_penalties() {return p_penalties;}
    const std::string& get_player_team() const { return player_team; }

    
    //Modifiers
    void increment_p_assists();
    void increment_p_goals();
    void increment_p_penalties();
    void set_p_penalties(int penalties);
    void increment_p_team(std::string teamname);

    
private:
    std::string player_name;
    int p_assists;
    int p_goals;
    int p_penalties;
    std::string player_team;
};

bool isbetterplayer(Player player1, Player player2);

#endif	/* PLAYER_H */

