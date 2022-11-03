#pragma once
#include <iostream>
#include <string>

class Bill {
private:
    std::string serial_number;
    std::string company;
    std::string due_date;
    int sum;
    bool isPaid;

public:
    Bill();
    Bill(std::string& serial_number, std::string& company, std::string& due_date, int sum, bool isPaid);
    std::string get_serial_number() {return this->serial_number; }
    std::string get_company() { return this->company; }
    std::string get_due_date() {return this->due_date; }
    int get_sum() const {return this->sum; }
    bool get_isPaid() const { return this->isPaid; }

};


