#pragma once
#include "Task.h"
#include <vector>
class Service {
private:
    std::vector<Task > tasks;

public:
    Service();
    ~Service();
    std::vector<Task > get_all_tasks() { return tasks; }
    void read_from_file();
    void write_to_file();
    std::vector<Task> get_sorted();
    int get_task_priority(int p);

};

