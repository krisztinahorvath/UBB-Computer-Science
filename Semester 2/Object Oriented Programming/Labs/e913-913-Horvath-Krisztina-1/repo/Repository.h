#pragma once
#include "Question.h"

class Repository {
private:
    std::vector<Question> questions;
    std::vector<Participant> participants;
    std::vector<Question> selected_questions;

public:
    Repository();
    void read_file_questions();
    void read_file_participants();
    void write_file_questions();
    void write_file_participants();

    std::vector<Question> get_questions() { return questions; }
    std::vector<Participant> get_participants() { return  participants; }

    void add_question(Question& q){questions.push_back(q);}
    void add_selected_questions(Question& q){ selected_questions.push_back(q);}\
    std::vector<Question> get_selected_questions(){ return selected_questions;}

    int answer_question(int id, std::string ans, std::string name);
};

