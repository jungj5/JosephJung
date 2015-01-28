#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include "board.h"
#include <algorithm>

// ==================================================================
// ==================================================================
// Implementation of the Position class


// allows a position to be output to a stream
std::ostream& operator<<(std::ostream &ostr, const Position &p) {
  ostr << '(' << p.row << "," << p.col << ')';
  return ostr;
}


// equality and inequality comparision of positions
bool operator==(const Position &a, const Position &b) {
  return (a.row == b.row && a.col == b.col);
}
bool operator!=(const Position &a, const Position &b) {
  return !(a==b);
}


// ==================================================================
// ==================================================================
// Implementation of the Board class


// ===================
// CONSTRUCTOR
// ===================

Board::Board(int r, int c) { 
  // initialize the dimensions
  rows = r; 
  cols = c; 

  // allocate space for the contents of each grid cell
  board = std::vector<std::vector<char> >(rows,std::vector<char>(cols,' '));

  // allocate space for booleans indicating the presense of each wall
  // by default, these are false == no wall
  // (note that there must be an extra column of vertical walls
  //  and an extra row of horizontal walls)
  vertical_walls = std::vector<std::vector<bool> >(rows,std::vector<bool>(cols+1,false));
  horizontal_walls = std::vector<std::vector<bool> >(rows+1,std::vector<bool>(cols,false));

  // initialize the outermost edges of the grid to have walls
  for (int i = 0; i < rows; i++) {
    vertical_walls[i][0] = vertical_walls[i][cols] = true;
  }
  for (int i = 0; i < cols; i++) {
    horizontal_walls[0][i] = horizontal_walls[rows][i] = true;
  }
}


// ===================
// ACCESSORS related to board geometry
// ===================

// Query the existance of a horizontal wall
bool Board::getHorizontalWall(double r, int c) const {
  // verify that the requested wall is valid
  // the row coordinate must be a half unit
  assert (fabs((r - floor(r))-0.5) < 0.005);
  assert (r >= 0.4 && r <= rows+0.6);
  assert (c >= 1 && c <= cols);
  // subtract one and round down because the corner is (0,0) not (1,1)
  return horizontal_walls[floor(r)][c-1];
}

// Query the existance of a vertical wall
bool Board::getVerticalWall(int r, double c) const {
  // verify that the requested wall is valid
  // the column coordinate must be a half unit
  assert (fabs((c - floor(c))-0.5) < 0.005);
  assert (r >= 1 && r <= rows);
  assert (c >= 0.4 && c <= cols+0.6);
  // subtract one and round down because the corner is (0,0) not (1,1)
  return vertical_walls[r-1][floor(c)];
}


// ===================
// MODIFIERS related to board geometry
// ===================

// Add an interior horizontal wall
void Board::addHorizontalWall(double r, int c) {
  // verify that the requested wall is valid
  // the row coordinate must be a half unit
  assert (fabs((r - floor(r))-0.5) < 0.005);
  assert (r >= 0 && r <= rows);
  assert (c >= 1 && c <= cols);
  // verify that the wall does not already exist
  assert (horizontal_walls[floor(r)][c-1] == false);
  // subtract one and round down because the corner is (0,0) not (1,1)
  horizontal_walls[floor(r)][c-1] = true;
}

// Add an interior vertical wall
void Board::addVerticalWall(int r, double c) {
  // verify that the requested wall is valid
  // the column coordinate must be a half unit
  assert (fabs((c - floor(c))-0.5) < 0.005);
  assert (r >= 1 && r <= rows);
  assert (c >= 0 && c <= cols);
  // verify that the wall does not already exist
  assert (vertical_walls[r-1][floor(c)] == false);
  // subtract one and round down because the corner is (0,0) not (1,1)
  vertical_walls[r-1][floor(c)] = true;
}


// ===================
// PRIVATE HELPER FUNCTIONS related to board geometry
// ===================

char Board::getspot(const Position &p) const {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  // subtract one from each coordinate because the corner is (0,0) not (1,1)
  return board[p.row-1][p.col-1];
}


void Board::setspot(const Position &p, char a) {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <=  rows);
  assert (p.col >= 1 && p.col <= cols);
  // subtract one from each coordinate because the corner is (0,0) not (1,1)
  board[p.row-1][p.col-1] = a;
}

