#include "person.h"
#include <iostream>
//Person class implementation



bool Person::add_friend(Person *person) {
	
	std::list<Person*>::iterator iter;
	//if person is already in the list, don't add him and return false.
	for (iter = m_friends.begin(); iter != m_friends.end(); ++iter) {
		if ((*iter)->get_name() == person->get_name()) {
			//std::cerr << "friend already in list!" << std::endl;
			return false;
		}
	}
	//add the person
	m_friends.push_back(person);
	return true;
}


bool Person::remove_friend(Person* person) {
	std::list<Person*>::iterator iter;
	//find person in list and remove the son of a gun! >=D
	for (iter = m_friends.begin(); iter != m_friends.end(); ++iter) {
		if ((*iter)->get_name() == person->get_name()) {
			m_friends.remove(person);
			return true;
		}
	}
	//std::cerr << "This person is not on the friends list!" << std::endl;
	return false;
}


bool Person::add_message(Message *message) {
	std::list<Message*>::iterator iter;
	//check to see if the message is already in the list. Return false if it is.
	for (iter = m_messages.begin(); iter != m_messages.end(); ++iter) {
		if ((*iter)->get_message() == message->get_message()) {
			//std::cerr << "message already in list!" << std::endl;
			return false;
		}
	}

	//add message to system
	m_messages.push_back(message);
	return true;
}


bool Person::remove_message(Message *message) {
	std::list<Message*>::iterator iter;
	//find the message in the graph and delete it once found.
	for (iter = m_messages.begin(); iter != m_messages.end(); ++iter) {
		if ((*iter)->get_message() == message->get_message()) {
			m_messages.remove(message);
			return true;
		}
	}
	//std::cerr << "Message not found in database" << std::endl;
	return false;
}

bool Person::is_friend(Person* person) const {
	bool found = false;
	//check to see if person is on friend list and return true if he/she is.
	std::list<Person*>::const_iterator iter;
	for (iter = m_friends.begin(); iter != m_friends.end(); ++iter) {
		if ((*iter)->get_name() == person->get_name()) {
			found = true;
		}
	}
	return found;
}