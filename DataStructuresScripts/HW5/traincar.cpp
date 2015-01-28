// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
//    This file provides the code for ASCII art printing of trains.
//    You should implement all of the functions prototyped in
//    "traincar_prototypes.h" in this file.
//
// =======================================================================


#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "traincar.h"
#include <cmath>
#include <stdlib.h>
// =======================================================================
// =======================================================================

// This helper function checks that the forward and backward pointers
// in a doubly-linked structure are correctly and consistently assigned.
void SanityCheck(TrainCar* train) {
  // an empty train is valid
  if (train == NULL) return;
  assert (train->prev == NULL);
  TrainCar *tmp = train;
  while (tmp->next != NULL) {
    // the next train better point back to me
    assert (tmp->next->prev == tmp);
    tmp = tmp->next;
  }
}


// This helper function prints one of the 5 rows of the TrainCar ASCII art
void PrintHelper(TrainCar* t, int which_row) {
  if (t == NULL) {
    // end of the line
    std::cout << std::endl;
    return;
  }

  if (which_row == 0) {
    // the top row only contains "smoke" for engine traincars
    if (t->isEngine()) {
      std::cout << "     ~~~~";
    } else {
      std::cout << "         ";
    }
  } else if (which_row == 1) {
    // the 2nd row only contains the smoke stack for engine traincars
    if (t->isEngine()) {
      std::cout << "    ||   ";
    } else {
      std::cout << "         ";
    }
  } else if (which_row == 2) {
    // the 3rd row contains the ID for each traincar
    // (and engine traincars are shaped a little differently)
    if (t->isEngine()) {
      std::cout << "   " << std::setw(6) << std::setfill('-') << t->getID();
    } else {
      std::cout << std::setw(9) << std::setfill('-') << t->getID();
    }
    std::cout << std::setfill(' ');
  } else if (which_row == 3) {
    // the 4th row is different for each TrainCar type
    if (t->isEngine()) {
      std::cout << " / ENGINE";
    } else if (t->isFreightCar()) {
      // freight cars display their weight
      std::cout << "|" << std::setw(5) << t->getWeight() << "  |";
    } else if (t->isPassengerCar()) {
      // passenger cars are simple empty boxes
      std::cout << "|       |";
    } else if (t->isDiningCar()) {
      std::cout << "|  dine |";
    } else {
      assert (t->isSleepingCar());
      std::cout << "| sleep |";
    }
  } else if (which_row == 4) {
    // final row is the same for all cars, just draw the wheels
    std::cout << "-oo---oo-";
  }

  // between cars display the '+' link symbol on the 5th row 
  // (only if there is a next car)
  if (t->next != NULL) {
    if (which_row == 4) {
      std::cout << " + ";
    } else {
      std::cout << "   ";
    }
  }

  // recurse to print the rest of the row
  PrintHelper(t->next, which_row);
}

//implemented functions
void CountEnginesAndTotalWeight
(TrainCar*& head, int &total_weight,
int &num_engines, int &num_freight_cars, int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars) {
	num_engines = 0;
	num_freight_cars = 0;
	total_weight = 0;
	num_passenger_cars = 0;
	num_dining_cars = 0;
	num_sleeping_cars = 0;
	for (TrainCar* tmp = head; tmp != NULL; tmp = tmp->next) {
		if (tmp->isEngine() == true) {
			num_engines += 1;
		}
		if (tmp->isFreightCar() == true) {
			num_freight_cars += 1;
		}
		if (tmp->isPassengerCar() == true) {
			num_passenger_cars += 1;
		}
		if (tmp->isDiningCar() == true) {
			num_dining_cars += 1;
		}
		if (tmp->isSleepingCar() == true) {
			num_sleeping_cars += 1;
		}
	}
	total_weight = (num_engines * 150) + (num_freight_cars * 50) + (num_passenger_cars * 50) + (num_dining_cars * 50) + (num_sleeping_cars * 50);
	 
}

float CalculateSpeed(TrainCar *& head) {
	TrainCar *tmp;
	float weight = 0;
	float hp = 0;
	for (tmp = head; tmp != NULL; tmp = tmp->next) {
		if (tmp->isEngine() == true) {
			weight = weight + 150.0;
			hp = hp + 3000.0;

		}
		else {
			weight = weight + tmp->getWeight();
		}
	}
	float speed = (hp * 550.0 * 3600.0) / (2000.0 * .02 * 5280.0 * weight);
	return speed;
}

