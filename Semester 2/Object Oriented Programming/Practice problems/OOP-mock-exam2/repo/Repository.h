#pragma once
#include "User.h"
#include <vector>

class Repository {
private:
    std::vector<User> users;
    std::vector<Question> questions;
    std::vector<Answer> answers;

public:
    Repository();
    void read_file_users();
    void read_file_questions();
    void read_file_answers();

    std::vector<User> get_users(){ return users;}
    std::vector<Question> get_questions(){ return questions;}
    std::vector<Answer> get_answers(){ return answers;}

    /** Adds a question to the vector that holds all the questions*/
    void add_question(Question& q);

    void write_file_questions();
    void write_file_answers();
};