char Board::isGoal(const Position &p) const {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  // loop over the goals, see if any match this spot
  for (unsigned int i = 0; i < goals.size(); i++) {
    if (p == goals[i].pos) { return goals[i].which; }
  }
  // else return space indicating that no goal is at this location
  return ' ';
}


// ===================
// MODIFIERS related to robots
// ===================

// for initial placement of a new robot
void Board::placeRobot(const Position &p, char a) {

  // check that input data is reasonable
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  assert (getspot(p) == ' ');
  
  // robots must be represented by a capital letter
  assert (isalpha(a) && isupper(a));

  // make sure we don't already have a robot with the same name
  for (unsigned int i = 0; i < robots.size(); i++) {
    assert (robots[i].which != a);
  }

  // add the robot and its position to the vector of robots
  robots.push_back(Robot(p,a));

  // mark the robot on the board
  setspot(p,a);
}
//Set/modify a robot's position
void Board::setRobotPosition(int i, int row1, int col1, std::string is_reach) { 
	assert(i >= 0 && i < (int)numRobots());

		
		setspot(robots[i].pos, ' ');
		robots[i].pos.col = col1;
		robots[i].pos.row = row1;
		setspot(robots[i].pos, robots[i].which);
	
}

bool Board::moveRobot(int i, const std::string &direction, std::string is_reach) {
	
	/*check to see if robot can move in particular spot, if it can move it. If not, return false.*/

	//Get the initial position of the robot
	Position robot_position = getRobotPosition(i);

	//Boolean that will be returned by the function
	bool cant_move = false;
	if (direction == "north") {
		
		Position position_check = getRobotPosition(i);
		position_check.row -= 1;
		//If the robot can move to the next spot in the particular direction, move there and keep doing so until it can't.
		while ((robots[i].pos.row - 1 > 0) && (getHorizontalWall((double)robot_position.row - 0.5, (int)robot_position.col) == false) && (getspot(position_check) == ' ')) {			//Generally same code for all 
																																														//directions.
			//Update the positions of the robot.
			position_check.row -= 1;
			setRobotPosition(i, robot_position.row - 1, robot_position.col, is_reach);									
			
			//Set boolean to true if the robot moved
			cant_move = true;
			robot_position = getRobotPosition(i);
		}
	
	}
	if (direction == "south") {
		
		Position position_check = getRobotPosition(i);
		position_check.row += 1;

		while ((robots[i].pos.row + 1 <= getRows()) && (getHorizontalWall((double)robot_position.row + 0.5, (int)robot_position.col) == false) && (getspot(position_check) == ' ')) {
			
			
			position_check.row += 1;
			setRobotPosition(i, robot_position.row + 1, robot_position.col, is_reach);
			cant_move = true;
			robot_position = getRobotPosition(i);
		}
	}
	if (direction == "east") {
		Position position_check = getRobotPosition(i);
		position_check.col += 1;
		while ((robots[i].pos.col + 1 <= getCols()) && (getVerticalWall((int)robot_position.row, (double)robot_position.col + 0.5) == false) && (getspot(position_check) == ' ')) {
			
			position_check.col += 1;
			setRobotPosition(i, robot_position.row, robot_position.col + 1, is_reach);
			cant_move = true;
			robot_position = getRobotPosition(i);
		}
	}
	if (direction == "west") {
		Position position_check = getRobotPosition(i);
		position_check.col -= 1;
		while ((robots[i].pos.col - 1 > 0) && (getVerticalWall((int)robot_position.row, (double)robot_position.col - 0.5) == false) && (getspot(position_check) == ' ')) {
			
			position_check.col -= 1;
			setRobotPosition(i, robot_position.row, robot_position.col - 1, is_reach);
			cant_move = true;
			robot_position = getRobotPosition(i);
		}
	}
	return cant_move;
}


// ===================
// MODIFIER related to the puzzle goal
// ===================