float AverageDistanceToDiningCar(TrainCar *& head) {
	
	TrainCar* tmp;
	TrainCar* tmp2;
	TrainCar* tmp3;
	int pass_ID;
	int dine_ID;
	bool found_engine = false;
	int engine_ID;
	int pass_count;
	int total_distance = 0;
	float return_value;
	for (tmp = head; tmp != NULL; tmp = tmp->next) {
		if (tmp->isPassengerCar() == true) {
			pass_ID = tmp->getID();
			for (tmp2 = head; tmp2 != NULL; tmp2 = tmp2->next) {
				if (tmp2->isDiningCar() == true) {
					dine_ID = tmp2->getID();
					for (tmp3 = head; tmp3 != NULL; tmp3 = tmp3->next) {
						if (tmp3->isEngine() == true) {
							found_engine = true;
							engine_ID = tmp3->getID();
							if ((engine_ID > dine_ID && engine_ID < pass_ID) || (engine_ID < dine_ID && engine_ID > pass_ID)) {
								return -1;
							}
							else {
								total_distance += abs(dine_ID - pass_ID);
							}

						}
					} 
				}


			}
			pass_count += 1;

		}
		
	}
	return_value = total_distance / pass_count;
	return return_value;
}

int ClosestEngineToSleeperCar(TrainCar *& head) {
	TrainCar* tmp;
	int engine_ID;
	int car_ID;
	int closest = 9999;
	bool sleeper_found = false;
	for (tmp = head; tmp != NULL; tmp = tmp->next) {
		
		if (tmp->isSleepingCar() == true) {
			sleeper_found = true;
			car_ID = tmp->getID();
			TrainCar* tmp2;
			for (tmp2 = head; tmp2 != NULL; tmp2 = tmp2->next) {
				if (tmp2->isEngine() == true) {
					engine_ID = tmp2->getID();
					if (abs(car_ID - engine_ID < closest)) {
						closest = abs(engine_ID - car_ID);
					}

				}
			}

		}

	}
	if (sleeper_found == true) {
		return closest;
	}

}


  
void PrintTrain(TrainCar* train) {
  
  if (train == NULL) { 
    std::cout << "PrintTrain: empty train!" << std::endl; 
    return; 
  }

  // Print each of the 5 rows of the TrainCar ASCII art
  PrintHelper(train, 0);
  PrintHelper(train, 1);
  PrintHelper(train, 2);
  PrintHelper(train, 3);
  PrintHelper(train, 4);


  // UNCOMMENT THESE ADDITIONAL STATISTICS AS YOU WORK

  int total_weight,num_engines,num_freight_cars,num_passenger_cars,num_dining_cars,num_sleeping_cars;
  CountEnginesAndTotalWeight
    (train, total_weight,
     num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars);
  //total_weight = (num_engines * 150) + (num_freight_cars * 50) + (num_passenger_cars * 50) + (num_dining_cars * 50) + (num_sleeping_cars * 50); //<-----Made that
  int total_cars = num_engines+num_freight_cars+num_passenger_cars+num_dining_cars+num_sleeping_cars;
  float speed = CalculateSpeed(train);
  std::cout << "#cars = " << total_cars;
  std::cout << ", total weight = " << total_weight;
  std::cout << ", speed on 2% incline = " << std::setprecision(1) << std::fixed << speed;

  // If there is at least one passenger car, print the average
  // distance to dining car statistic
  if (num_passenger_cars > 0) {
    float dist_to_dining = AverageDistanceToDiningCar(train);
    if (dist_to_dining < 0) {
      // If one or more passenger cars are blocked from accessing the
      // dining car (by an engine car) then the distance is infinity!
      std::cout << ", avg distance to dining = inf";
    } else {
      std::cout << ", avg distance to dining = " << std::setprecision(1) << std::fixed << dist_to_dining;
    }
  }

  // If there is at least one sleeping car, print the closest engine
  // to sleeper car statistic
  if (num_sleeping_cars > 0) {
    int closest_engine_to_sleeper = ClosestEngineToSleeperCar(train);
    std::cout << ", closest engine to sleeper = " << closest_engine_to_sleeper;
  }

  std::cout << std::endl;
  
}




