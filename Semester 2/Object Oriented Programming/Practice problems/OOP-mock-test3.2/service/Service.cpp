//
// Created by krisz on 5/24/2022.
//

#include "Service.h"
#include <fstream>

std::vector<Item> Service::get_sorted_items() {
    std::vector<Item> sorted = items;

    /// asc by category
    for(int i = 0; i < sorted.size() - 1; i++)
        for(int j = i + 1; j < sorted.size(); j++)
            if(sorted[i].get_category() > sorted[j].get_category()){
                Item it = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = it;
            }

    /// asc by name
    for(int i = 0; i < sorted.size() - 1; i++)
        for(int j = i + 1; j < sorted.size(); j++)
            if(sorted[i].get_category() == sorted[j].get_category() && sorted[i].get_name() > sorted[j].get_name()){
                Item it = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = it;
            }
    return sorted;
}

void Service::read_from_file() {
    std::string file_name = R"(C:\Facultate\OOP\tests\OOP-mock-test3.2\items.txt)";
    std::ifstream f(file_name);

    Item i{};
    while(f >> i)
        items.push_back(i);
    f.close();
}

std::vector<Item> Service::get_by_category(std::string c) {
    std::vector<Item> list;
    for(auto i: items)
        if(i.get_category() == c)
            list.push_back(i);
    return list;
}

std::vector<Item> Service::sort_by_quantity(std::string c) {
    std::vector<Item> sorted = this->get_by_category(c);
    for(int i = 0; i < sorted.size() - 1; i++)
        for(int j = i + 1; j < sorted.size(); j++)
            if(sorted[i].get_quantity() > sorted[j].get_quantity()){
                Item it = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = it;
            }

    return sorted;
}

//std::vector<Item> Service::get_matching_items(std::string s) {
//    std::vector<Item> v;
//    for(auto i: items)
//        if(i.get_category().find(s) || i.get_name().find(s))
//            v.push_back(i);
//    return v;
//}
