#include "graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

Graph::Graph() {

}



//Destructor
Graph::~Graph() {
	//delete all people
	for (int i = 0; i < m_people.size(); ++i) {
		delete m_people[i];
	}
	//delete all messages
	for (int j = 0; j < m_messages.size(); ++j) {
		delete m_messages[j];
	}
}

bool Graph::add_person(const std::string& person_name) {
	//check to see if person is already in the graph
	for (int i = 0; i < m_people.size(); ++i) {
		if (m_people[i]->get_name() == person_name) {
			//std::cerr << "error" << std::endl;
			return false;
		}
	}

	//add the person if the function didn't return false
	Person* new_person = new Person(person_name);
	m_people.push_back(new_person);
	return true;
}

bool Graph::remove_person(const std::string& person_name) {
	//go through each person in the graph
	for (int i = 0; i < m_people.size(); ++i) {

		std::list<Person*> tmp_friends = m_people[i]->get_friends();
		std::list<Person*>::iterator iter;
		//go through each person's friend list
		for (iter = tmp_friends.begin(); iter != tmp_friends.end(); ++iter) {
			//if the person being removed is in the friends list, then get take him out
			if ((*iter)->get_name() == person_name) {
				m_people[i]->remove_friend(*iter);
			}
		}
	}
	//finding the person in the graph
	for (int j = 0; j < m_people.size(); ++j) {
		//if found, clear out his friends list and get rid of him.
		if (m_people[j]->get_name() == person_name) {
			std::list<Person*> tmp_m_friends;
			tmp_m_friends = m_people[j]->get_friends();
			std::list<Person*>::iterator tmp_iter;
			for (tmp_iter = tmp_m_friends.begin(); tmp_iter != tmp_m_friends.end(); ++tmp_iter) {
				m_people[j]->remove_friend(*tmp_iter);
			}

			delete m_people[j];
			m_people.erase(m_people.begin() + j);

			return true;
		}
	}
	return false;
}


bool Graph::add_friendship(const std::string& person_name1, const std::string& person_name2) {
	Person* tmp1;
	Person* tmp2;
	//check to see if person is trying to add him/herself. Return false if this is happening
	if (person_name1 == person_name2) {
		//std::cerr << "Can't add youself as a friend!" << std::endl;
		return false;
	}
	for (int i = 0; i < m_people.size(); ++i) {
		if (m_people[i]->get_name() == person_name1) {
			tmp1 = m_people[i];
		}
		if (m_people[i]->get_name() == person_name2) {
			tmp2 = m_people[i];
		}
	}
	//add the friend
	if (tmp1->add_friend(tmp2) == true) {
		return true;
	}
	else {
		return false;
	}
	
	

}

bool Graph::remove_friendship(const std::string& person_name1, const std::string& person_name2) {
	Person* tmp1;
	Person* tmp2;
	//check to see if person is trying to remove himself. DON'T LET HIM D=
	if (person_name1 == person_name2) {
		//std::cerr << "Can't remove yourself from friends list!" << std::endl;
		return false;
	}
	for (int i = 0; i < m_people.size(); ++i) {
		if (m_people[i]->get_name() == person_name1) {
			tmp1 = m_people[i];
		}
		if (m_people[i]->get_name() == person_name2) {
			tmp2 = m_people[i];
		}
	}
	//remove the friend and return true if it is a valid move.
	if (tmp1->remove_friend(tmp2) == true) {
		return true;
	}
	else {
		return false;

	}
	
	
}


bool Graph::add_message(const std::string& person_name, const std::string& message) {
	bool found = false;
	Person* tmp_person;
	//check to see if the person exists in the graph and return false if he doesn't
	for (int i = 0; i < m_people.size(); ++i) {
		if (person_name == m_people[i]->get_name()) {
			tmp_person = m_people[i];
			found = true;
		}
	}
	if (found == false) {
		//std::cerr << "person not found in database" << std::endl;
		return found;
	}
	//create a new message and add it to the graph.
	else {
		Message* new_message = new Message(message, tmp_person);
		m_messages.push_back(new_message);
		return found;
	}
}


