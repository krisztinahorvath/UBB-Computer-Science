#pragma once
#include "Service.h"

class UI {
private:
    Service serv;

public:
    UI(const Service s): serv(s) {}
    void start();

private:
    void add_bill_ui();
    void list_all_ui();

};


