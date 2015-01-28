// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <cstdlib>
#include "DVD.h"
#include "Customer.h"

// several type defs to keep things neat
// (hint, these are STL lists)
typedef std::list<DVD> inventory_type;
typedef std::list<Customer> customers_type;
typedef std::list<std::string> preference_type;


// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);
customers_type::iterator find_Customer(customers_type &customers, const std::string &customer_name);
// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// ==================================================================


void usage(const char* program_name) {
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}


int main(int argc, char* argv[]) {

  if (argc < 3 || argc > 5) {
    usage(argv[0]);
  }

  // open input and output file streams
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
    usage(argv[0]); 
  }
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
    usage(argv[0]); 
  }

  // optional parameters for extra credit
  bool use_improved_algorithm = false;
  bool print_analysis = false;
  for (int i = 3; i < argc; i++) {
    if (std::string(argv[i]) == "--improved") {
      use_improved_algorithm = true;
    } else if (std::string(argv[i]) == "--analysis") {
      print_analysis = true;
    } else {
      usage(argv[0]);
    }
  }


  // stores information about the DVDs
  inventory_type inventory;
  // stores information about the customers
  customers_type customers;


  // read in and handle each of the 8 keyword tokens
  std::string token;
  while (istr >> token) {
    if (token == "dvd") {
      std::string dvd_name = read_dvd_name(istr);
      int copies;
      istr >> copies;

      
      bool duplicate = false;
      for (std::list<DVD>::iterator iter = inventory.begin(); iter != inventory.end(); ++iter) {
          if (dvd_name == iter->get_name() ) {
              iter->increment_num_copies(copies);
              duplicate = true;
          }
      }
      if (duplicate == false) {
        int rented_out = 0; 
        DVD temp (dvd_name, copies, rented_out);
        inventory.push_back(temp);
      }
      if (copies == 1) {
          ostr << copies << " copy of " << dvd_name << " added" << std::endl;
      }
      else{
      ostr << copies << " copies of " << dvd_name << " added" << std::endl;
      }

      
    } else if (token == "customer") {
        
        // new guys
      std::string customer_name = read_customer_name(istr);
      int num_movies;
      istr >> num_movies;
      bool customer_added = false;
      customers_type::iterator temp_itr = find_Customer(customers, customer_name);
      if (temp_itr != customers.end()) {
          // Already in sysem
          // false
          customer_added = false;

      }
      else{ 
         
          Customer temp_customer(customer_name);
          customers.push_back(temp_customer);
          temp_itr = customers.end();
          temp_itr--;
          customer_added=true;
      }
 
      
      std::list<DVD>::iterator dvd_iter;
      
      
      if (customer_added == true) {
          
      for (int i = 0; i < num_movies; i++) {
          
          bool dvd_in_inventory = false;

        std::string dvd_name = read_dvd_name(istr);
          for (dvd_iter = inventory.begin(); dvd_iter != inventory.end(); ++dvd_iter) {
              
              if (dvd_iter->get_name() == dvd_name) {
 
                  temp_itr->add_preference(dvd_name, ostr);
                  dvd_in_inventory = true;
                  
              }


          }        
        
              if (dvd_in_inventory == false) {
                  ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
              }
      }
    }
      if (customer_added == false) {
                ostr << "WARNING: Already have a customer named " << customer_name << std::endl;
                //______________________________________________________________
                std::list<std::string> trash;
                for (int i = 0; i < num_movies; ++i) {
                    std::string dvd_name = read_dvd_name(istr);
                }
                
                
      }
      if (customer_added == true) {
          ostr << "new customer: " << customer_name << std::endl;
      }

     

    } else if (token == "ship") {

      shipping_algorithm(inventory,customers,ostr);
      
    } else if (token == "return_oldest") {
      std::string customer_name = read_customer_name(istr);
      std::list<Customer>::iterator cust_iter2;
      bool is_there3 = false;
      bool generic = false;
      std::string oldest;
      for (cust_iter2 = customers.begin(); cust_iter2 != customers.end(); ++cust_iter2) {
          if (customer_name == cust_iter2->get_name()) {
              if (cust_iter2->rented_list_empty() == true) {
                  ostr << "WARNING: " << customer_name << " has no DVDs to return!" << std::endl;
                  is_there3 = true;
                  generic = true;
              }
              else{
              oldest = cust_iter2->get_oldest();
              cust_iter2->return_oldest(customer_name, ostr);
              is_there3 = true;
              ostr << customer_name << " returns " << oldest << std::endl;
              }
          }         
      }
      if (is_there3 == true) {
          
          std::list<DVD>::iterator iter;
          for (iter = inventory.begin(); iter != inventory.end(); ++iter) {
              if (iter->get_name() == oldest) {
                  iter->increment_num_copies(1);
                  iter->decrement_num_rented(1);
              }
          }

      }
      
      if (is_there3 == false) {
          ostr << "WARNING: No customer named " << customer_name << std::endl;
      }
      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else if (token == "return_newest") {
      std::string customer_name = read_customer_name(istr);
      std::list<Customer>::iterator cust_iter2;
      bool is_there3 = false;
      std::string newest;
      bool is_newest2 = false;
      for (cust_iter2 = customers.begin(); cust_iter2 != customers.end(); ++cust_iter2) {
          if (customer_name == cust_iter2->get_name()) {
              if (cust_iter2->rented_list_empty() == true) {
                  ostr << "WARNING: " << customer_name << " has no DVDs to return!" << std::endl;
                  is_there3 = true;
                  is_newest2 = true;
              }
              else{
              newest = cust_iter2->get_newest(); 
              cust_iter2->return_newest(customer_name, ostr);//<---------------------------------------------------------------------
              is_there3 = true;
              ostr << customer_name << " returns " << newest << std::endl;
              }
          }         
      }
      if (is_there3 == true) {
          
          std::list<DVD>::iterator iter;
          for (iter = inventory.begin(); iter != inventory.end(); ++iter) {
              if (iter->get_name() == newest) {
                  iter->increment_num_copies(1);
                  iter->decrement_num_rented(1);
                  is_newest2 = true;
              }
          }

         // else {
         //     ostr << "WARNING: " << customer_name << " has no DVDs to return!" << std::endl;
         // }
      }
      
      if (is_there3 == false) {
          ostr << "WARNING: No customer named " << customer_name << std::endl;
      }

      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else if (token == "print_customer") {
      std::string customer_name = read_customer_name(istr);
      std::list<Customer>::iterator cust_iter1;
      bool is_there = false;
      for (cust_iter1 = customers.begin(); cust_iter1 != customers.end(); ++cust_iter1) {
          if (customer_name == cust_iter1->get_name()) {
              cust_iter1->print_customer(customer_name, ostr);
              is_there = true;
              break;
          }
          
      }
      if (is_there == false) {
          ostr << "WARNING: No customer named " << customer_name << std::endl;
      }
      
      

     

    } else if (token == "print_dvd") {
      std::string dvd_name = read_dvd_name(istr);
      std::list<DVD>::iterator DVD_iter1;
      bool is_there2 = false;
      for (DVD_iter1 = inventory.begin(); DVD_iter1 != inventory.end(); ++DVD_iter1) {
          if (dvd_name == DVD_iter1->get_name()) {
              DVD_iter1->print_dvd(dvd_name, ostr);
              is_there2 = true;
              break;
          }
          
      }
      if (is_there2 == false) {
          ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
      }

    

    } else if (token == "add_preference") {
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = read_dvd_name(istr);
      std::list<Customer>::iterator cust_iter1;
      if (find_DVD(inventory, dvd_name) == inventory.end()) {
          ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << std::endl;
      }
      bool is_present = false;
      
      for (cust_iter1 = customers.begin(); cust_iter1 != customers.end(); ++cust_iter1) {
          
          if (customer_name == cust_iter1->get_name()) {
              is_present = true;
              std::list<std::string>::iterator iter5;
              for (iter5 = cust_iter1->get_preferences().begin(); iter5 != cust_iter1->get_preferences().end(); ++iter5) {
                  if (dvd_name == *iter5){
                      ostr << "WARNING: " << customer_name << " already has " << dvd_name << "on his/her preference list!" << std::endl;
                      break;
                  }
              else {
              cust_iter1->add_preference(dvd_name, ostr);
              break;
              }
              }
          }

          }
    


      
      if (is_present == false) {
            ostr << "WARNING: No customer named " << customer_name <<  std::endl;
      }
      

      /* YOU MUST FINISH THIS IMPLEMENTATION */

    } else {
      std::cerr << "ERROR: Unknown token " << token << std::endl;
      exit(1);
    }
  }
}


// ==================================================================


// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
  std::string token;
  istr >> token;
  assert (token[0] == '"');
  std::string answer = token;
  while (answer[answer.size()-1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}


// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name) {
  for (inventory_type::iterator inventory_itr = inventory.begin(); 
       inventory_itr != inventory.end(); inventory_itr++) {
    if (inventory_itr->get_name() == dvd_name) {
      return inventory_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return inventory.end();
}

//A helper function to find a customer from the system
customers_type::iterator find_Customer(customers_type &customers, const std::string &customer_name)
{
  for (customers_type::iterator customer_itr = customers.begin(); 
       customer_itr != customers.end(); customer_itr++) {
    if (customer_itr->get_name() == customer_name) {
      return customer_itr;
    }
  }
  // if the DVD is not found, return the .end() iterator
  return customers.end();
}


// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr) {

  



  ostr << "Ship DVDs" << std::endl;

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  customers_type::iterator customer_itr = customers.begin();
  while (customer_itr != customers.end()) {
    

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->has_max_num_movies() || customer_itr->preference_list_empty()) {
        
      // move on to the next customer
      customer_itr++;
      continue;
    }
    

    // a helper flag variable
    bool sent_dvd = false;
 
    // loop over the customer's preferences
    const preference_type &preferences = customer_itr->get_preferences();
    for (preference_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) {

      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr);

      if (inventory_itr != inventory.end() && inventory_itr->available()) { 
          
          

        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->get_name() << " receives " << *preferences_itr << std::endl;
        inventory_itr->shipped();
        customer_itr->receives(*preferences_itr);
        
        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;        
        break;
      }
    }

    // if no DVD was sent to this customer, then we move on to the next customer 
    // (do not change this customer's priority for tomorrow's shipment)
    if (!sent_dvd) {
      customer_itr++;
    }
  }

  

}

// ==================================================================
