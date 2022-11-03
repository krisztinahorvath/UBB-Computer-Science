#pragma once
#include "Item.h"

class Service {
private:
    std::vector<Item> items;

public:
    std::vector<Item> get_all_items() {return items;}
    std::vector<Item> get_sorted_items();
//    std::vector<Item> get_matching_items(std::string s);

    void read_from_file();
    std::vector<Item> get_by_category(std::string c);
    std::vector<Item> sort_by_quantity(std::string c);


};