void Board::addGoal(const std::string &gr, const Position &p) {

  // check that input data is reasonable
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);

  char goal_robot;
  if (gr == "any") {
    goal_robot = '?';
  } else {
    assert (gr.size() == 1);
    goal_robot = gr[0];
    assert (isalpha(goal_robot) && isupper(goal_robot));
  }

  // verify that a robot of this name exists for this puzzle
  if (goal_robot != '?') {
    int robot_exists = false;
    for (unsigned int i = 0; i < robots.size(); i++) {
      if (getRobot(i) == goal_robot) 
        robot_exists = true;
    }
    assert (robot_exists);
  }
  
  // make sure we don't already have a robot at that location
  assert (isGoal(p) == ' ');

  // add this goal label and position to the vector of goals
  goals.push_back(Goal(p,goal_robot));
}


// ==================================================================
// PRINT THE BOARD
// ==================================================================

void Board::print() {

  // print the column headings
  std::cout << " ";
  for (int j = 1; j <= cols; j++) {
    std::cout << std::setw(5) << j;
  }
  std::cout << "\n";
  
  // for each row
  for (int i = 0; i <= rows; i++) {

    // don't print row 0 (it doesnt exist, the first real row is row 1)
    if (i > 0) {
      
      // Note that each grid rows is printed as 3 rows of text, plus
      // the separator.  The first and third rows are blank except for
      // vertical walls.  The middle row has the row heading, the
      // robot positions, and the goals.  Robots are always uppercase,
      // goals are always lowercase (or '?' for any).
      std::string first = "  ";
      std::string middle;
      for (int j = 0; j <= cols; j++) {

        if (j > 0) { 
          // determine if a robot is current located in this cell
          // and/or if this is the goal
          Position p(i,j);
          char c = getspot(p);
          char g = isGoal(p);
          if (g != '?') g = tolower(g);
          first += "    ";
          middle += " "; 
          middle += c; 
          middle += g; 
          middle += " ";
        }

        // the vertical walls
        if (getVerticalWall(i,j+0.5)) {
          first += "|";
          middle += "|";
        } else {
          first += " ";
          middle += " ";
        }
      }

      // output the three rows
      std::cout << first << std::endl;
      std::cout << std::setw(2) << i << middle << std::endl;
      std::cout << first << std::endl;
    }

    // print the horizontal walls between rows
    std::cout << "  +";
    for (double j = 1; j <= cols; j++) {
      (getHorizontalWall(i+0.5,j)) ? std::cout << "----" : std::cout << "    ";
      std::cout << "+";
    }
    std::cout << "\n";
  }
}

