#include "Repository.h"

int Repository::add_bill(Bill &b) {
    this->bills.add(b);
    return 0;
}

int Repository::find_bill(Bill &b) {
    Bill aux;
    for(int i = 0; i < this->bills.get_size(); i++){
        aux = this->bills.get_elem(i);
        if(b.get_serial_number() == aux.get_serial_number())
            return i;
    }
    return -1;
}

int Repository::remove_bill(std::string& serial_number) {
    Bill aux;
    for(int i = 0; i < this->bills.get_size(); i++){
        aux = this->bills.get_elem(i);
        if(serial_number == aux.get_serial_number()){
            this->bills.remove(i);
            return 1;
        }

    }
    return 0;
}
