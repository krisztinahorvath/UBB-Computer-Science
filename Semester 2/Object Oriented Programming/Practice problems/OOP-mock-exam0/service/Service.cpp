//
// Created by krisz on 6/4/2022.
//

#include "Service.h"
#include <algorithm>
#include <fstream>

Service::~Service() {

}

int Service::add_issue_serv(std::string desc, std::string status, std::string reporter, std::string solver) {
    Issue i(desc, status, reporter, solver);
    std::vector<Issue> is;
    for(auto k: issues)
        if(k.get_description() == i.get_description())
            is.push_back(k);

    if(i.get_description().empty() || !is.empty())
        return 0;

    issues.push_back(i);
    notify(); /// observer notify

    return 1;


}

std::vector<Issue> Service::get_sorted_issues() {
    std::vector<Issue> sorted = issues;

    std::sort(sorted.begin(), sorted.end(), [](Issue i1, Issue i2){return i1.get_status() > i2.get_status();});

    std::sort(sorted.begin(), sorted.end(), [](Issue i1, Issue i2){if(i1.get_status() == "open" && i2.get_status() == "open") return i1.get_description() < i2.get_description(); return false;});
    std::sort(sorted.begin(), sorted.end(), [](Issue i1, Issue i2){if(i1.get_status() == "closed" && i2.get_status() == "closed") return i1.get_description() < i2.get_description(); return false;});

    return sorted;

}

void Service::read_from_users() {
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-exam0\repo\users.txt)";
    std::ifstream f(file);

    User u{};
    while(f >> u){
        users.push_back(u);
    }
    f.close();
}

void Service::read_file_issues() {
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-exam0\repo\issues.txt)";
    std::ifstream f(file);

    Issue i{};
    while(f >> i)
        issues.push_back(i);
    f.close();
}

void Service::write_file_issues() {
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-exam0\repo\issues.txt)";
    std::ofstream f(file, std::ios::trunc);
    if(!f.is_open()){
        std::string error = "\n\tError! Couldn't open watchlist CSV file!\n";
        return;
    }
    for(auto m: issues)
        f << m << "\n";
    f.close();
}

Service::Service() {

}

void Service::remove_issue(std::string desc) {
    int pos = 0;
    for(auto i:issues){
        if(i.get_description() == desc && i.get_status() == "closed"){
            issues.erase(issues.begin() + pos);
            notify();
            break;
        }
        pos++;
    }
}

void Service::resolve_issue(std::string desc, std::string solver) {
    int index = 0;
    for(auto i:get_issues_serv()){
        if(i.get_description() == desc){
            Issue is(desc, "closed", i.get_reporter(), solver);
            issues[index] = is;
            notify();
            break;
        }
        index++;
    }

}