void Graph::pass_messages(MTRand &mtrand) {
	for (int i = 0; i < m_people.size(); ++i) {
		if (m_people[i]->get_messages().size() > 0) {
			//copy list of messages
			std::list<Message*> tmp_messages = m_people[i]->get_messages();
			std::list<Message*>::iterator iter;
			//go through all the messages
			for (iter = tmp_messages.begin(); iter != tmp_messages.end(); ++iter) {
				int rand = mtrand.randInt(m_people[i]->get_friends().size());
				//tmp_vect used for random selection purposes
				std::vector<Person*> tmp_vect;
				std::list<Person*>::iterator person_iter;
				std::list<Person*> tmp_persons = m_people[i]->get_friends();
				//push back people into the temporary vector
				for (person_iter = tmp_persons.begin(); person_iter != tmp_persons.end(); ++person_iter) {
					tmp_vect.push_back(*person_iter);
				}
				//selected person from random integer generator
				Person* selected = tmp_vect[rand];
				//pass on the message to the selected person
				(*iter)->pass_message(selected);
				//delete the message from the previous holder
				m_people[i]->remove_message(*iter);
				//add message to new holder
				for (int k = 0; k < m_people.size(); ++k) {
					if (m_people[k]->get_name() == selected->get_name()) {
						m_people[k]->add_message(*iter);
					}
					

				}
				
			}
			

		}
		

	}
	

}

//print all the data
void Graph::print(std::ostream &ostr) const {
	ostr << std::endl;
	for (int i = 0; i < m_people.size(); ++i) {
		ostr << m_people[i]->get_name() << std::endl;
		ostr << "  friends: ";
		std::list<Person*> tmp_friends = m_people[i]->get_friends();
		std::list<Person*>::iterator tmp_iter;
		for (tmp_iter = tmp_friends.begin(); tmp_iter != tmp_friends.end(); ++tmp_iter) {
			ostr << (*tmp_iter)->get_name() << " ";
		}
		ostr << std::endl;
		ostr << "  messages: ";
		std::vector<std::string> tmp_vect;

		for (int j = 0; j < m_messages.size(); ++j) {
			
			if (m_messages[j]->get_owner() == m_people[i]) {
				
				tmp_vect.push_back(m_messages[j]->get_message());
				

				
			}



		}
		std::sort(tmp_vect.begin(), tmp_vect.end());
		for (int k = 0; k < tmp_vect.size(); ++k) {
			ostr << tmp_vect[k] << " ";

		}
		ostr << std::endl;
	}
	ostr << std::endl;
}

//helper function implementation (used in print_invite_list)

void helper_printer(Person *person, int n, int count, std::set<std::string> &answer) {
	if (count >= n) {
		return;
	}
	std::list<Person*>::const_iterator iter;
	std::list<Person*> tmp = person->get_friends();
	for (iter = tmp.begin(); iter != tmp.end(); ++iter) {
		answer.insert((*iter)->get_name());
		helper_printer(*iter, n, count + 1, answer);
	}

}

bool Graph::print_invite_list(std::ostream &ostr, const std::string &name, int n) const {
	std::set<std::string> answer;
	Person* p = find_person(name);
	if (p != NULL) {
		helper_printer(p, n, 0, answer);
		std::set < std::string>::iterator iter;
		ostr << "Invite list of " << name << " " << n << ": ";
		for (iter = answer.begin(); iter != answer.end(); ++iter) {
			ostr << *iter << " ";
		}
		ostr << std::endl;
		return true;
	}
	return false;
}

Person* Graph::find_person(const std::string &name) const {
	Person* answer;
	bool found = false;
	for (int i = 0; i < m_people.size(); ++i) {
		if (m_people[i]->get_name() == name) {
			answer = m_people[i];
			found = true;
		}
	}
	if (found == false) {
		//std::cerr << "Person was not found" << std::endl;
	}
	else {
		return answer;
	}
	
}

