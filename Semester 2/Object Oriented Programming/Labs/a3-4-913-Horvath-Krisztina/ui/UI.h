#pragma once
#include "CountryServ.h"

typedef  struct
{
    Service* serv;
}UI;

UI* create_ui(Service* s);
void destroy_ui(UI* ui);

void start_ui(UI* ui);
