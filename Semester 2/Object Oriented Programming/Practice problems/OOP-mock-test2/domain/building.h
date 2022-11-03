#pragma once
#include <string>
#include <utility>

class Building{
protected:
    std::string address;
    int constructionYear;

public:
    Building();
    Building(std::string address, int year): address(std::move(address)), constructionYear(year){}
    int get_year() const { return this->constructionYear;}

    ~Building();

    virtual bool mustBeRestored() = 0;
    virtual bool canBeDemolished() = 0;
    virtual std::string toString();

};

class Block: public Building{
private:
    int totalApartments;
    int occupiedApartments;

public:
    Block(const std::string& _address, int _year, int _totalApartments, int _occupiedApartments);
    ~Block();
    bool mustBeRestored() override;
    bool canBeDemolished() override;
    std::string toString() override;

};

class House: public Building{
private:
    bool isHistorical;

public:
    House(const std::string& _address, int _year, bool _isHistorical);
    bool mustBeRestored() override;
    bool canBeDemolished() override;
    std::string toString() override;
};