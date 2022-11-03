#pragma once
#include "Task.h"

class Service {
private:
    std::vector<Task> tasks;

public:
    Service();
    ~Service();

    std::vector<Task> get_all_tasks() { return tasks; }
    std::vector<Task> get_sorted_tasks();
    std::vector<Task> get_by_priority(int p);
    void read_from_file();
};


