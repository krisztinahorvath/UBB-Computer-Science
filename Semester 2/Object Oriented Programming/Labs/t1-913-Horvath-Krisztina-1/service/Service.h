#pragma once
#include <utility>
#include "DynamicVector.h"
#include "Repository.h"
#include "Bill.h"

class Service {
private:
    Repository repo;

public:
    explicit Service(Repository  r): repo(std::move(r)) {}
    int add_bill_serv(std::string& serial_number, std::string& company, std::string& due_date, int sum, bool isPaid);
    int remove_bill_serv(std::string& serial_number);
    DynamicVector<Bill> get_all_bills() { return this->repo.get_repo(); }

};


