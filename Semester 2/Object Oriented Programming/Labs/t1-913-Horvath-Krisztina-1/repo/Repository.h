#pragma once
#include "DynamicVector.h"
#include "Bill.h"

class Repository {
private:
    DynamicVector<Bill> bills;

public:
    int add_bill(Bill& b);
    int remove_bill(std::string& serial_number);
    int find_bill(Bill& b);
    DynamicVector<Bill> get_repo() { return this->bills; }
};

