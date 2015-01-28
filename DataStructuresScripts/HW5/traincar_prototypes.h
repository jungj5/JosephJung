#ifndef TRAIN_H
#define TRAIN_H
#include <vector>
// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//


std::vector<TrainCar*> ShipFreight(TrainCar *&engines, TrainCar *&freight, int min_speed, int max_cars);


void PushBack(TrainCar* &head, TrainCar* car);


void DeleteAllCars(TrainCar * & head);

TrainCar* PopBack(TrainCar * & head);

float Speed(TrainCar *& head);

void CountEnginesAndTotalWeight(TrainCar*& head, int &total_weight, int &num_engines, int &num_freight_cars, int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars);

float CalculateSpeed(TrainCar *& head);

void Separate(TrainCar *& head1, TrainCar *& head2, TrainCar *& head3);




#endif