void Board::reachability(std::vector<std::vector<int> > &visual_chars, const int &max_moves, const char &visualize, int current_turn) {

	//Set the initial position of the robot to 0
	if (current_turn == 1) {
		Position robot_position;
		for (int tmp = 0; tmp < robots.size(); ++tmp) {
			if (getRobot(tmp) == visualize) {
				robot_position = this->getRobotPosition(tmp);
				visual_chars[robot_position.row - 1][robot_position.col - 1] = 0;
				break;
			}
		}
	}


	if (current_turn < max_moves + 1 || max_moves == -1) {
		// for each robot
		for (int i = 0; i < robots.size(); ++i) {
			//Get the original positions of the robots before they get moved
			Position orig_position = this->getRobotPosition(i);
			if (this->moveRobot(i, "north", "reachability")) {
				//get the new positions of the robots now that they moved
				Position tmp_position = this->getRobotPosition(i);
				if (visualize == getRobot(i)) {
					//If the spot hasn't been used yet
					if (visual_chars[tmp_position.row - 1][tmp_position.col - 1] == '.') {				//All the code is roughly the same for 
						visual_chars[tmp_position.row - 1][tmp_position.col - 1] =  current_turn;		//each direction (North, South, East, West
					}
					//If the spot's number is less than the current turn
					else if ( visual_chars[tmp_position.row - 1][tmp_position.col - 1] > current_turn) {
						visual_chars[tmp_position.row - 1][tmp_position.col - 1] =  current_turn;
					}
				}
				//Call the function again
				reachability(visual_chars, max_moves, visualize, current_turn + 1);
				//Update the 2d vectors
				this->setspot(orig_position, getspot(tmp_position));
				this->setspot(tmp_position, ' ');
				//Update the position of the robot
				setRobotPosition(i, orig_position.row, orig_position.col, "reachability");
			}
			if (this->moveRobot(i, "south", "reachability")) {
			
				Position tmp_position = this->getRobotPosition(i);
				if (visualize == getRobot(i)) {
					if (visual_chars[tmp_position.row - 1][tmp_position.col - 1] == '.') {
						visual_chars[tmp_position.row - 1][tmp_position.col - 1] =  current_turn;
					}
					else if (visual_chars[tmp_position.row - 1][tmp_position.col - 1] > current_turn) {
						visual_chars[tmp_position.row - 1][tmp_position.col - 1] =  current_turn;
					}
				}
				reachability(visual_chars, max_moves, visualize, current_turn + 1);
				this->setspot(orig_position, getspot(tmp_position));
				this->setspot(tmp_position, ' ');
				setRobotPosition(i, orig_position.row, orig_position.col, "reachability");
			}
			if (this->moveRobot(i, "east", "reachability")) {
				
				Position tmp_position = this->getRobotPosition(i);
				if (visualize == getRobot(i)) {
					if (visual_chars[tmp_position.row - 1][tmp_position.col - 1] == '.') {
						visual_chars[tmp_position.row - 1][tmp_position.col - 1] =  current_turn;
					}
					else if ( visual_chars[tmp_position.row - 1][tmp_position.col - 1] > current_turn) {
						visual_chars[tmp_position.row - 1][tmp_position.col - 1] =  current_turn;
					}
				}
				reachability(visual_chars, max_moves, visualize, current_turn + 1);
				this->setspot(orig_position, getspot(tmp_position));
				this->setspot(tmp_position, ' ');
				setRobotPosition(i, orig_position.row, orig_position.col, "reachability");
			}
			if (this->moveRobot(i, "west", "reachability")) {
				
				Position tmp_position = this->getRobotPosition(i);
				if (visualize == getRobot(i)) {
					if (visual_chars[tmp_position.row - 1][tmp_position.col - 1] == '.') {
						visual_chars[tmp_position.row - 1][tmp_position.col - 1] = current_turn;
					}
					else if ( visual_chars[tmp_position.row - 1][tmp_position.col - 1] > current_turn) {
						visual_chars[tmp_position.row - 1][tmp_position.col - 1] = current_turn;
					}
				}
				reachability(visual_chars, max_moves, visualize, current_turn + 1);
				this->setspot(orig_position, getspot(tmp_position));
				this->setspot(tmp_position, ' ');
				setRobotPosition(i, orig_position.row, orig_position.col, "reachability");
			}
		}
		//Ending case
	}
	if (current_turn == max_moves + 1) {
		current_turn--;
		return;
	}

	//Check and performs appropriate actions when max_moves = -1 (unlimited)
	if (max_moves == -1) {
		bool infinite_incomplete = false;
		for (int k = 0; k < visual_chars.size(); ++k) {
			for (int l = 0; l < visual_chars[k].size(); ++l) {
				if (visual_chars[k][l] == '.') {
					infinite_incomplete = true;
				}
			}
		}
		if (infinite_incomplete == true) {
			return;
		}
	}
}




