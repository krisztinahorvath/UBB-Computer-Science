#pragma once
#include <string>
#include <sstream>
#include <utility>

class Dwelling{
private:
    double price;
    bool is_profitable;

public:
    Dwelling();
    Dwelling(double price, bool prof): price(price), is_profitable(prof){}
    ~Dwelling();
    double get_price() const { return price;}
    double get_is_profitable() const {return is_profitable;}
    std::string to_string();
};

class Client {
protected:
    std::string name;
    double income;

public:
    Client();
    ~Client();
    Client(std::string name, double income): name(std::move(name)), income(income){}
    virtual double total_income();
    virtual std::string to_string();
    virtual bool is_interested(Dwelling d) = 0; /// todo add dwelling
    std::string get_name() {return name;}
};

class Person: public Client{
public:
    Person(std::string name, double income): Client(std::move(name), income){}
    bool is_interested(Dwelling d) override;
};

class Company:public Client{
private:
    double money_from_investments;


public:
    Company(std::string name, double inc, double inv): Client(name, inc), money_from_investments(inv){}
    ~Company();
    double total_income() override;
    std::string to_string() override;
    bool is_interested(Dwelling d) override;
};


