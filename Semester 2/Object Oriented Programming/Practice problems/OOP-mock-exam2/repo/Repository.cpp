//
// Created by krisz on 6/5/2022.
//

#include "Repository.h"
#include <fstream>

Repository::Repository() {

}

void Repository::read_file_users() {
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-exam2\repo\users.txt)";
    std::ifstream f(file);

    User u{};
    while(f >> u)
        users.push_back(u);
    f.close();
}

void Repository::read_file_questions() {
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-exam2\repo\questions.txt)";
    std::ifstream f(file);

    Question q{};
    while(f >> q)
        questions.push_back(q);
    f.close();
}

void Repository::read_file_answers() {
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-exam2\repo\answers.txt)";
    std::ifstream f(file);

    Answer u{};
    while(f >> u)
        answers.push_back(u);
    f.close();
}

void Repository::add_question(Question& q) {
    questions.push_back(q);
}

void Repository::write_file_questions() {
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-exam2\repo\questions.txt)";
    std::ofstream f(file, std::ios::trunc);

    for(auto q:questions)
        f << q << "\n";
    f.close();
}

void Repository::write_file_answers() {
    std::string file = R"(C:\Facultate\OOP\tests\OOP-mock-exam2\repo\answers.txt)";
    std::ofstream f(file, std::ios::trunc);

    for(auto a:answers)
        f << a << "\n";
    f.close();

}
