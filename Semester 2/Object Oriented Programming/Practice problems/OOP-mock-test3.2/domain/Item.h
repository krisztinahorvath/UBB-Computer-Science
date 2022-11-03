#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Item {
private:
    std::string category;
    std::string name;
    int quantity;

public:
    Item();
    ~Item();
    Item(std::string c, std::string n, int q): category(c), name(n), quantity(q){}

    std::string get_category() { return category; }
    std::string get_name() { return name; }
    int get_quantity() { return quantity; }

    friend std::istream& operator>>(std::istream& is, Item& i);
    std::string to_string() const;
};


