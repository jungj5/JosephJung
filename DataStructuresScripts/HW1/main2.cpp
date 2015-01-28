/* 
 * File:   main.cpp
 * Author: jungj5
 *
 *
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
//Flush left function
void flush_left(std::vector<std::string> vect, std::ofstream &out, const int width) {
 
    for (int i = 0; i < width+4; ++i ) {
        out << "-";
    }
    out << std::endl;
    int words_used = 0;
    while (vect.size() > 0) {
        out << "| ";
        int count = 0;
        std::vector<std::string> temp;
        while (true){
            if (vect.size() > 0 && (count == 0) && (vect[0].length() <= width)) {
                temp.push_back(vect[0]);
                count += vect[0].length();
                vect.erase(vect.begin());
            
            }
            
            else if (vect.size() > 0 && (count > 0) && (vect[0].length() + 1 <= width - count)){
                temp.push_back(vect[0]);
                count += vect[0].length() + 1;
                vect.erase(vect.begin());
            }
            else {
                for ( int i = 0; i < temp.size(); ++i) {
                    if (i == 0) {
                        out << temp[i];
                        ++words_used;
                    }
                    else {
                        out << " " << temp[i];
                        ++words_used;
                    }
                }
                for (int i = 0; i < width-count; ++i) {
                    out << " ";
                }
                break;
            }
        }
        out << " |" << std::endl;
    }
    for (int i = 0; i < width+4; ++i ) {
        out << "-";
    }
    out << std::endl;
}

//Function that will flush right when called.
void flush_right(std::vector<std::string> vect, std::ofstream &out, const int width) {
 
 
    for (int i = 0; i < width+4; ++i ) {
        out << "-";
    }
    out << std::endl;
    int words_used = 0;
    while (vect.size() > 0) {
        out << "| ";
        int count = 0;
        std::vector<std::string> temp;
        while (true){
            if (vect.size() > 0 && (count == 0) && (vect[0].length() <= width)) {
                temp.push_back(vect[0]);
                count += vect[0].length();
                vect.erase(vect.begin());
            
            }
            
            else if (vect.size() > 0 && (count > 0) && (vect[0].length() + 1 <= width - count)){
                temp.push_back(vect[0]);
                count += vect[0].length() + 1;
                vect.erase(vect.begin());
            }
            else {
                for (int i = 0; i < width-count; ++i) {
                    out << " ";
                }
                for ( int i = 0; i < temp.size(); ++i) {
                    if (i == 0) {
                        out << temp[i];
                        ++words_used;
                    }
                    else {
                        out << " " << temp[i];
                        ++words_used;
                    }
                }
                
                break;
            }
        }
        out << " |" << std::endl;
    }
    for (int i = 0; i < width+4; ++i ) {
        out << "-";
    }
    out << std::endl;
}
//Full justify function
void full_justify(std::vector<std::string> vect, std::ofstream &out, const int width) {
        for (int i = 0; i < width+4; ++i ) {
        out << "-";
    }
    out << std::endl;
    int words_used = 0;
    while (vect.size() > 0) {
        out << "| ";
        int count = 0;
        std::vector<std::string> temp;
        while (true){
           int inbetweenspaces = 0;
           int remaining_space = 0;
           int spaces = 0;            
            if (vect.size() > 0 && (count == 0) && (vect[0].length() <= width)) {
                temp.push_back(vect[0]);
                count += vect[0].length();
                vect.erase(vect.begin());
            
            }
            
            else if (vect.size() > 0 && (count > 0) && (vect[0].length() + 1 <= width - count)){
                temp.push_back(vect[0]);
                count += vect[0].length() + 1;
                vect.erase(vect.begin());
            }
            else {
                if (temp.size() > 1){
                        inbetweenspaces = temp.size() - 1;
                        remaining_space = width - count;
                        if ((remaining_space / inbetweenspaces)%2 == 0) {
                        spaces = (remaining_space / inbetweenspaces) + 1;
                        }
                        else if ((remaining_space / inbetweenspaces)%2 != 0){
                            spaces = (remaining_space / inbetweenspaces) + 1;
                        }
                        
                        }
                        else{
                            spaces = 0;
                        }
                
                for ( int i = 0; i < temp.size(); ++i) {
                    if (i == 0) {
                        out << temp[i];
                        ++words_used;
                    }

                    else {
                        

                        for (int j = 0; j < spaces; ++j) {
                        out << " ";
                        }
                    if (spaces == 1) {
                        out << " ";
                        //spaces = 0;
                    }    
                    out << temp[i];
                    ++words_used;
                    
                    }
                }
                if (spaces == 0) {
                    for (int i = 0; i < width-count; ++i) {
                        out << " ";
                        }
                }
                break;
            }
        }
        out << " |" << std::endl;
    }
    for (int i = 0; i < width+4; ++i ) {
        out << "-";
    }
    out << std::endl;
    
    
}

//Main code
int main(int argc, char* argv[]) {
    std::ifstream in_str(argv[1]);
    if (!in_str.good()) {
        std::cerr << "Can't open " << argv[1] << " to read. \n";
        return 1;
    }
       
    
   
    std::ofstream out_str(argv[2]);
    if (!out_str.good()) {
        std:: cerr << "Can't open " << argv[2] << " to write.\n";
        return 1;
    }
    if (argc != 5){
        std::cerr << "Not a valid number of arguments";
        return 1;
    }
    
    std::vector<std::string> data;
    std::string my_string;
    
    while (in_str >> my_string ){
        data.push_back(my_string);
    }
    //Width from user input
    int x = atoi(argv[3]);
    if (x <= 0) {
        std::cerr << "Not a valid width for justification";
        return 1;
    }
    
    //Flush left, flush right, or full justify from user input
    std::string tmp = argv[4];
    
    //Checks user input for type of action
    if (tmp == "flush_left"){
        flush_left(data, out_str, x);
        return 0;
    }
    else if (tmp == "flush_right"){
        flush_right(data, out_str, x);
        return 0;
        
    }
    else if (tmp == "full_justify"){
        full_justify(data, out_str, x);
        return 0;
               
    }
    
    else {
        std::cerr << tmp << " is not a valid command.";
        return 1;
    }
        
    
    return 0;
}
    
      
        
        
        
    