void Board::solve_board(const int &max_moves, int current_turn) {


	if (current_turn < max_moves + 1 || max_moves == -1) {
		
		// for each robot
		for (int i = 0; i < robots.size(); ++i) {
			//Get the original positions of the robots before they get moved
			Position orig_position = this->getRobotPosition(i);
			if (this->moveRobot(i, "north", "reachability")) {
				//get the new positions of the robots now that they moved
				Position tmp_position = this->getRobotPosition(i);
				std::string direction = "robot ";
				direction.append(1, robots[i].which);
				direction += " moves north";
				steps.push_back(direction);
				if (isGoal(robots[i].pos) == '?') {
					//std::cout << current_turn;
					//std::cout << robots[i].which << "hit north" << std::endl;
					//current_turn--;
					endings.push_back(steps);
					return;
					//break;
					//print();
				}
				else{
					//call the function again
					solve_board(max_moves, current_turn + 1);
				}
				//Update the 2d vectors
				this->setspot(orig_position, getspot(tmp_position));
				this->setspot(tmp_position, ' ');
				
				
				//Update the position of the robot
				setRobotPosition(i, orig_position.row, orig_position.col, "reachability");
				steps.pop_back();

			}
			if (this->moveRobot(i, "south", "reachability")) {

				Position tmp_position = this->getRobotPosition(i);
				std::string direction = "robot ";
				direction.append(1, robots[i].which);
				direction += " moves south";
				steps.push_back(direction);
				
				if (isGoal(robots[i].pos) == '?') {
					//print();
					//current_turn--;
					endings.push_back(steps);
					return;
					//break;
				}
				else{
					solve_board(max_moves, current_turn + 1);
				}
				this->setspot(orig_position, getspot(tmp_position));
				this->setspot(tmp_position, ' ');



				setRobotPosition(i, orig_position.row, orig_position.col, "reachability");
				steps.pop_back();
			}
			if (this->moveRobot(i, "east", "reachability")) {

				Position tmp_position = this->getRobotPosition(i);
				std::string direction = "robot ";
				direction.append(1, robots[i].which);
				direction += " moves east";
				steps.push_back(direction);

				if (isGoal(robots[i].pos) == '?') {
					endings.push_back(steps);
					//current_turn--;
					return;
					//break;
					//print();
				}
				else{
					solve_board(max_moves, current_turn + 1);
				}
				this->setspot(orig_position, getspot(tmp_position));
				this->setspot(tmp_position, ' ');
				setRobotPosition(i, orig_position.row, orig_position.col, "reachability");
				steps.pop_back();

			}
			if (this->moveRobot(i, "west", "reachability")) {

				Position tmp_position = this->getRobotPosition(i);
				std::string direction = "robot ";
				direction.append(1, robots[i].which);
				direction += " moves west";
				steps.push_back(direction);
				if (isGoal(robots[i].pos) == '?') {
					endings.push_back(steps);
					//current_turn--;
					return;
					//break;
					//print();
				}
				else{
					solve_board(max_moves, current_turn + 1);
				}
				this->setspot(orig_position, getspot(tmp_position));
				this->setspot(tmp_position, ' ');
				setRobotPosition(i, orig_position.row, orig_position.col, "reachability");
				steps.pop_back();

			}

		
		
		}

	}
	
	//Ending case
	if (current_turn == max_moves + 1) {
		current_turn--;
		return;
	}

	//Check and performs appropriate actions when max_moves = -1 (unlimited)
	/*
	if (max_moves == -1) {
		bool infinite_incomplete = false;
		for (int k = 0; k < visual_chars.size(); ++k) {
			for (int l = 0; l < visual_chars[k].size(); ++l) {
				if (visual_chars[k][l] == '.') {
					infinite_incomplete = true;
				}
			}
		}
		if (infinite_incomplete == true) {
			return;
		}
	}
	*/
}

