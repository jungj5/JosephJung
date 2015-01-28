#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

#include "utilities.h"

class Polygon {
public:
	Polygon(const std::string &name_, const std::vector<Point> &points_) : name(name_), points(points_) {}

	//Accessor
	std::string getName() { return name; }


	//name of polygon
	std::string name;
	
	//vector of points
	std::vector<Point> points;

	//functions
	virtual bool HasAllEqualSides();
	virtual bool HasTwoEqualSides();
	virtual bool HasAllEqualAngles();
	virtual bool HasARightAngle();
	virtual bool HasAnObtuseAngle();
	virtual bool HasAnAcuteAngle();
	virtual bool IsConvex();
	virtual bool IsConcave();
	virtual bool HasParallelSides();
	virtual bool IsAParallelogram();
	virtual bool HasAdjacentEqualAngles();
};


//Triangle classes


class Triangle: public Polygon {
public:
	Triangle(const std::string &name_, const std::vector<Point> &points_) : Polygon(name_, points_) {
		if (points_.size() != 3) throw(1);
	}
};

class ObtuseTriangle : virtual public Triangle {
public:
	ObtuseTriangle(const std::string &name_, const std::vector<Point> &points_) : Triangle(name_, points_) {
		if (HasAnObtuseAngle() == false) throw(1);
	}
};
class IsoscelesTriangle : virtual public Triangle {
public:
	IsoscelesTriangle(const std::string &name_, const std::vector<Point> &points_) : Triangle(name_, points_) {
		if (HasTwoEqualSides() == false) throw(1);
	}
};

class RightTriangle : virtual public Triangle {
public:
	RightTriangle(const std::string &name_, const std::vector<Point> &points_) : Triangle(name_, points_) {
		if (HasARightAngle() == false) throw(1);
	}
};

class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle {
public:
	IsoscelesRightTriangle(const std::string &name_, const std::vector<Point> &points_) : Triangle(name_, points_), IsoscelesTriangle(name_, points_), RightTriangle(name_, points_) {

	}
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
	EquilateralTriangle(const std::string &name_, const std::vector<Point> &points_) : Triangle(name_, points_), IsoscelesTriangle(name_, points_) {
		if (HasAllEqualSides() == false || HasAllEqualAngles() == false) throw(1);
	}
};


class IsoscelesObtuseTriangle : public ObtuseTriangle, public IsoscelesTriangle {
public:
	IsoscelesObtuseTriangle(const std::string &name_, const std::vector<Point> &points_) : Triangle(name_, points_), ObtuseTriangle(name_, points_), IsoscelesTriangle(name_, points_) {

	}
};

//############################################################################################################################################################################
//############################################################################################################################################################################
//																			Quadrilateral classes.

class Quadrilateral : public Polygon {
public:
	Quadrilateral(const std::string &name_, const std::vector<Point> &points_) : Polygon(name_, points_) {
		if (points_.size() != 4) throw(1);
	}
};

class Kite : virtual public Quadrilateral {
public:
	Kite(const std::string &name_, const std::vector<Point> &points_) : Quadrilateral(name_, points_) {
		if (IsConcave() == true || HasTwoEqualSides() == false) throw(1);
	}
};

class Trapezoid : virtual public Quadrilateral {
public:
	Trapezoid(const std::string &name_, const std::vector<Point> &points_) : Quadrilateral(name_, points_) {
		if (HasParallelSides() == false) throw(1);
	}
};

class Parallelogram : virtual public Trapezoid {
public:
	Parallelogram(const std::string &name_, const std::vector<Point> &points_) : Quadrilateral(name_, points_), Trapezoid(name_, points_) {
		if (IsAParallelogram() == false) throw(1);
	}
};

class IsoscelesTrapezoid : virtual public Trapezoid {
public:
	IsoscelesTrapezoid(const std::string &name_, const std::vector<Point> &points_) : Quadrilateral(name_, points_), Trapezoid(name_, points_) {
		if (HasTwoEqualSides() == false || HasAdjacentEqualAngles() == false) throw(1);
	}
};


class Arrow : public Quadrilateral {
public:
	Arrow(const std::string &name_, const std::vector<Point> &points_) : Quadrilateral(name_, points_) {
		if (IsConcave() == false) throw(1);
	}
};


class Rectangle : virtual public Parallelogram, public IsoscelesTrapezoid {
public:
	Rectangle(const std::string &name_, const std::vector<Point> &points_) : Quadrilateral(name_, points_), Trapezoid(name_, points), Parallelogram(name_, points_), IsoscelesTrapezoid(name_, points_) {
		if (HasAllEqualAngles() == false) throw(1);
	}
};

class Rhombus : virtual public Parallelogram, public Kite {
public:
	Rhombus(const std::string &name_, const std::vector<Point> &points_) : Quadrilateral(name_, points_), Trapezoid(name_, points_), Parallelogram(name_, points_), Kite(name_, points_) {
		if (HasAllEqualSides() == false) {
			throw(1);
		}
	}
};

class Square : public Rectangle, public Rhombus {
public:
	Square(const std::string &name_, const std::vector<Point> &points_) : Parallelogram(name_, points_), Trapezoid(name_, points_), Quadrilateral(name_, points_), Rectangle(name_, points_), Rhombus(name_, points_) {
		if (HasAllEqualSides() == false) throw(1);
		if (HasAllEqualAngles() == false) throw(1);
	}
};