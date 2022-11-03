#pragma once
#include "Observer.h"
#include "User.h"
#include "Issue.h"

class Service: public Subject{
private:
    std::vector<User> users;
    std::vector<Issue> issues;

public:
    Service();
    ~Service();

    std::vector<Issue> get_issues_serv() { return issues; }
    std::vector<User> get_users() {return users;}
    int add_issue_serv(std::string desc, std::string status, std::string reporter, std::string solver);

    std::vector<Issue> get_sorted_issues();
    void read_from_users();
    void read_file_issues();
    void write_file_issues();

    void remove_issue(std::string desc);

    void resolve_issue(std::string desc, std::string solver);

};