void PushBack(TrainCar* &head, TrainCar* car) {
	//if the list is empty, make car first value in list
	if (head == NULL) {
		head = car;
		head->next = NULL;
		head->prev = NULL;
		
	}
	else {
		TrainCar *tmp;
		//go to end of current list
		for (tmp = head; tmp->next != NULL; tmp = tmp->next) {

		}

		tmp->next = car;
		car->prev = tmp;
		car->next = NULL;

	}
	
}
float Speed(TrainCar *& head) {
	TrainCar *tmp;
	float weight = 0;
	float hp = 0;
	for (tmp = head; tmp != NULL; tmp = tmp->next) {
		if (tmp->isEngine() == true) {
			weight = weight + 150.0;
			hp = hp + 3000.0;

		}
		else {
			weight = weight + tmp->getWeight();
		}
	}
	float speed = (hp * 550.0 * 3600.0) / (2000.0 * .02 * 5280.0 * weight);
	return speed;
}

std::vector<TrainCar*> ShipFreight(TrainCar * &engines, TrainCar * &freight, int min_speed, int max_cars) {
	std::vector<TrainCar*> TrainCars;
	if (engines == NULL || freight == NULL) {
		return TrainCars;
	}
	
	int i = 0;
	int engine_count = 0;
	TrainCar *engine_counter;
	for (engine_counter = engines; engine_counter->next != NULL; engine_counter = engine_counter->next) {
		engine_count += 1;
	}

	int freight_count = 0;
	TrainCar *freight_counter;
	for (freight_counter = freight; freight_counter->next != NULL; freight_counter = freight_counter->next) {
		
		freight_count += 1;
	}

	

		while (engines != NULL && freight_count > 0) {
			//Allocate the first engine
			TrainCar *first_engine = engines;
			engines = engines->next;
			if (first_engine->next != NULL) {
				first_engine->next->prev = NULL;
			}
			first_engine->next = NULL;
			i += 1;
			engine_count -= 1;



			while (Speed(first_engine) > min_speed && i < max_cars) {
				//if there are no more freight cars
				if (freight == NULL) {
					break;
				}
				else{
					//Allocate freight
					TrainCar *first_freight = freight;
					
					freight = freight->next;
					if (first_freight->next != NULL) {
						first_freight->next->prev = NULL;
					}
					first_freight->next = NULL;
					PushBack(first_engine, first_freight);
					i += 1;
					freight_count -= 1;
				}

			}
			if (Speed(first_engine) < min_speed) {
				TrainCar* popped = PopBack(first_engine);
				PushBack(freight, popped);
				freight_count += 1;
			}

			TrainCars.push_back(first_engine);
			i = 0;
		}






	return TrainCars;

}





//Delete function
void DeleteAllCars(TrainCar * & head) {

	//if no traincars
	if (head == NULL) {
		return;

	}
	else {
		TrainCar *tmp;
		tmp = head->next;
		while (head != NULL) {
			delete head;
			head = tmp;
			if (tmp != NULL) {
				tmp = tmp->next;
			}
		}

	}
}


TrainCar* PopBack(TrainCar * & head) {
	int total_weight, num_engines, num_freight_cars, num_passenger_cars, num_dining_cars, num_sleeping_cars;
	CountEnginesAndTotalWeight
		(head, total_weight,
		 num_engines, num_freight_cars, num_passenger_cars, num_dining_cars,  num_sleeping_cars);
	int total_length = num_engines + num_freight_cars + num_passenger_cars + num_dining_cars + num_sleeping_cars;

	TrainCar *tmp;
	for (tmp = head; tmp->next != NULL; tmp = tmp->next) {

	}
	tmp->prev->next = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	
	//Take last TrainCar off of a train and return it.
	return tmp;
	
}


