#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "polygons.h"
#include "cassert"


//helper function to get distances between points.
std::vector<double> getDistances(std::vector<Point> &points) {
	assert(points.size() > 0); //<-----OMG AN ASSERT THAT I MADE MYSELF =0
	std::vector<double> answer;
	for (int i = 0; i < points.size(); ++i) {
		if (i != points.size() - 1) {
			double being_put_in = DistanceBetween(points[i], points[i + 1]);
			answer.push_back(being_put_in);
		}
		else {
			double being_put_in = DistanceBetween(points[i], points[0]);
			answer.push_back(being_put_in);
		}
	}
	return answer;
}

//helper function to get vectors of polygon
std::vector<Vector> getVectors(std::vector<Point> &points) {
	std::vector<Vector> answer;
	for (int i = 0; i < points.size(); ++i) {
		if (i != points.size() -1) {
			Vector being_put_in = Vector(points[i], points[i + 1]);
			answer.push_back(being_put_in);
		}
		else {
			Vector being_put_in = Vector(points[i], points[0]);
			answer.push_back(being_put_in);
		}
	}
	return answer;
}

std::vector<double> getAngles(std::vector<Point> &points) {
	std::vector<double> answer;
	for (int i = 0; i < points.size(); ++i) {
		if (i == points.size() - 2) {
			double angle = Angle(points[i], points[i + 1], points[0]);
			answer.push_back(angle);
		}
		else if (i == points.size() - 1) {
			double angle = Angle(points[i], points[0], points[1]);
			answer.push_back(angle);
		}
		else {
			double angle = Angle(points[i], points[i + 1], points[i + 2]);
			answer.push_back(angle);
		}

	}
	return answer;
}


bool Polygon::HasTwoEqualSides() {
	std::vector<double> tmp = getDistances(points);
	for (int i = 0; i < tmp.size(); ++i) {
		for (int j = 0; j < tmp.size(); ++j) {
			if (i != j) {
				if (tmp[i] == tmp[j]) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Polygon::HasParallelSides() {
	std::vector<Vector> tmp = getVectors(points);
	for (int i = 0; i < tmp.size(); ++i) {
		for (int j = 0; j < tmp.size(); ++j) {
			if (i != j) {
				if (Parallel(tmp[i], tmp[j]) == true) {
					return true;
				}
			}
		}

	}
	return false;
}

bool Polygon::IsAParallelogram() {
	bool is_found1 = false;
	bool is_found2 = false;
	bool is_found3 = false;
	bool is_found4 = false;
	std::vector<Vector> tmp = getVectors(points);

	std::vector<double> tmp1 = getDistances(points);
	is_found1 = Parallel(tmp[0], tmp[2]);
	is_found2 = Parallel(tmp[1], tmp[3]);
	is_found3 = EqualSides(tmp1[0], tmp1[2]);
	is_found4 = EqualSides(tmp1[1], tmp1[3]);


	if (is_found1 == true && is_found2 == true && is_found3 == true && is_found4 == true) {
		return true;
	}
	else{
		return false;
	}
	
}


bool Polygon::HasAllEqualSides() {
	std::vector<double> tmp = getDistances(points);
	double compare_value = tmp[0];
	for (int i = 0; i < tmp.size(); ++i) {
		if (!EqualSides(tmp[0], tmp[i])) {
			return false;
		}
	}
	return true;

}

bool Polygon::HasAllEqualAngles() {
	double compare_value = Angle(points[0], points[1], points[2]);
	for (int i = 0; i < points.size(); ++i) {
		if (i == points.size() - 2) {
			if (EqualAngles(Angle(points[points.size() - 2], points[points.size() - 1], points[0]), compare_value) == false) {
				return false;
			}
			
		}
		else if (i == points.size() - 1) {
			if (EqualAngles(Angle(points[points.size() - 1], points[0], points[1]), compare_value) == false) {
				return false;
			}
		}
		else {
			if (EqualAngles(Angle(points[i], points[i + 1], points[i + 2]), compare_value) == false) {
				return false;
			}
		}
	}
	return true;
}

bool Polygon::HasAdjacentEqualAngles() {
	std::vector<double> tmp = getAngles(points);
	for (int i = 0; i < tmp.size(); ++i) {
		if (i == points.size() - 1) {
			if (EqualAngles(tmp[i], tmp[0]) == true) {
				return true;
			}
		}
		else {
			if (EqualAngles(tmp[i], tmp[i + 1]) == true) {
				return true;
			}
		}
	}
	return false;
}

bool Polygon::HasARightAngle() {
	for (int i = 0; i < points.size(); ++i) {
		if (i == points.size() - 2) {
			if (RightAngle(Angle(points[points.size() - 2], points[points.size() - 1], points[0])) == true) {
				return true;
			}

		}
		else if (i == points.size() - 1) {
			if (RightAngle(Angle(points[points.size() - 1], points[0], points[1])) == true) {
				return true;
			}
		}
		else {
			if (RightAngle(Angle(points[i], points[i + 1], points[i + 2])) == true) {
				return true;
			}
		}
	}
	return false;
}

bool Polygon::HasAnObtuseAngle() {
	for (int i = 0; i < points.size(); ++i) {
		if (i == points.size() - 2) {
			if (ObtuseAngle(Angle(points[points.size() - 2], points[points.size() - 1], points[0])) == true) {
				return true;
			}

		}
		else if (i == points.size() - 1) {
			if (ObtuseAngle(Angle(points[points.size() - 1], points[0], points[1])) == true) {
				return true;
			}
		}
		else {
			if (ObtuseAngle(Angle(points[i], points[i + 1], points[i + 2])) == true) {
				return true;
			}
		}
	}
	return false;
}

bool Polygon::HasAnAcuteAngle() {
	for (int i = 0; i < points.size(); ++i) {
		if (i == points.size() - 2) {
			if (AcuteAngle(Angle(points[points.size() - 2], points[points.size() - 1], points[0])) == true) {
				return true;
			}

		}
		else if (i == points.size() - 1) {
			if (AcuteAngle(Angle(points[points.size() - 1], points[0], points[1])) == true) {
				return true;
			}
		}
		else {
			if (AcuteAngle(Angle(points[i], points[i + 1], points[i + 2])) == true) {
				return true;
			}
		}
	}
	return false;

}

bool Polygon::IsConvex() {
	for (int i = 0; i < points.size(); ++i) {
		if (i == points.size() - 2) {
			if (ReflexAngle(Angle(points[points.size() - 2], points[points.size() - 1], points[0])) == true) {
				return false;
			}

		}
		else if (i == points.size() - 1) {
			if (ReflexAngle(Angle(points[points.size() - 1], points[0], points[1])) == true) {
				return false;
			}
		}
		else {
			if (ReflexAngle(Angle(points[i], points[i + 1], points[i + 2])) == true) {
				return false;
			}
		}
	}
	return true;

}

bool Polygon::IsConcave() {
	for (int i = 0; i < points.size(); ++i) {
		if (i == points.size() - 2) {
			if (ReflexAngle(Angle(points[points.size() - 2], points[points.size() - 1], points[0])) == true) {
				return true;
			}

		}
		else if (i == points.size() - 1) {
			if (ReflexAngle(Angle(points[points.size() - 1], points[0], points[1])) == true) {
				return true;
			}
		}
		else {
			if (ReflexAngle(Angle(points[i], points[i + 1], points[i + 2])) == true) {
				return true;
			}
		}
	}
	return false;
}



