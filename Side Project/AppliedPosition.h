#include <iostream>
#include <string>
#include <list>
#include <fstream>

#ifndef _APPLIEDPOSITION_H_
#define _APPLIEDPOSITION_H_


class AppliedPosition {
public:
	//Constructor
	AppliedPosition(const std::string& company, const std::string& position_title, const std::string& jobID, const std::string& date_applied, const std::string& position_type) {
		company_ = company;
		position_title_ = position_title;
		jobID_ = jobID;
		date_applied_ = date_applied;
		position_type_ = position_type;
	}
	
	//Accessors
	std::string getCompany() const {
		return company_;
	}

	std::string getPositionTitle() const {
		return position_title_;
	}

	std::string getJobID() const {
		return jobID_;
	}

	std::string getDateApplied() const {
		return date_applied_;
	}

	std::string getPositionType() const {
		return position_type_;
	}



private:
	std::string company_;
	std::string position_title_;
	std::string jobID_;
	std::string date_applied_;
	std::string position_type_;

};


#endif /* _APPLIEDPOSITION_H_*/