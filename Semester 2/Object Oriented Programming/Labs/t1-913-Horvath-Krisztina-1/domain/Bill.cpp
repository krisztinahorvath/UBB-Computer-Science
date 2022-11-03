#include "Bill.h"
#include <string>

Bill::Bill() {
    this->serial_number = "";
    this->company = "";
    this->due_date = "";
    this->sum = 0;
    this->isPaid = false;
}

Bill::Bill(std::string& serial_number, std::string& company, std::string& due_date, int sum, bool isPaid) {

    this->serial_number = serial_number;
    this->company = company;
    this->due_date = due_date;
    this->sum = sum;
    this->isPaid = isPaid;
}

