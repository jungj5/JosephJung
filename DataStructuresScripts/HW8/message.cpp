#include "message.h"
 

//Message class implementation

//constructor
Message::Message(const std::string &msg, Person *person) {
	m_owner = person;
	m_message = msg;
}

bool Message::pass_message(Person *person) {
	//check to see if person exists
	//if he/she does, change m_owner and return true
	//if not return false
	std::list<Person*>::iterator iter;
	std::list<Person*> tmp_list = get_owner()->get_friends();
	for (iter == tmp_list.begin(); iter != tmp_list.end(); ++iter) {
		if ((*iter)->get_name() == person->get_name()) {
			m_owner = person;
			return true;
		}
	}
	return false;


}