void Board::output_solved_puzzle(const std::vector<std::vector<std::string> > &endings) {
	print();
	int i = 0;
	int counter = 0;
	
		for (int j = 0; j < endings[i].size(); ++j) {
			if (endings[i][j].find("A") != std::string::npos) {
				std::vector<Position> used_positionsA;
				used_positionsA.push_back(robots[0].pos);
				if (endings[i][j].find("north") != std::string::npos) {
					
					moveRobot(0, "north", "reachability");
					Position new_position = robots[0].pos;
					std::vector<Position>::iterator it = find(used_positionsA.begin(), used_positionsA.end(), new_position);
					
					if (it != used_positionsA.end()) {
						counter += 1;
						moveRobot(0, "south", "reachability");
					}
					else{
						used_positionsA.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("south") != std::string::npos) {
					moveRobot(0, "south", "reachability");
					Position new_position = robots[0].pos;
					std::vector<Position>::iterator it = find(used_positionsA.begin(), used_positionsA.end(), new_position);

					if (it != used_positionsA.end()) {
						counter += 1;
						moveRobot(0, "north", "reachability");
					}
					else{
						used_positionsA.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("east") != std::string::npos) {
					moveRobot(0, "east", "reachability");
					Position new_position = robots[0].pos;
					std::vector<Position>::iterator it = find(used_positionsA.begin(), used_positionsA.end(), new_position);

					if (it != used_positionsA.end()) {
						counter += 1;
						moveRobot(0, "west", "reachability");
					}
					else{
						used_positionsA.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("west") != std::string::npos) {
					moveRobot(0, "west", "reachability");
					Position new_position = robots[0].pos;
					std::vector<Position>::iterator it = find(used_positionsA.begin(), used_positionsA.end(), new_position);

					if (it != used_positionsA.end()) {
						counter += 1;
						moveRobot(0, "east", "reachability");
					}
					else{
						used_positionsA.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}

			}
			if (endings[i][j].find("B") != std::string::npos) {
				std::vector<Position> used_positionsB;
				used_positionsB.push_back(robots[1].pos);
				if (endings[i][j].find("north") != std::string::npos) {
					moveRobot(1, "north", "reachability");
					Position new_position = robots[1].pos;
					std::vector<Position>::iterator it = find(used_positionsB.begin(), used_positionsB.end(), new_position);

					if (it != used_positionsB.end()) {
						counter += 1;
						moveRobot(1, "south", "reachability");
					}
					else{
						used_positionsB.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("south") != std::string::npos) {
					moveRobot(1, "north", "reachability");
					Position new_position = robots[1].pos;
					std::vector<Position>::iterator it = find(used_positionsB.begin(), used_positionsB.end(), new_position);

					if (it != used_positionsB.end()) {
						counter += 1;
						moveRobot(1, "north", "reachability");
					}
					else{
						used_positionsB.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("east") != std::string::npos) {
					moveRobot(1, "east", "reachability");
					Position new_position = robots[1].pos;
					std::vector<Position>::iterator it = find(used_positionsB.begin(), used_positionsB.end(), new_position);

					if (it != used_positionsB.end()) {
						counter += 1;
						moveRobot(1, "west", "reachability");
					}
					else{
						used_positionsB.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("west") != std::string::npos) {
					moveRobot(1, "west", "reachability");
					Position new_position = robots[1].pos;
					std::vector<Position>::iterator it = find(used_positionsB.begin(), used_positionsB.end(), new_position);

					if (it != used_positionsB.end()) {
						counter += 1;
						moveRobot(1, "east", "reachability");
					}
					else{
						used_positionsB.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}

			}
			if (endings[i][j].find("C") != std::string::npos) {
				std::vector<Position> used_positionsC;
				used_positionsC.push_back(robots[2].pos);
				if (endings[i][j].find("north") != std::string::npos) {
					moveRobot(2, "north", "reachability");
					Position new_position = robots[2].pos;
					std::vector<Position>::iterator it = find(used_positionsC.begin(), used_positionsC.end(), new_position);

					if (it != used_positionsC.end()) {
						counter += 1;
						moveRobot(2, "south", "reachability");
					}
					else{
						used_positionsC.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("south") != std::string::npos) {
					moveRobot(2, "south", "reachability");
					Position new_position = robots[2].pos;
					std::vector<Position>::iterator it = find(used_positionsC.begin(), used_positionsC.end(), new_position);

					if (it != used_positionsC.end()) {
						counter += 1;
						moveRobot(2, "north", "reachability");
					}
					else{
						used_positionsC.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("east") != std::string::npos) {
					moveRobot(2, "east", "reachability");
					Position new_position = robots[2].pos;
					std::vector<Position>::iterator it = find(used_positionsC.begin(), used_positionsC.end(), new_position);

					if (it != used_positionsC.end()) {
						counter += 1;
						moveRobot(2, "west", "reachability");
					}
					else{
						used_positionsC.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}
				if (endings[i][j].find("west") != std::string::npos) {
					moveRobot(2, "west", "reachability");
					Position new_position = robots[2].pos;
					std::vector<Position>::iterator it = find(used_positionsC.begin(), used_positionsC.end(), new_position);

					if (it != used_positionsC.end()) {
						counter += 1;
						moveRobot(2, "east", "reachability");
					}
					else{
						used_positionsC.push_back(new_position);
						std::cout << endings[i][j] << std::endl;
						print();
					}
				}

			}
		}
		std::cout << "All goals are satisfied after " << endings[0].size() - counter << " moves" << std::endl;
	
}

/*
void Board::testrun() {
	Position test;
	test.row = 3;
	test.col = 6;
	std::cout << isGoal(test) << std::endl;
	std::cout << "^^^^^^^^^^^^^" << std::endl;
}
*/

// ==================================================================
// ==================================================================
