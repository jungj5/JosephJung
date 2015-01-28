#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>

#ifndef CUSTOMER_H
#define	CUSTOMER_H

class Customer {
public:
    //Constructor
    Customer(const std::string& customer_name){
        customer_name_ = customer_name;
    }
    
    //Accessors
    
    //This function returns the oldest movie for the customer
    std::string& get_oldest() {
        
        std::list<std::string>::iterator movie_iter = rented_out_list.begin();
        return *movie_iter;
        
        
    }
    
    std::string& get_newest() {

        std::list<std::string>::reverse_iterator movie_iter = rented_out_list.rbegin();
        //movie_iter--;
        return *movie_iter;
    }
    const std::string& get_name() const {return customer_name_;}
    std::list<std::string> &get_preferences() {

        return preference_list;
        
    } 
    void print_customer(std::string customer_name, std::ostream &ostr) {
        if (rented_out_list.size() == 0) {
            ostr << customer_name << " has " << "no" << " movies" << std::endl;
        }
        else {
            ostr << customer_name << " has " << rented_out_list.size() << " movies:" << std::endl;
        }
        
        std::list<std::string>::iterator movie_iter;
        for (movie_iter = rented_out_list.begin(); movie_iter != rented_out_list.end(); ++movie_iter) {
            ostr << "    " << *movie_iter << std::endl;
        }
        if (preference_list.size() > 0) {
            ostr << "  preference list:" << std::endl;
            std::list<std::string>::iterator pref_iter;
            for (pref_iter = preference_list.begin(); pref_iter != preference_list.end(); ++pref_iter) {
                ostr << "    " << *pref_iter << std::endl;
            }
        }
                
    }
    
    //Modifers
    void return_oldest(std::string customer_name, std::ostream &ostr) {
        if (rented_out_list.size() == 0) {
            ostr << "WARNING: Customer currently does not have any DVDs" << std::endl;
            return;
        }
      std::list<std::string>::iterator iter = rented_out_list.begin();
      rented_out_list.erase(iter);

    }
    
    void return_newest(std::string customer_name, std::ostream &ostr) {

        std::list<std::string>::iterator iter = rented_out_list.end();
        --iter;
        rented_out_list.erase(iter);
    }
    void add_preference(std::string movie_name_, std::ostream &ostr) {
        std::list<std::string>::iterator movie_iter;
        std::list<std::string>::iterator movie_iter2;
        bool duplicates = false;
        for (movie_iter2 = preference_list.begin(); movie_iter2 != preference_list.end(); ++movie_iter2) {
            if (customer_name_ == "Harold Evans"){
            
            }
            if (*movie_iter2 == movie_name_) {
                ostr << "WARNING: Duplicate movie " << movie_name_<< " on preference list!" << std::endl;
                duplicates = true;
            }
        }
        /*
        for (movie_iter = rented_out_list.begin(); movie_iter != rented_out_list.end(); ++movie_iter) {
            if (*movie_iter == movie_name_) {
                ostr << "WARNING: Duplicate movie " << movie_name_<< " on preference list!" << std::endl;
                duplicates = true;
                //std::cout << "hit test";
            }
 
        }*/
        if (duplicates == false) {
            preference_list.push_back(movie_name_);
        }
        
    }

    void receives(std::string the_movie) {
        rented_out_list.push_back(the_movie);
        for (std::list<std::string>::iterator iter = preference_list.begin(); iter != preference_list.end(); ++iter) {
                if (the_movie == *iter) {
                        preference_list.erase(iter);
                        return;
              
          }
       }
    }
    bool has_max_num_movies() {
        if (rented_out_list.size() == 3) {
            return true;
        }
        return false;
    }
    bool preference_list_empty() {
        if (preference_list.size() == 0) {
            return true;
        }
        return false;
    }
    
    bool rented_list_empty() {
        if (rented_out_list.size() == 0) {
            return true;
            
        }
        return false;
    }
private:
    std::string customer_name_;
    std::list<std::string> preference_list;
    std::list<std::string> rented_out_list;
};


#endif	/* CUSTOMER_H */

