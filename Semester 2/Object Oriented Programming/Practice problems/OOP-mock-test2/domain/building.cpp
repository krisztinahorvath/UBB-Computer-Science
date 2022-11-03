#include "building.h"
#include <iostream>
#include <sstream>

Building::Building() {
    this->address = "";
    this->constructionYear = 0;
}

std::string Building::toString() {
    std::stringstream buffer;
    buffer << "Address: " << this->address << ",    year of constr: " << this->constructionYear;
    return buffer.str();
}

Building::~Building() = default;


Block::Block(const std::string &_address, int _year, int _totalApartments, int _occupiedApartments): Building(_address,_year), totalApartments(_totalApartments), occupiedApartments(_occupiedApartments) {}

bool Block::mustBeRestored() {
    if(2022 - this->constructionYear > 40 && this->occupiedApartments > this->totalApartments*0.8)
        return true;
    return false;
}

bool Block::canBeDemolished() {
    if(this->totalApartments*0.05 > this->occupiedApartments)
        return true;
    return false;
}

std::string Block::toString() {
    std::string baseStr = Building::toString();
    std::string type = "Block: ";
    std::string info = ",     total apartment: " + std::to_string(this->totalApartments) + ",    nr occupied ap: " + std::to_string(this->occupiedApartments);
    return type + baseStr + info;
}

Block::~Block() = default;


House::House(const std::string &_address, int _year, bool _isHistorical): Building(_address, _year), isHistorical(_isHistorical) {
}

bool House::mustBeRestored() {
    if(2022 - this->constructionYear > 100)
        return true;
    return false;
}

bool House::canBeDemolished() {
    if(!isHistorical)
        return true;
    return false;
}

std::string House::toString() {
    std::stringstream buffer;
    buffer << "House, " << "address: " << this->address << ",    year of constr: " << this->constructionYear << ",    historical: " << this->isHistorical;
    return buffer.str();
}
