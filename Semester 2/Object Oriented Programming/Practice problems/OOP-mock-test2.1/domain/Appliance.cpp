//
// Created by krisz on 5/4/2022.
//

#include "Appliance.h"

std::string Appliance::toString() {
    std::stringstream buffer;
    buffer << "id: " << id << ", weight: " << weight;
    return buffer.str();
}

Appliance::Appliance() = default;

Appliance::~Appliance() = default;

double Refrigerator::consumed_electricity() {
    double res = 0;
    if(electricity_usage_class == "A")
        res = 30*3;
    else if(electricity_usage_class == "A+")
        res = 30*2.5;
    else if(electricity_usage_class == "A++")
        res = 30*2;
    if(has_freezer)
        res += 20;

    return res;

}

std::string Refrigerator::toString() {
    std::stringstream buffer;
    std::string yes;
    if(has_freezer)
        yes = "yes";
    else
        yes = "no";
    buffer <<"Refrigerator: " <<  "id: " << id << ", weight: " << weight << ", electricity usage class: " << electricity_usage_class << "has freezer: " << yes << "\n";
    return buffer.str();
}

Refrigerator::~Refrigerator() {

}

double DishWasher::consumed_electricity() {
    return (consumed_energy_for_one_hour/washing_cycle_length)*20;
}

std::string DishWasher::toString() {
    std::stringstream buffer;
    buffer <<"Dish washer: " <<  "id: " << id << ", weight: " << weight << ", washing cycle lenght, " << washing_cycle_length << ", consumed energy/one hour: " << consumed_energy_for_one_hour << "\n";

    return buffer.str();
}

DishWasher::~DishWasher() {

}
