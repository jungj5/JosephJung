/* 
 * File:   team.h
 * Author: jungj5
 *
 * Created on February 3, 2014, 8:40 PM
 */

#ifndef __team_h_
#define	__team_h_

#include <iostream>
#include <string>
#include <vector>


class Team {
public:
    Team(std::string teamname);
    //Accessors
    const std::string& get_team_name() const { return team_name; }
    int get_wins() {return wins;}
    int get_loss() {return loss;}
    int get_ties() {return ties;}
    int get_goals() {return goals;}
    int get_penalties() {return penalties;}
    int get_assists() {return assists;}
    double get_wlr() {return wlr;}
    
    //Modifiers
    void increment_wins();
    void increment_loss();
    void increment_ties();
    void increment_goals();
    void increment_penalties();
    void increment_assists(int assist);
    void increment_wlr(double wlr2);
    
    //double wlr() const { return (wins + .5 * ties); }         //wlr = win loss ratio for teams
    
    //Output function (Makes the output look pretty)
    void output_stats(std::ostream& out_str);
    
    
private:
    std::string team_name;
    int wins;
    int loss;
    int ties;
    int goals;
    int penalties;
    int assists;
    double wlr;
   
};
bool isbetterteam(Team team1, Team team2);
#endif	/* TEAM_H */

