//
// Created by krisz on 5/4/2022.
//

#include "Client.h"

Dwelling::Dwelling() {

}

Dwelling::~Dwelling() {

}

std::string Dwelling::to_string() {
    std::stringstream buffer;
    std::string prof;
    if(is_profitable)
        prof = "yes";
    else
        prof = "no";
    buffer << "price: " << price << ", is profit: " << prof;
    return buffer.str();
}

double Company::total_income() {
    return income + money_from_investments;
}

std::string Company::to_string() {
    std::stringstream buffer;
    buffer << "Company: " << "name: " << name << ", income: " << total_income() << ", invest: " << money_from_investments;
    return buffer.str();
}


bool Company::is_interested(Dwelling d) {
    if(d.get_price() / 100 <= this->total_income() && d.get_is_profitable())
        return true;
    return false;
}

Company::~Company() {

}

bool Person::is_interested(Dwelling d) {
    if(d.get_price() / 1000 <= this->total_income())
        return true;
    return false;
}

double Client::total_income() {
    return income;
}

std::string Client::to_string() {
    std::stringstream buffer;
    buffer << "name: " << name << ", income: " << income;
    return buffer.str();
}

Client::Client() {

}

Client::~Client() {

}
