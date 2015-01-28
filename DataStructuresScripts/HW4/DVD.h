#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

#ifndef DVD_H
#define	DVD_H

class DVD {
public:
    //Constructor
    DVD(const std::string& name, int num_copies, int num_rented){
        name_ = name;
        num_copies_ = num_copies;
        num_rented_ = num_rented;
    }
    
    //Accessor 
    const std::string& get_name() const {return name_;}
    bool available() {
        return (num_copies_ > 0); 
    }
    
    void print_dvd(std::string dvd_name, std::ostream &ostr) {
        ostr << dvd_name << ":" << std::endl;
        if (num_rented_ == 1) {
            ostr << "  " << num_rented_ << " copy checked out";
        }
        else if (num_rented_ == 0) {
            ostr << "";
        }
        else {
        ostr << "  " << num_rented_ << " copies checked out";
        }
        if (num_copies_ == 0) {
            ostr << std::endl;
        }
        if (num_copies_ == 1) {
            ostr << " and " << num_copies_ << " copy available" << std::endl;
        }
        if (num_copies_ > 1) {
            ostr << " and " << num_copies_ << " copies available" << std::endl;
        }

                
    }
    
    //Modifier
    void increment_num_copies(int add_num) { 
        num_copies_ += add_num;
        //num_rented_ -= add_num;
    }
    void decrement_num_rented(int dec_num) {
        num_rented_ -= dec_num;
    }
    void shipped() {
        num_copies_ -= 1;
        num_rented_ += 1;
    }
    
private:
    std::string name_;
    int num_copies_;
    int num_rented_;
    
};




#endif	/* DVD_H */

