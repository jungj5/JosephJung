// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include "assert.h"
#include <algorithm>
#include "stdlib.h"



// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef  std::map<std::string, std::map<std::string, int> >  MY_MAP;
typedef  std::map<std::string, std::map<std::string, std::map<std::string, int> > > MY_MAP2;


// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  std::cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << std::endl;
  std::cout << std::endl;


  //
  // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
  //
  std::string original;
  ReadNextWord(istr, original);
  std::map < std::string, std::map<std::string, int> >::iterator p;
  std::map<std::string, int>::iterator q;
  std::string word;

  while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;
	std::map < std::string, std::map<std::string, int> >::iterator finder = data.find(original);
	if (finder == data.end()) {
		++data[original][word];
		original = word;
	}
	else if (finder != data.end()) {
		finder->second[word]++;
		original = word;
	}
    //
    // ASSIGNMENT: PROCESS ALL THE NON PUNCTUATION WORDS
    // INSERTING THESE WORDS INTO THE DATA STRUCTURE
    //


  }

}


//LoadSampleText function for window = 3.
void LoadSampleText2(MY_MAP2 &data, const std::string &filename, int window, const std::string &parse_method) {
	// open the file stream
	std::ifstream istr(filename.c_str());
	if (!istr) {
		std::cerr << "ERROR cannot open file: " << filename << std::endl;
		exit(1);
	}
	// verify the window parameter is appropriate
	if (window < 2) {
		std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
	}
	// verify that the parse method is appropriate
	bool ignore_punctuation = false;
	if (parse_method == "ignore_punctuation") {
		ignore_punctuation = true;
	}
	else {
		std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
		exit(1);
	}

	std::cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << std::endl;
	std::cout << std::endl;
	

	//
	// ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
	//
	std::string original;
	std::string original2;
	ReadNextWord(istr, original);
	ReadNextWord(istr, original2);
	std::map < std::string, std::map<std::string, int> >::iterator p;
	std::map<std::string, int>::iterator q;
	std::string word;

	while (ReadNextWord(istr, word)) {
		
		// skip the quotation marks (not used for this part)
		if (word == "\"") continue;
		std::map < std::string, std::map<std::string, std::map<std::string, int> > >::iterator finder = data.find(original);
		if (finder == data.end()) {
			++data[original][original2][word];
			original = original2;
			original2 = word;
		}
		else if (finder != data.end()) {
			//std::cout << original2 << "," << word << std::endl;
			std::map<std::string, std::map<std::string, int> >::iterator iter;


			data[original][original2][word]++;
			original = original2;
			original2 = word;
		}
		//
		// ASSIGNMENT: PROCESS ALL THE NON PUNCTUATION WORDS
		// INSERTING THESE WORDS INTO THE DATA STRUCTURE
		//


	}
	/*
	std::map<std::string, int>::iterator test_iter;
	for (test_iter = data["could"]["not"].begin(); test_iter != data["could"]["not"].end(); ++test_iter) {
		std::cout << test_iter->first << " " << test_iter->second << std::endl;
	}
	*/

}





