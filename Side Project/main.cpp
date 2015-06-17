#include "stdlib.h"
#include <iostream>
#include <string>
#include <list>
#include "AppliedPosition.h"

int main() {

	AppliedPosition test = AppliedPosition("Google", "Software Developer", "12345", "5/28/15", "internship");


	std::cout << "Company name: " + test.getCompany() << std::endl;
	std::cout << "Position Title: " + test.getPositionTitle() << std::endl;
	std::cout << "Job ID: " + test.getJobID() << std::endl;
	std::cout << "Date Applied: " + test.getDateApplied() << std::endl;
	std::cout << "Position Type: " + test.getPositionType() << std::endl;
	return 0;

}
