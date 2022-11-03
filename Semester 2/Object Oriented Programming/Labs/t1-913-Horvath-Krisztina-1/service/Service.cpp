
#include "Service.h"

int Service::add_bill_serv(std::string &serial_number, std::string &company, std::string &due_date, int sum, bool isPaid) {

    Bill b = Bill(serial_number, company, due_date, sum, isPaid);

    return this->repo.add_bill(b);
}

int Service::remove_bill_serv(std::string &serial_number)
{
    return this->repo.remove_bill(serial_number);
}