int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP data;
  MY_MAP2 data2;
  int window2;
  // Parse each command
  std::string command;    
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      int window;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;      
	  if (window == 2) {
		  LoadSampleText(data, filename, window, parse_method);
		  window2 = 2;
	  }
	  else if (window == 3) {
		  LoadSampleText2(data2, filename, window, parse_method);
		  window2 = 3;
	  }
      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //

    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
	  
	  if (window2 == 2) {
		  std::map<std::string, std::map<std::string, int> >::iterator it;
		  for (int i = 0; i < sentence.size(); ++i) {
			  for (it = data.begin(); it != data.end(); ++it) {
				  if (it->first == sentence[i]) {
					  int total = 0;
					  std::map<std::string, int>::iterator it2;
					  //finding total number of occurances a word showed up after word/ phrase
					  for (it2 = data[sentence[i]].begin(); it2 != data[sentence[i]].end(); ++it2) {
						  total += it2->second;
					  }
					  std::cout << sentence[i] << " (" << total << ")" << std::endl;
					  std::map<std::string, int>::iterator it3;
					  //output all the words that showed up after the desired word/phrase
					  for (it3 = data[sentence[i]].begin(); it3 != data[sentence[i]].end(); ++it3) {
						  std::cout << sentence[i] << " " << it3->first << " (" << it3->second << ")" << std::endl;
					  }
				  }
			  }
			  std::cout << std::endl;
		  }
	  }
	  if (window2 == 3) {
		  std::map<std::string, std::map<std::string, std::map<std::string, int> > >::iterator it;

		  if (sentence.size() == 1) {
			  int total2;
			  for (it = data2.begin(); it != data2.end(); ++it) {
				  if (it->first == sentence[0]) {
				  
					  int total = 0;
					  std::map<std::string, std::map<std::string, int> >::iterator it4;
					  for (it4 = data2[sentence[0]].begin(); it4 != data2[sentence[0]].end(); ++it4) {
						  


							  
							  std::map<std::string, int>::iterator it2;
							  //finding total number of occurances a word showed up after word/ phrase
							  for (it2 = data2[sentence[0]][it4->first].begin(); it2 != data2[sentence[0]][it4->first].end(); ++it2) {
								  total += it2->second;
								  total2 = total;
							  }
							  

						  
					  }
				  }
			  }
			  std::cout << sentence[0] << " (" << total2 << ")" << std::endl;
			  std::map<std::string, int>::iterator it3;
			  std::map<std::string, std::map<std::string, int> >::iterator iter2;
			  //output all the words that showed up after the desired word/phrase
			  for (iter2 = data2[sentence[0]].begin(); iter2 != data2[sentence[0]].end(); ++iter2) {
				  int total4 = 0;
				  for (it3 = data2[sentence[0]][iter2->first].begin(); it3 != data2[sentence[0]][iter2->first].end(); ++it3) {
					  total4 += it3->second;

					}
				  std::cout << sentence[0] << " " << iter2->first << " (" << total4 << ")" << std::endl;
			  }

		  }

		  else if (sentence.size() == 2) {
			  for (it = data2.begin(); it != data2.end(); ++it) {
				  if (it->first == sentence[0]) {
					  std::map<std::string, std::map<std::string, int> >::iterator it4;
					  for (it4 = data2[sentence[0]].begin(); it4 != data2[sentence[0]].end(); ++it4) {

						  if (it4->first == sentence[1]){
							  int total = 0;
							  std::map<std::string, int>::iterator it2;
							  //finding total number of occurances a word showed up after word/ phrase
							  for (it2 = data2[sentence[0]][sentence[1]].begin(); it2 != data2[sentence[0]][sentence[1]].end(); ++it2) {
								  total += it2->second;
							  }
							  std::cout << sentence[0] << " " << sentence[1] << " (" << total << ")" << std::endl;
							  std::map<std::string, int>::iterator it3;
							  //output all the words that showed up after the desired word/phrase
							  for (it3 = data2[sentence[0]][sentence[1]].begin(); it3 != data2[sentence[0]][sentence[1]].end(); ++it3) {
								  std::cout << sentence[0] << " " << sentence[1] << " " << it3->first << " (" << it3->second << ")" << std::endl;
							  }
						  }
					  }
				  }
			  }
		  }
			  std::cout << std::endl;
		  
	  }

      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //


    }

    // generate the specified number of words 
	else if (command == "generate") {
		std::vector<std::string> sentence = ReadQuotedWords(std::cin);
		// how many additional words to generate
		int length;
		std::cin >> length;
		std::string selection_method;
		std::cin >> selection_method;
		bool random_flag;
		if (selection_method == "random") {
			random_flag = true;
		}
		else {
			assert(selection_method == "most_common");
			random_flag = false;
		}
		if (window2 == 2) {

			if (random_flag == false) {


				for (int i = 0; i < sentence.size(); ++i) {
					std::cout << sentence[i] << " ";
				}
				int count = 0;
				std::string last_word = sentence[sentence.size() - 1];

				//while we still need to generate more words..
				while (count < length) {


					int highest_value = 0;
					std::map<std::string, int>::iterator iter;
					//finding the highest value in the 2nd map
					for (iter = data[last_word].begin(); iter != data[last_word].end(); ++iter) {
						if (iter->second > highest_value) {
							highest_value = iter->second;
						}
					}
					//find the word with that corresponding number of occurances (highest value)
					std::map<std::string, int>::iterator iter2;

					//stores words with highest_value number of occurances
					std::vector<std::string> tmp;
					//find all the words that have highest_value number of occurances and put it in vector
					for (iter2 = data[last_word].begin(); iter2 != data[last_word].end(); ++iter2) {
						if (iter2->second == highest_value) {
							tmp.push_back(iter2->first);
						}
					}
					//if there is more than one word that occurs the most (equal highest_values)

					if (tmp.size() > 1) {
						std::sort(tmp.begin(), tmp.end());
						std::cout << tmp[0] << " ";
						last_word = tmp[0];
						count += 1;
					}
					else{

						std::cout << tmp[0] << " ";

						last_word = tmp[0];
						count += 1;
					}

				}

				std::cout << std::endl;

			}

			//if we randomly generate the words.
			if (random_flag == true) {
				for (int i = 0; i < sentence.size(); ++i) {
					std::cout << sentence[i] << " ";
				}
				std::string last_word = sentence[sentence.size() - 1];
				int count = 0;

				while (count < length) {

					std::map<std::string, int>::iterator iter;
					std::vector<std::string> tmp_words;
					int total_occurances = 0;
					for (iter = data[last_word].begin(); iter != data[last_word].end(); ++iter) {
						total_occurances += iter->second;
						int number_occurances = iter->second;
						for (int j = 0; j < number_occurances; ++j) {
							tmp_words.push_back(iter->first);
						}

					}
					int randomly_chosen_number = rand() % total_occurances;
					std::cout << tmp_words[randomly_chosen_number] << " ";
					count += 1;
					last_word = tmp_words[randomly_chosen_number];
					
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
	}
		//******************************************Window size 3 generate***************************************
		//*******************************************************************************************************
		//*******************************************************************************************************

		if (window2 == 3) {


			if (random_flag == false) {


				for (int i = 0; i < sentence.size(); ++i) {
					std::cout << sentence[i] << " ";
				}
				int count = 0;

				if (sentence.size() > 1) {
					std::string first_word = sentence[0];
					std::string last_word = sentence[sentence.size() - 1];

					//while we still need to generate more words..
					while (count < length) {


						int highest_value = 0;
						std::map<std::string, int>::iterator iter;
						//finding the highest value in the 2nd map
						for (iter = data2[first_word][last_word].begin(); iter != data2[first_word][last_word].end(); ++iter) {
							if (iter->second > highest_value) {
								highest_value = iter->second;
							}
						}
						//find the word with that corresponding number of occurances (highest value)
						std::map<std::string, int>::iterator iter2;

						//stores words with highest_value number of occurances
						std::vector<std::string> tmp;
						//find all the words that have highest_value number of occurances and put it in vector
						for (iter2 = data2[first_word][last_word].begin(); iter2 != data2[first_word][last_word].end(); ++iter2) {
							if (iter2->second == highest_value) {
								tmp.push_back(iter2->first);
							}
						}
						//if there is more than one word that occurs the most (equal highest_values)

						if (tmp.size() > 1) {
							std::sort(tmp.begin(), tmp.end());
							std::cout << tmp[0] << " ";
							first_word = last_word;
							last_word = tmp[0];
							count += 1;
						}
						else{

							std::cout << tmp[0] << " ";
							first_word = last_word;
							last_word = tmp[0];
							count += 1;
						}

					}
				}
				else {


					
					std::string last_word = sentence[0];
					
					//while we still need to generate more words..
					while (count < length) {


						int highest_value = 0;
						std::map<std::string, int>::iterator iter;
						std::map<std::string, int>::iterator it3;
						std::map<std::string, std::map<std::string, int> >::iterator iter2;
						std::map<std::string, int> tmp_map;
						for (iter2 = data2[last_word].begin(); iter2 != data2[last_word].end(); ++iter2) {
							int total4 = 0;
							for (it3 = data2[last_word][iter2->first].begin(); it3 != data2[last_word][iter2->first].end(); ++it3) {
								total4 += it3->second;
								
							}
							if (total4 > highest_value) {
								highest_value = total4;
							}
							std::pair < std::string, int> tmp_pair (iter2->first, total4);
							tmp_map.insert(tmp_pair);
							
						}


						std::vector<std::string> tmp_vect;
						std::map<std::string, int>::iterator iter3;
						for (iter3 = tmp_map.begin(); iter3 != tmp_map.end(); ++iter3) {
							if (iter3->second == highest_value) {
								tmp_vect.push_back(iter3->first);
							}
						}
						//if there is more than one word that occurs the most (equal highest_values)
						std::string last_word_tmp = last_word;
						if (tmp_vect.size() > 1) {
							
							std::sort(tmp_vect.begin(), tmp_vect.end());
							std::cout << tmp_vect[0] << " ";
							last_word = tmp_vect[0];
							count += 1;
						}
						else if (tmp_vect.size() == 1) {

							std::cout << tmp_vect[0] << " ";

							last_word = tmp_vect[0];
							count += 1;
						}
						std::vector<std::string> tmp_vect2;
						std::map<std::string, int>::iterator iter5;
						int highest_value2 = 0;
						
						for (iter5 = data2[last_word_tmp][last_word].begin(); iter5 != data2[last_word_tmp][last_word].end(); ++iter5) {
							if (highest_value2 < iter5->second) {
								highest_value2 = iter5->second;
							}
						}
						for (iter5 = data2[last_word_tmp][last_word].begin(); iter5 != data2[last_word_tmp][last_word].end(); ++iter5) {
							if (highest_value2 == iter5->second) {
								tmp_vect2.push_back(iter5->first);
							}
						}
						if (tmp_vect2.size() > 1) {
							
							std::sort(tmp_vect2.begin(), tmp_vect2.end());
							std::cout << tmp_vect2[0] << " ";
							
							last_word = tmp_vect2[0];
							count += 1;
							
						}
						else if (tmp_vect2.size() == 1) {
							

							std::cout << tmp_vect2[0] << " ";

							last_word = tmp_vect2[0];
							count += 1;
						}

						

					}
				}
				std::cout << std::endl;

			}
			if (random_flag == true) {
				for (int i = 0; i < sentence.size(); ++i) {
					std::cout << sentence[i] << " ";
				}
				std::string last_word = sentence[sentence.size() - 1];
				int count = 0;

				while (count < length) {

					std::map<std::string, std::map<std::string, int> >::iterator iter;
					std::map<std::string, int>::iterator iter2;
					std::vector<std::string> tmp_words;
					int total_occurances = 0;
					for (iter = data2[last_word].begin(); iter != data2[last_word].end(); ++iter) {
						for (iter2 = data2[last_word][iter->first].begin(); iter2 != data2[last_word][iter->first].end(); ++iter2) {
							total_occurances += iter2->second;
							int number_occurances = iter2->second;
							for (int j = 0; j < number_occurances; ++j) {
								tmp_words.push_back(iter2->first);
							}
						}

					}
					int randomly_chosen_number = rand() % total_occurances;
					std::cout << tmp_words[randomly_chosen_number] << " ";
					count += 1;
					last_word = tmp_words[randomly_chosen_number];
					
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			}

		}
		

      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //


     else if (command == "quit") {
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