void Separate(TrainCar *& head1, TrainCar *& head2, TrainCar *& head3) {
	if (head1 == NULL) {
		return;
	}

	TrainCar* tmp1;
	TrainCar* engine1;
	TrainCar* engine2;
	TrainCar* tmp2;
	TrainCar* tmp3;
	TrainCar* counter;
	TrainCar* tmp4;
	int i = 0;
	int engine1_ID;
	int engine2_ID;
	int train_length = 0;
	int count = 0;

	//these counters find where the engines are in the train.
	int engine1_counter = 0;
	int engine2_counter = 0;

	//find the length of the train.
	for (counter = head1; counter != NULL; counter = counter->next) {
		train_length += 1;
	}


	//find the first engine in the train. (closest to the front)
	for (tmp1 = head1; tmp1 != NULL; tmp1 = tmp1->next) {
		engine1_counter += 1;
		if (tmp1->isEngine() == true) {
			engine1_ID = tmp1->getID();
			engine1 = tmp1;

			break;
		}
		
	}
	//find the second engine in the train. (second closest to the front)
	for (tmp2 = head1; tmp2 != NULL; tmp2 = tmp2->next) {
		engine2_counter += 1;
		if (tmp2->isEngine() == true && tmp2->getID() != engine1_ID) {
			engine2_ID = tmp2->getID();	
			engine2 = tmp2;
			break;
		}
	}

	//keep count of where the halfway mark for the train is.
	for (tmp4 = head1; count >= (train_length / 2); tmp4 = tmp4->next) {
		count += 1;
	}
			//If both engines are within the first half of the train.
	
			if (engine1_counter < (train_length / 2) && engine2_counter < (train_length / 2)) {
				TrainCar* engine_tmp;
				TrainCar* engine_next;
				TrainCar* engine_prev;
				
				for (engine_tmp = head1; engine_tmp != NULL; engine_tmp = engine_tmp->next) {
					if (engine_tmp == engine2) {
						engine_next = engine_tmp->next;
						engine_prev = engine_tmp->prev;
						break;
					}
				}
				/*
				engine2->prev->next = NULL;
				engine2->next->prev = NULL;
				engine2->next = NULL;
				engine2->prev = NULL;
				PushBack(head1, engine2);
				*/
				engine_next->prev = engine_prev;
				engine_prev->next = engine_next;
				
				PushBack(head1, engine_tmp);
				/*
				engine_tmp->prev = head1;
				engine_tmp->prev = NULL;
				
				head1->prev = engine_tmp;
				*/
				head2 = head1;

				for (tmp3 = head1; i <= (train_length / 2); tmp3 = tmp3->next) {
					i += 1;
				}
				if (train_length % 2 == 0) {
					TrainCar* ranoutofnames;
					head3 = tmp3->prev;
					if (head3->prev != NULL) {
						ranoutofnames = head3->prev;
						ranoutofnames->next = NULL;
					}
					/*
					head3 = tmp3;
					tmp3 = tmp3->prev;
					tmp3->next->prev = NULL;
					tmp3->next = NULL;
					head2 = head1;
					*/

					head3->prev = NULL;
				}
				else {
					head3 = tmp3;
					TrainCar* yetanothertmp;
					if (head3->prev != NULL) {
						yetanothertmp = head3->prev;
						yetanothertmp->next = NULL;
					}
					head3->prev = NULL;

				}



			}
			//if both engines are in the second half of the train.
			else if (engine1_counter > (train_length / 2) && engine2_counter > (train_length / 2)) {
				TrainCar* engine_tmp;
				TrainCar* engine_next;
				TrainCar* engine_prev;
				for (engine_tmp = head1; engine_tmp != NULL; engine_tmp = engine_tmp->next) {
					if (engine_tmp == engine1) {
						engine_next = engine_tmp->next;
						
						engine_prev = engine_tmp->prev;
						
						break;
					}
				}
				engine_next->prev = engine_prev;
				engine_prev->next = engine_next;
				
				engine_tmp->next = head1;
				engine_tmp->prev = NULL;
				head1->prev = engine_tmp;
				
				head2 = engine_tmp;


				for (tmp3 = head2; i <= (train_length / 2); tmp3 = tmp3->next) {
					i += 1;
				}
				if (train_length % 2 == 0) {
					TrainCar* ranoutofnames;
					

					head3 = tmp3->prev;
					if (head3->prev != NULL) {
						ranoutofnames = head3->prev;
						ranoutofnames->next = NULL;
					}
					
					head3->prev = NULL;


				}
				else {
					head3 = tmp3;
					TrainCar* yetanothertmp;
					if (head3->prev != NULL) {
						yetanothertmp = head3->prev;
						yetanothertmp->next = NULL;
					}
					head3->prev = NULL;
				}



			}

			//code comes here if engines are already in their respective halves.
			else {
				for (tmp3 = head1; i <= (train_length / 2); tmp3 = tmp3->next) {
					i += 1;
				}
					if (train_length % 2 == 0) {
						head3 = tmp3;
						tmp3 = tmp3->prev;
						tmp3->next->prev = NULL;
						tmp3->next = NULL;
						head2 = head1;
					}
					else {
						head3 = tmp3;
						head3->prev->next = NULL;
						head3->prev = NULL;
						head2 = head1;
					}



			}
			head1 = NULL;

}


// =======================================================================
// =======================================================================